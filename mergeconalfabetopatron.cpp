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
		//ciclo  para buscar posiciones del alfabeto 
		for (int t = 0; t < cont; t++) {

			if (I[i][0] == patron[t][0]) {
				p1 = t;
			}
			if (D[j][0] == patron[t][0]) {
				p2 = t;
			}
		}

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

void mergesort(char A[][20], char patron[][1], int inicio, int fin, int cont) {
	if (inicio < fin) {
		int mitad = inicio + (fin - inicio) / 2;
		mergesort(A, patron, inicio, mitad, cont);

		mergesort(A, patron, mitad + 1, fin, cont);

		fusion(A, patron, inicio, mitad, fin, cont);
	}
}



void imprimeArreglo(char A[][20], int arraysize) {
	int i = 0, j = 0;
	for (i = 0; i<arraysize; ++i)
	{
		printf("%s ", A[i]);
		printf("\n");
	}
	printf("\n");
}



int main() {
	int n, arraysize = 0;
	FILE *fp, *al;
	char palabra[20];
	fp = fopen("palabras.txt", "r");
	al = fopen("alfabeto.txt", "r");
	if ((fp == NULL) || (al == NULL)) { fputs("File error", stderr); exit(1); }

	char matriz[50][20];

	//Guarda palabras en un arreglo
	for (int i = 0; fscanf(fp, "%s", &palabra) == 1; i++) {
		strcpy(matriz[i], palabra);
		arraysize++;
	}
	fclose(fp);

	char patron[30][1];
	char p[1];
	int cont = 0;

	//	Guarda alfabeto en un arreglo
	for (int i = 0; fscanf(al, "%s", &p) == 1; i++) {
		strcpy(patron[i], p);
		cont++;
	}
	fclose(al);


	//	pid_t child_pid = 0; // crea un pipe no nominal hijo
	//int fd[2]; //dos descriptores de archivo (0 para leer y 1 para escribir)

	/*Esto se logra mediante la función fdopen. Por ejemplo para leer de p[0] podemos simplemente hacer FILE *f=fdopen(p[0], "r+"),
	y ya disponemos de un FILE* listo para leer los bytes que emergen del pipe.*/

	int inicio = 0;
	int fin = arraysize - 1;


	imprimeArreglo(matriz, arraysize);

	mergesort(matriz, patron, 0, fin, cont);

	imprimeArreglo(matriz, arraysize);

	system("PAUSE");
	return 0;
}