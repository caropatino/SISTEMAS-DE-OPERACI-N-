#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

//#include <unistd.h>

void fusion(char A[][20], int inicio, int mitad, int fin) {
	int z = 20; // constate, tamaño de palabra
	int i, j, k;
	int n1 = mitad - inicio + 1;
	int n2 = fin - mitad;

	char I[20][20], D[20][20]; // Arreglos temporales

	for (i = 0; i < n1; i++)
		for (int m = 0; m < z;m++)
		I[i][m] = A[inicio + i][m];
	for (j = 0; j < n2; j++)
		for (int n = 0; n < z; n++)
		D[j][n] = A[mitad + 1 + j][n];

	i = 0;
	j = 0;
	k = inicio;

	while (i < n1 && j < n2) {
		if (I[i][0] <= D[j][0]) {
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

void mergesort(char A[], int inicio, int fin) {
	if (inicio < fin) {
		int mitad = inicio + (fin - inicio) / 2;

		mergesort(A, inicio, mitad);
		mergesort(A, mitad + 1, fin);

		fusion(A, inicio, mitad, fin);
	}
}
