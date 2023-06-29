#ifndef CSR_H
#define CSR_H

/*             ***CSR***
		1  0  2
	     	0  3  0
	     	4  0  5
	     	6  7  0

	     	n = 4;
	     	m = 3;
	     	nz = 7;

     val      = [1, 2, 3, 4, 5, 6, 7];  size = [nz]
     colIndex = [0, 2, 1, 0, 2, 0, 1];  size = [nz]
     rowPtr   = [0, 2, 3, 5, 7];        size = [n + 1]

     val holds the numbers in the non-zero indices

     colIndex holds the column of each of the vals

     rowPtr[i] - rowPtr[i - 1] is the amount of values in each row i + 1

     		ex --> row[0] = rowPtr[1] - rowPtr[0]
		       row[0] =    2      -     0

	Therefore there are two values and two colIndices in this row
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct CSR {
	int n; //num rows
	int m; //num cols
	int nz; //num non-zero
	
	int* val; //non-zero values
	int* colIndex; // column indices
	int* rowPtr; //row ptrs
};

struct Triplet { //csv:    0, 0, 1   ==   [0, 0] = 1
	int n;
	int m;
	int nz;

	int* val;
	int* col;
	int* row;
};

void init_CSR(struct CSR *A, int* vals, int* colIndex, int* rowPtr, int n, int m, int nz);
void print_CSR(struct CSR *A);
void destroy_CSR(struct CSR *A);

struct Triplet read_triplet(char *filename, int rows, int cols, int numNonZeros);
void destroy_Triplet(struct Triplet *A);
int* get_edge(struct Triplet *A, int index);

struct CSR Triplet_to_CSR(struct Triplet *A);

#endif
