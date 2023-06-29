#include "sparse.h"

struct Triplet read_triplet(const char *filename, int rows, int cols, int numNonZeros) {
	FILE *file = fopen(filename, "r");

	struct Triplet ret;

	ret.n = rows;
	ret.m = cols;
	ret.nz = numNonZeros;

	ret.row = (int *) malloc(sizeof(int) * ret.nz);
	ret.col = (int *) malloc(sizeof(int) * ret.nz);
	ret.val = (int *) malloc(sizeof(int) * ret.nz);

	int num;	
	for (int i = 0; i < numNonZeros; i++) {
		num = fscanf(file, "%d,%d,%d/n", &ret.row[i], &ret.col[i], &ret.val[i]);
		if (num != 3) {
			printf("ERROR");
			exit(1);
		}
	}

	fclose(file);

	return ret;
}

int index_first_unexplored(struct Triplet *A) {
	for (int i = 0; i < A->nz; i++) {
		if (A->val[i] == 1) {
			return i;
		}
	}
	return -1;
}

int find_row_index(struct Triplet* T, int col) {
	for (int i = 0; i < T->nz; i++) {
		if (T->row[i] == col) {
			return i;
		}
	}
	return -1;
}

void destroy_Triplet(struct Triplet *A) {
	free(A->row);
	free(A->col);
	free(A->val);
}
