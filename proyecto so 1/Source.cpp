#include <stdio.h>
#include <stdlib.h>

void fusion(int A[], int inicio, int mitad, int fin) {

	int i, j, k;
	int n1 = mitad - inicio + 1;
	int n2 = fin - mitad;

	int I[20], D[20]; // Arreglos temporales

	for (i = 0; i < n1; i++)
		I[i] = A[inicio + i];
	for (j = 0; j < n2; j++)
		D[j] = A[mitad + 1 + j];

	i = 0;
	j = 0;
	k = inicio;

	while (i < n1 && j < n2) {
		if (I[i] <= D[j]) {
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

void mergesort(int A[], int inicio, int fin) {
	if (inicio < fin) {
		int mitad = inicio + (fin - inicio) / 2;

		mergesort(A, inicio, mitad);
		mergesort(A, mitad+1, fin);

		fusion(A, inicio, mitad, fin);
	}
}

void imprimeArreglo(int A[], int arraysize) {

	for (int i = 0; i < arraysize; i++) {
		printf("%i \n", A[i]);
	}
	printf("\n");

}

int main() {
	//int n;
	int arraysize = 8;
	int A[8] = { 5,6,2,8,9,10,1,3 };

	int inicio = 0;
	int fin = arraysize - 1;

	imprimeArreglo(A, arraysize);

	mergesort(A, 0, fin);

	imprimeArreglo(A, arraysize);


	system("PAUSE");
	return 0;
}

