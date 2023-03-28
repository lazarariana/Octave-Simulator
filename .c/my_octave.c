//Copyright Ariana-Maria Lazar-Andrei 312CAb 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "functions.h"
#define R 10007

int main(void)
{
	int nr_matrix = 0, ***a, *lin, *col;
	char ch;
	while (scanf("%c", &ch) && ch != 'Q') {
		switch (ch) {
		case 'L':
			task_L(&a, &nr_matrix, &lin, &col);
			break;

		case 'D':
			task_D(lin, col, nr_matrix);
			break;

		case 'P':
			task_P(a, lin, col, nr_matrix);
			break;

		case 'C':
			task_C(&a, &lin, &col, nr_matrix);
			break;

		case 'S':
		case 'M':
			task_M(&a, &nr_matrix, &lin, &col);
			break;

		case 'O':
			task_O(a, lin, col, nr_matrix);
			break;

		case 'T':
			task_T(&a, nr_matrix, &lin, &col);
			break;

		case 'R':
			task_R(&a, lin, col, nr_matrix);
			break;

		case 'F':
			task_F(&a, &nr_matrix, &lin, &col);
			break;

		default:
		    /* alte situatii */
			if (!strchr("\n ", ch))
				printf("Unrecognized command\n");
		}
	}

	/* eliberarea tuturor resurselor */
	task_Q(&a, &lin, &col, nr_matrix);

	return 0;
}
