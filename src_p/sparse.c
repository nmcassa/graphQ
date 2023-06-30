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

void destroy_Triplet(struct Triplet *A) {
	free(A->row);
	free(A->col);
	free(A->val);
}

struct CSR Triplet_to_CSR(struct Triplet *A) {
	struct CSR ret;

	ret.n = A->n;
	ret.m = A->m;
	ret.nz = A->nz;

	ret.rowPtr = (int *) malloc(sizeof(int) * (ret.n + 1));
	ret.colIndex = (int *) malloc(sizeof(int) * ret.nz);
	ret.val = (int *) malloc(sizeof(int) * ret.nz);

	int *rowCounter = (int *) malloc(sizeof(int) * ret.n);
	for (int i = 0; i < ret.n; i++) {
		rowCounter[i] = 0;
	}

	for (int i = 0; i < ret.nz; i++) { //number of nonzeros in each row
		rowCounter[A->row[i]]++;
	}

	ret.rowPtr[0] = 0;
	for (int i = 0; i < ret.n; i++) { 
		ret.rowPtr[i + 1] = ret.rowPtr[i] + rowCounter[i];
	}

	int currRow;
	int index;
	for (int i = 0; i < ret.nz; i++) {
		currRow = A->row[i];
		index = ret.rowPtr[currRow]++;

		ret.val[index] = A->val[i];
		ret.colIndex[index] = A->col[i];
	}

	for (int i = ret.n; i > 0; i--) {
		ret.rowPtr[i] = ret.rowPtr[i - 1];
	}
	ret.rowPtr[0] = 0;

	free(rowCounter);

	return ret;
}
