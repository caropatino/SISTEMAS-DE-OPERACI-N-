#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
// #include "algoritmo.h"

void fusion(char A[][20], char patron[][1], int inicio, int mitad, int fin, int cont) {
	int z = 20; // constate, tamaño de palabra
	int i, j, k;
	int n1 = mitad - inicio + 1;
	int n2 = fin - mitad;
	int p1, p2;

	char I[20][20], D[20][20]; // Arreglos temporales

	// GUARDAR EN ARREGLOS TEMPORALES
	for (i = 0; i < n1; i++)
		for (int m = 0; m < z; m++)
			I[i][m] = A[inicio + i][m];
	for (j = 0; j < n2; j++)
		for (int n = 0; n < z; n++)
			D[j][n] = A[mitad + 1 + j][n];

	i = 0;
	j = 0;
	k = inicio;

	while (i < n1 && j < n2) {

		// BUSCAR POSICIONES DEL ALFABETO PATRON
		for (int t = 0; t < cont; t++) {

			if (I[i][0] == patron[t][0]) {
				p1 = t;
			}
			if (D[j][0] == patron[t][0]) {
				p2 = t;
			}
		}

		// COMPARAR POSICIONES
		if (p1 <= p2) {
			for (int m = 0; m < z; m++)
				A[k][m] = I[i][m];
			i++;
		}
		else {
			for (int m = 0; m < z; m++)
				A[k][m] = D[j][m];
			j++;
		}
		k++;
	}

		// AGREGAR LAS OTRAS CADENAS
		while (i < n1)
		{
			for (int m = 0; m < z; m++)
				A[k][m] = I[i][m];
			i++;
			k++;
		}
		while (j < n2)
		{
			for (int m = 0; m < z; m++)
				A[k][m] = D[j][m];
			j++;
			k++;
		}

}

// MERGESORT
void mergesort(char A[][20], char patron[][1], int inicio, int fin, int cont) {
	if (inicio < fin) { // Hasta que se divida a 1

		int mitad = inicio + (fin - inicio) / 2;

		int fd1[2], fd2[2],fd3[2],fd4[2];
		int pid1, pid2;
		int stat;

		// PIPES
		if (pipe(fd1) == -1){
		    perror("Pipe error");
		    exit(-1);
		}
		if (pipe(fd2) == -1){
		    perror("Pipe error");
		    exit(-1);
		}
		if (pipe(fd3) == -1){
		    perror("Pipe error");
		    exit(-1);
		}
		if (pipe(fd4) == -1){
		    perror("Pipe error");
		    exit(-1);
		}

		int mitad = inicio + (fin - inicio) / 2;

		pid1 = fork();
		switch(pid1){
		  case -1: perror("Pipe error");
		          exit(-1);
		  case 0: close(fd1[1]);
		          close(fd2[0]);

							// Proceso de lado izquierdo del arreglo
		          while(read(fd1[0],A,mitad) != 0)
		            mergesort(A, patron, inicio, mitad, cont);


		          write(fd2[1],A,mitad);
		          close(fd2[1]);
		          exit(0);
		  default:
							// Proceso padre
		          close(fd1[0]);
		          close(fd2[1]);

							// Envia info a hijo izquierdo
		          write(fd1[1],A,mitad);
		          close(fd1[1]);

							// Leer info de hijo izquierdo
		          while(read(fd2[0],A,mitad)!=0)
		              wait(NULL);
		          close(fd2[0]);

		          pid2 = fork();
		          switch(pid2){
		            case -1: perror("fork error\n");
		            exit(-1);
		            case 0:
												// Proceso de lado derecho del arreglo
												close(fd3[1]);
		                    close(fd4[0]);

												// Lee del padre
		                    while(read(fd3[0],A[mitad+1],fin)!=0)
		                      mergesort(A, patron, mitad + 1, fin, cont);

												// Envia info al padre, del hijo derecho
		                    write(fd4[1],A[mitad+1],fin);
		                    close(fd4[1]);
		                    exit(0);

		            default:
		                    close(fd3[0]);
		                    close(fd4[1]);

												// Envia info al hijo derecho
		                    write(fd3[1],A[mitad+1],fin);
		                    close(fd3[1]);

												// Lee info del hijo derecho
		                    while(read(fd4[0],A[mitad+1],fin)!=0)
		                      wait(NULL);
		                    close(fd4[0]);

												// FUSIONAR CHAN CHAN CHAN
		                    fusion(A, patron, inicio, mitad, fin, cont);

		          }
						}
		}
/*
		mergesort(A, patron, inicio, mitad, cont); // una mitad
		mergesort(A, patron, mitad + 1, fin, cont); // otra mitad


		 fusion(A, patron, inicio, mitad, fin, cont); // fusiona
	} */
}

// IMPRIMIR ARREGLO
void imprimeArreglo(char A[][20], int arraysize) {
	int i = 0, j = 0;
	for (i = 0; i<arraysize; ++i)
	{
		printf("%s ", A[i]);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[]) {

	// LEER ARGUMENTOS DE LLAMADA AL PROGRAMA
	char *archivoAlfabeto = argv[1];
	char *archivoPalabras = argv[2];


	if (argc != 3){
		printf("Fallo en los argumentos\nIndicar archivos (.txt)\n");
		return 1;
	}

	int n;
	int arraysize = 0; // lineas de palabras
	FILE *fp, *al; // archivos

	// ABRIR ARCHIVOS
	fp = fopen(archivoPalabras, "r");
	al = fopen(archivoAlfabeto, "r");
	if ((fp == NULL) || (al == NULL)) { fputs("File error", stderr); exit(1); }

	// GUARDAR PALABRAS EN MATRIZ
	char palabra[20];
	char matriz[50][20];
	for (int i = 0; fscanf(fp, "%s", &palabra) == 1; i++) {
		strcpy(matriz[i], palabra);
		arraysize++;
	}
	fclose(fp);

	// GUARDAR PATRON DE ALFABETO
	char patron[30][1];
	char p[1];
	int cont = 0;
	for (int i = 0; fscanf(al, "%s", &p) == 1; i++) {
		strcpy(patron[i], p);
		cont++;
	}
	fclose(al);

/*
	pid_t child_pid = 0;
	int fd[2];

	if (pipe(fd)== -1) {  // prueba de pipe
		perror("Fallido");
		return 1;
	}

	printf("Proceso actual PID: %id \n Padre PID: %id\n\n", (long)getpid(),(long)getppid());
	*/

	/*Esto se logra mediante la función fdopen. Por ejemplo para leer de p[0]
	podemos simplemente hacer FILE *f=fdopen(p[0], "r+"),
	y ya disponemos de un FILE* listo para leer los bytes que emergen del pipe.*/

	// PARAMETROS
	int inicio = 0;
	int fin = arraysize - 1;


	imprimeArreglo(matriz, arraysize);
	mergesort(matriz, patron, 0, fin, cont);
	imprimeArreglo(matriz, arraysize);

	system("PAUSE");
	return 0;

}
