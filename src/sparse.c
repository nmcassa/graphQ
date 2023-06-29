#include "sparse.h"

void init_CSR(struct CSR* A, int* vals, int* colIndex, int* rowPtr, int n, int m, int nz) {
	A->n = n;
	A->m = m;
	A->nz = nz;

	A->val = (int *) malloc(sizeof(int) * nz);
	A->colIndex = (int *) malloc(sizeof(int) * nz);
	A->rowPtr = (int *) malloc(sizeof(int) * (n + 1));

	memcpy(A->val, vals, sizeof(int) * nz);
	memcpy(A->colIndex, colIndex, sizeof(int) * nz);
	memcpy(A->rowPtr, rowPtr, sizeof(int) * (n + 1));
}

void print_CSR(struct CSR* A) {
	int* B = (int *) malloc(sizeof(int) * A->n * A->m);

	for(int i = 0; i < A->n * A->m; i++) {
		B[i] = 0;
	}

	for (int i = 0; i < A->n; i++) {
		for (int j = A->rowPtr[i]; j < A->rowPtr[i + 1]; j++) {
			B[i * A->m + A->colIndex[j]] = A->val[j];
		}
	}

	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			printf("%d\t", B[i * A->m + j]);
		}
		printf("\n");
	}

	free(B);
}

void destroy_CSR(struct CSR* A) {
	free(A->val);
	free(A->colIndex);
	free(A->rowPtr);
}

struct Triplet read_triplet(char *filename, int rows, int cols, int numNonZeros) {
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

int* get_edge(struct Triplet *A, int index) {
	int* ret = (int *) malloc(sizeof(int) * 3);
	ret[0] = A->row[index];
	ret[1] = A->col[index];
	ret[2] = A->val[index];
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
