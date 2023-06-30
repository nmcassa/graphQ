#ifndef CSR_H
#define CSR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Triplet { //csv:    0, 0, 1   ==   [0, 0] = 1
	int n;
	int m;
	int nz;

	int* val;
	int* col;
	int* row;
};

struct CSR {
	int n; //num rows
	int m; //num cols
	int nz; //num non-zero
	
	int* val; //non-zero values
	int* colIndex; // column indices
	int* rowPtr; //row ptrs
};

struct Triplet read_triplet(const char *filename, int rows, int cols, int numNonZeros);
void destroy_Triplet(struct Triplet *A);

struct CSR Triplet_to_CSR(struct Triplet *A);
#endif
