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
	FILE *fp;
	char palabra[20];
	//errno_t err;
	fp = fopen("palabras.txt", "r");
	if (fp == NULL) { fputs("File error", stderr); exit(1); }

	char matriz[50][20];

	for (int i = 0; fscanf(fp, "%s", palabra) == 1; i++) {
		strcpy(matriz[i], palabra);
		arraysize++;
	}
	fclose(fp);

	//	pid_t child_pid = 0; // crea un pipe no nominal hijo

	int inicio = 0;
	int fin = arraysize - 1;

	imprimeArreglo(matriz, arraysize);

	mergesort(matriz, 0, fin);

	imprimeArreglo(matriz, arraysize);

	system("PAUSE");
	return 0;
}
