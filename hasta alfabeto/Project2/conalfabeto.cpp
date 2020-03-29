#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "algoritmo.h"

//#include <unistd.h>

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

	for (int i = 0; fscanf(fp, "%s", palabra) == 1; i++) {
		strcpy(matriz[i], palabra);
		arraysize++;
	}
	fclose(fp);


	char patron[30][2];
	char p[2];
	int cont = 0;

	for (int i = 0; fscanf(al, "%s", p) == 1; i++) {
		strcpy(patron[i], p);
		cont++;
	}

	fclose(al);

	//	pid_t child_pid = 0; // crea un pipe no nominal hijo

	int inicio = 0;
	int fin = arraysize - 1;

	imprimeArreglo(matriz, arraysize);

	mergesort(matriz, 0, fin);

	imprimeArreglo(matriz, arraysize);

	system("PAUSE");
	return 0;
}
