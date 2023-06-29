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

struct Triplet read_triplet(const char *filename, int rows, int cols, int numNonZeros);
void destroy_Triplet(struct Triplet *A);

int find_row_index(struct Triplet* T, int col);
int index_first_unexplored(struct Triplet *A);

#endif
