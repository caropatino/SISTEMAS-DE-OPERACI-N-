#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void buscar(char patron[][2], int cont) {
	int p1, p2;
	int t = 0;
	char p[1][1] = { 'j' }, s[1][1] = { 's' };

	while (t < cont) {
		printf("chao %i \n", t);
		if (patron[t][0] == p[1][1]) {   //NO SE PORQUE NO ENTRA A ESTAS CONDICIONES
			printf("hola %i \n", t);
			p1 = t;
		}
		if (patron[t][0] == p[1][1]) {
			printf("chao %i \n", t);
			p2 = t;
		}
		t++;
	}

	/*for (int t = 0; t < cont; t++) {
		if (patron[t][0] == p) {
			printf("hola %i \n", t);
			p1 = t;
		}
		if (patron[t][0] == s) {
			printf("chao %i \n", t);
			p2 = t;
		}
	}
	*/
/*	if (p1 > p2) {
		printf("%s %s", patron[p2], patron[p1]);
	}
	else { printf("%s %s", patron[p1], patron[p2]); }*/
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
	fclose(fp);


	fclose(al);

	for (int i = 0; i < cont; i++) {
		printf("En la posicion %i se imprime %s \n", i, patron[i]);
	}

	buscar(patron, cont);

	system("PAUSE");
	return 0;
}