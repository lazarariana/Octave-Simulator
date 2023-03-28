#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "functions.h"
#define R 10007

void create_v(int **v, int lenght)
{
	int *aux = NULL;
	if (lenght > 1) {
	   /* modific dimensiunile vectorului pentru a adauga dimensiunile unui nou
       element */
		aux = (int *)realloc((*v), lenght * sizeof(int));
		if (!aux)
			(*v) = NULL;
		(*v) = aux;
	} else {
	     /* aloc memorie pentru vectorii de dimeniune si completez cu datele
	     primului element din vectorul de matrice */
		aux = (int *)calloc(lenght, sizeof(int));
		if (!aux)
			(*v) = NULL;
		(*v) = aux;
	}
}

void free_mat(int ***a, int nr_lin)
{
	int i;
	for (i = 0; i < nr_lin; i++) {
		free((*a)[i]);
		(*a)[i] = NULL;
	}
	free((*a));
	(*a) = NULL;
}

int **create_mat(int nr_lin, int nr_col)
{
	int **aux = NULL, i;
	aux = (int **)malloc(nr_lin * sizeof(int *));
	if (!aux)
		return NULL;
	for (i = 0; i < nr_lin; i++) {
		aux[i] = (int *)malloc(nr_col * sizeof(int));
		if (!aux[i]) {
			free_mat(&aux, i);
			return NULL;
		}
	}
	return aux;
}

int verif_index(int index1, int index2, int nr_matrix)
{
	if (index1 < 0 || index2 < 0)
		return 0;
	if (index1 > nr_matrix - 1 || index2 > nr_matrix - 1)
		return 0;
	return 1;
}

/* functia power se poate aplica doar pentru matricele patratice,
in cazul carora matricea rezultat a inmultirii are aceeasi
dimensiune ca factorii */
void power(int ***a, int **b, int index, int *lin, int *col)
{
	int **mat, i, j, k;

	/* alocam memorie pentru matricea rezultat. Tinem cont de faptul ca
	elementele trebuie sa fie initial 0, deoarece fiecare element al
	matricei rezultat este o suma de produse */
	mat = (int **)malloc(lin[index] * sizeof(int *));
	for (i = 0; i < lin[index]; i++)
		mat[i] = (int *)calloc(col[index], sizeof(int));
	for (i = 0; i < lin[index]; i++)
		for (j = 0; j < col[index]; j++)
			for (k = 0; k < lin[index]; k++) {
				mat[i][j] = (mat[i][j] + (*a)[i][k] * b[k][j]) % R;
				if (mat[i][j] < 0)
					mat[i][j] += R;
			}

	/* pentru primul pas, matricele a si b sunt de fapt a[index]. Ulterior,
    matricea a trebuie inlocuita cu matricea rezultat pentru a asigura
    continuitatea algoritmului de ridicare la putere. De aceea avem nevoie de
    pointer, ca valoarea sa fie pastrata pentru pasii urmatori. Inainte de
    inlocuire trebuie eliberata memoria */
	for (i = 0; i < lin[index]; i++)
		free((*a)[i]);
	free((*a));
	(*a) = mat;
	mat = NULL;
}
