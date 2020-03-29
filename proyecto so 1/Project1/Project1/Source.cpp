#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <unistd.h>
#include<iostream>
#include<cstring>
using namespace std;


/*void fusion(char *A[], int inicio, int mitad, int fin) {

	int i, j, k;
	int n1 = mitad - inicio + 1;
	int n2 = fin - mitad;

	char *I[20], *D[20]; // Arreglos temporales

	for (i = 0; i < n1; i++)
		I[i] = (A[inicio + i]);
	for (j = 0; j < n2; j++)
		D[j] = A[mitad + 1 + j];

	i = 0;
	j = 0;
	k = inicio;

	while (i < n1 && j < n2) {
		if (strcmp(I [i], D [j]) <= 0){
			A[k] = I[i];
			i++;
		}
		else {
			A[k] = D[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		A[k] = I[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		A[k] = D[j];
		j++;
		k++;
	}
}

void mergesort(char *A[], int inicio, int fin) {
	if (inicio < fin) {
		int mitad = inicio + (fin - inicio) / 2;

		mergesort(A, inicio, mitad);
		mergesort(A, mitad + 1, fin);

		fusion(A, inicio, mitad, fin);
	}
}

void imprimeArreglo(char A[][], int arraysize) {

	for (int i = 0; i < arraysize; i++) {
		printf("%s \n", A[i]);
	}
	printf("\n");

}*/

int main() {
	char *A[20];
	char linea [20];
	int cont = 0;
	FILE *fp;
	fp= fopen ("numeros.txt", "r");
	if (fp == NULL) { fputs("File error", stderr); exit(1); }

	while (fgets(linea, 20, fp) != NULL){
	//while (!feof(fp)) {
		A[cont] = fgets(linea,20,fp);
		cont++;
		printf("%s\n\n\n", A[cont]);
	}

	fclose(fp);

	for (int i = 0; i < cont; i++) {
		printf("%c", A[i]);
	}

//	pid_t child_pid = 0; // crea un pipe no nominal hijo 

	int inicio = 0;
	int arraysize = cont;
	int fin = arraysize-1;

	//imprimeArreglo(A, arraysize);

	/*mergesort(&A, 0, fin);

	imprimeArreglo(&A, arraysize);*/



	system("PAUSE");
	return 0;
}

