//Copyright Ariana-Maria Lazar-Andrei 312CAb 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "functions.h"
#define R 10007

void task_L(int ****a, int *nr_matrix, int **lin, int **col)
{
	int i, j, value, nr_lin, nr_col, **aux = NULL;

	scanf("%d %d", &nr_lin, &nr_col);
	(*nr_matrix)++;
	if ((*nr_matrix) > 1) {
	   /* modific dimensiunile vectorului pentru a adauga dimensiunile unui nou
       element */
		(*lin) = (int *)realloc((*lin), (*nr_matrix) * sizeof(int));
		(*lin)[(*nr_matrix) - 1] = nr_lin;
		(*col) = (int *)realloc((*col), (*nr_matrix) * sizeof(int));
		(*col)[(*nr_matrix) - 1] = nr_col;
	} else {
	     /* aloc memorie pentru vectorii de dimeniune si completez cu datele
	     primului element din vectorul de matrice */
		(*lin) = (int *)malloc((*nr_matrix) * sizeof(int));
		(*lin)[(*nr_matrix) - 1] = nr_lin;
		(*col) = (int *)malloc((*nr_matrix) * sizeof(int));
		(*col)[(*nr_matrix) - 1] = nr_col;
	}
	if ((*nr_matrix) > 1)
	    /* modific dimensiunile vectorului pentru a adauga un nou element */
		(*a) = (int ***)realloc((*a), (*nr_matrix) * sizeof(int **));
	else
	    /* aloc memorie pentru vectorul de matrice pentru a putea plasa primul
		element */
		(*a) = (int ***)malloc((*nr_matrix) * sizeof(int **));
	if ((*a) == NULL) {
		printf("Out of memory\n");
		task_Q(a, lin, col, (*nr_matrix));
		exit(-1);
	}

	/* formez un vectori de pointeri pentru liniile matricei si aloc numarul
    necesar de coloane dat */
	aux = create_mat(nr_lin, nr_col);
	if (!aux) {
		task_Q(a, lin, col, (*nr_matrix) - 1);
		exit(-1);
	}
	(*a)[(*nr_matrix) - 1] = aux;

	/* completez cu valorile citite matricea */
	for (i = 0; i < nr_lin; i++)
		for (j = 0; j < nr_col; j++) {
			scanf("%d", &value);
			(*a)[(*nr_matrix) - 1][i][j] = value;
		}
}

void task_D(int *lin, int *col, int nr_matrix)
{
	int index;

	scanf("%d", &index);
	/* utilizam informatiile stocate in vectorii de dimensiune
	lin si col in cazul unui index valid */
	if (index < 0 || index > nr_matrix - 1)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", lin[index], col[index]);
}

void task_P(int ***a, int *lin, int *col, int nr_matrix)
{
	int i, j, index;

	scanf("%d", &index);
	/* afisam valorile matricei de pe pozitia index din vectorul de matrice */
	if (index < 0 || index > nr_matrix - 1)
		printf("No matrix with the given index\n");
	else
		for (i = 0; i < lin[index]; i++) {
			for (j = 0; j < col[index]; j++)
				printf("%d ", a[index][i][j]);
			printf("\n");
		}
}

void task_C(int ****a, int **lin, int **col, int nr_matrix)
{
	int i, j, nr_lin, nr_col, index, cnt;
	int *vl = NULL, *vc = NULL, **aux = NULL;
	scanf("%d", &index);
	/* aloc un vector de dimensiune l pentru indicii liniilor ce
	vreau sa le pastrez dupa redimensionare */
	scanf("%d", &nr_lin);
	vl = (int *)malloc(nr_lin * sizeof(int));
	for (i = 0; i < nr_lin; i++) {
		scanf("%d", &cnt);
		vl[i] = cnt;
	}

	/* aloc un vector de dimensiune c pentru indicii coloanelor ce
	vreau sa le pastrez dupa redimensionare */
	scanf("%d", &nr_col);
	vc = (int *)malloc(nr_col * sizeof(int));
	for (i = 0; i < nr_col; i++) {
		scanf("%d", &cnt);
		vc[i] = cnt;
	}

	if (index < 0 || index > nr_matrix - 1) {
		printf("No matrix with the given index\n");
	} else {
	    /* salvez intr-un auxilar valorile aflate la intersectia
	    liniilor si coloanelor date, pentru a nu se pierde
	    cand eliberez matricea */
		aux = create_mat(nr_lin, nr_col);
		if (!aux) {
			task_Q(a, lin, col, nr_matrix - 1);
			exit(-1);
		}
		for (i = 0; i < nr_lin; i++)
			for (j = 0; j < nr_col; j++)
				aux[i][j] = (*a)[index][vl[i]][vc[j]];
		if (aux) {
			for (i = 0; i < (*lin)[index]; i++)
				free((*a)[index][i]);
			free((*a)[index]);
			/* actualizez dimensiunile noii matrice */
			(*lin)[index] = nr_lin;
			(*col)[index] = nr_col;
			/* salvez matricea redimensionata */
			(*a)[index] = aux;
		}
	}
	free(vl);
	free(vc);
}

void task_M(int ****a, int *nr_matrix, int **lin, int **col)
{
	int index1, index2, i, j, k, prod, **aux = NULL;

	scanf("%d %d", &index1, &index2);
	if (!verif_index(index1, index2, (*nr_matrix))) {
		printf("No matrix with the given index\n");
	} else {
	    /* conditia de inmultire a doua matrice */
		if ((*col)[index1] != (*lin)[index2]) {
			printf("Cannot perform matrix multiplication\n");
		} else {
		    /* deoarece matricea rezultat trebuie salvata la finalul
		    multimii de matrice, trebuie sa realocam memoria pentru
		    vectorul de matrice si vectorii de dimensiune lin si col. Ulterior,
		    alocam memorie pentru noua matrice si completam lin si col cu
			informatiile necesare*/
			(*nr_matrix)++;
			(*lin) = (int *)realloc((*lin), (*nr_matrix) * sizeof(int));
			(*col) = (int *)realloc((*col), (*nr_matrix) * sizeof(int));
			(*lin)[(*nr_matrix) - 1] = (*lin)[index1];
			(*col)[(*nr_matrix) - 1] = (*col)[index2];
			(*a) = (int ***)realloc((*a), (*nr_matrix) * sizeof(int **));

			if ((*a) == NULL) {
				printf("Out of memory\n");
				task_Q(a, lin, col, (*nr_matrix));
				return;
			}
			/* utilizam proprietatea conform careia matricea rezultat are
			numarul de linii al primei matrice si numarul de coloane al celei
			de a doua */
			aux = create_mat((*lin)[index1], (*col)[index2]);
			if (!aux) {
				task_Q(a, lin, col, (*nr_matrix) - 1);
				exit(-1);
			}
			(*a)[(*nr_matrix) - 1] = aux;
			/*aplicam algoritmul matematic de inmultire a doua matrice
			si utilizam % R pentru a nu stoca valori de dimensiune mare */
			for (i = 0; i < (*lin)[index1]; i++)
				for (j = 0; j < (*col)[index2]; j++) {
					(*a)[(*nr_matrix) - 1][i][j] = 0;
					for (k = 0; k < (*lin)[index2]; k++) {
						prod = (*a)[index1][i][k] * (*a)[index2][k][j];
						(*a)[(*nr_matrix) - 1][i][j] += prod;
						(*a)[(*nr_matrix) - 1][i][j] %= R;
					}

					if ((*a)[(*nr_matrix) - 1][i][j] < 0)
						(*a)[(*nr_matrix) - 1][i][j] += R;
				}
		}
	}
}

void task_O(int ***a, int *lin, int *col, int nr_matrix)
{
	int *sum, i, j, k, aux, **aux2;

	/* alocam memorie pentru un vector de sume. Initial
	fiecare element este 0, iar la finalul executiei sum[i]
	stocheaza suma elementelor lui a[i], adica matricea de pe
	pozitia i din vectorul de matrice*/
	sum = calloc(nr_matrix, sizeof(int));
	for (i = 0; i < nr_matrix; i++)
		for (j = 0; j < lin[i]; j++)
			for (k = 0; k < col[i]; k++) {
				sum[i] = (sum[i] + a[i][j][k]) % R;
				if (sum[i] < 0)
					sum[i] += R;
			}

	/* efectuam parcurgeri ale vectorului de matrice pana
	cand este sortat crescator. Cand gasim 2 elemente ce nu
	respecta regula, interschimbam atat matricele, cat si sumele
	acestora si vectorii de dimensiune */
	for (i = 0; i < nr_matrix - 1; i++)
		for (j = i + 1; j < nr_matrix; j++)
			if (sum[i] > sum[j]) {
				aux2 = a[i];
				a[i] = a[j];
				a[j] = aux2;
				aux = lin[i];
				lin[i] = lin[j];
				lin[j] = aux;
				aux = col[i];
				col[i] = col[j];
				col[j] = aux;
				aux = sum[i];
				sum[i] = sum[j];
				sum[j] = aux;
			}

	/* eliberam memoria la finalul sortarii */
	free(sum);
}

void task_T(int ****a, int nr_matrix, int **lin, int **col)
{
	int index, **aux, aux2, i, j;

	scanf("%d", &index);
	if (index < 0 || index > nr_matrix - 1) {
		printf("No matrix with the given index\n");
	} else {
	    /* transpusa unei matrice presupune plasarea elementelor de pe linii
	    pe coloane, deci si interschimbarea valorilor dimensiunilor matricei
	    initiale. Realizam acest lucru intr-o matrice auxiliara pentru a nu
	    provoca erori, iar dupa ce am eliberat memoria, putem plasa transpusa
	    in locul matricei de pe pozitia index */
		aux = create_mat((*col)[index], (*lin)[index]);
		if (!aux) {
			task_Q(a, lin, col, nr_matrix);
			exit(-1);
		}
		for (i = 0; i < (*col)[index]; i++)
			for (j = 0; j < (*lin)[index]; j++)
				aux[i][j] = (*a)[index][j][i];

		for (i = 0; i < (*lin)[index]; i++)
			free((*a)[index][i]);
		free((*a)[index]);

		aux2 = (*lin)[index];
		(*lin)[index] = (*col)[index];
		(*col)[index] = aux2;
		(*a)[index] = aux;
	}
}

void task_R(int ****a, int *lin, int *col, int nr_matrix)
{
	int index, **mat, expo, i, j;

	scanf("%d %d", &index, &expo);
	if (index < 0 || index > nr_matrix - 1) {
		printf("No matrix with the given index\n");
	} else if (expo < 0) {
		printf("Power should be positive\n");
	} else if (lin[index] != col[index]) {
		printf("Cannot perform matrix multiplication\n");
	} else {
	    /* alocam memorie pentru matricea rezultat, pe care o initializam cu
	    elementul neutru al inmultirii matricelor, In */
		mat = create_mat(lin[index], col[index]);
		if (!mat) {
			task_Q(a, &lin, &col, nr_matrix);
			exit(-1);
		}
		/* construim elementrul neutrul al inmultirii*/
		for (i = 0; i < lin[index]; i++)
			for (j = 0; j < col[index]; j++) {
				if (i == j)
					mat[i][j] = 1;
				else
					mat[i][j] = 0;
			}

		while (expo) {
		    /* la fiecare putere para, a[index] devine patratul sau pentru a
		    asigura complexitatea logaritmica a algoritmului. Pentru puteriile
		    impare acesta operatie nu este posibila, deci inmultim matricea
			rezultat doar cu a[index] */
			if (expo % 2 == 1)
				power(&mat, (*a)[index], index, lin, col);
			power(&(*a)[index], (*a)[index], index, lin, col);

			/* cum expo este de tip int, putem imparti la 2 fara ca paritatea
			sa conteze (nu efectuam pasi suplimentari) */
			expo /= 2;
		}

		/* eliberam zona de memorie inainte de a inlocui a[index] cu
		matricea rezultat */
		for (i = 0; i < lin[index]; i++)
			free((*a)[index][i]);
		free((*a)[index]);
		(*a)[index] = mat;
	}
}

void task_F(int ****a, int *nr_matrix, int **lin, int **col)
{
	int index, i;

	scanf("%d", &index);
	if (index < 0 || index > (*nr_matrix) - 1) {
		printf("No matrix with the given index\n");
	} else {
	    /* eliberam vectorii ce pointeaza spre liniile matricei, apoi zona
	    de memorie alocata acesteia. Vectorii de dimensiune nu mai sunt
		necesari, iar numarul de matrice se micsoreaza. Pentru a nu avea
		discontinuitati in memorie, deplasam cu o pozitie la stanga elementele
		ce urmeaza dupa matricea de pe pozitia index*/
		for (i = 0; i < (*lin)[index]; i++)
			free((*a)[index][i]);
		free((*a)[index]);

		for (i = index; i < (*nr_matrix) - 1; i++)	{
			(*a)[i] = (*a)[i + 1];
			(*lin)[i] = (*lin)[i + 1];
			(*col)[i] = (*col)[i + 1];
		}
		(*nr_matrix)--;

		/* realocam memoria dupa eliminarea elementului din vectorul de matrice
		si vectorii de dimensiune */
		(*a) = (int ***)realloc((*a), (*nr_matrix) * sizeof(int **));
		(*lin) = (int *)realloc((*lin), (*nr_matrix) * sizeof(int));
		(*col) = (int *)realloc((*col), (*nr_matrix) * sizeof(int));
	}
}

void task_Q(int ****a, int **lin, int **col, int nr_matrix)
{
	int i, j;

    /* eliberarea tuturor resurselor */
	for (i = 0; i < nr_matrix; i++) {
		for (j = 0; j < (*lin)[i]; j++) {
			free((*a)[i][j]);
			(*a)[i][j] = NULL;
			}
		free((*a)[i]);
		(*a)[i] = NULL;
	}

	free((*a));
	(*a) = NULL;
	free((*lin));
	(*lin) = NULL;
	free((*col));
	(*col) = NULL;
}

