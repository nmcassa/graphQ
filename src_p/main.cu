#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "sparse.h"
}

#define NUM_ITER 2
#define STRIDE 2

__device__ void find_row_index(int* rows, int col, int size, int* ret);

__global__ void fun(int* row, int* col, int* val, int size) {
	int index = threadIdx.x;

	for (int i = row[index]; i < row[index + 1]; i++) { //go through each row
		for (int j = row[col[i]]; j < row[col[i] + 1]; j++) { //go to each column in that row
			if (val[j] > val[i]) { //check if the value held is larger
				val[j] = val[i];
			}
		}
	}
}

int main(void) {
	int nodes = 9;
	int edges = 15;

	struct Triplet T = read_triplet("../data/nick/clean.csv", nodes, nodes, edges);

	for (int i = 0; i < edges; i++) { //set all values to be their row
		T.val[i] = T.row[i];
		printf("[%d, %d]: %d\n", T.row[i], T.col[i], T.val[i]);
	}

	struct CSR C = Triplet_to_CSR(&T);
	destroy_Triplet(&T);

	int *row, *col, *val;

	cudaMalloc(&row, edges * sizeof(int));
	cudaMalloc(&col, edges * sizeof(int));
	cudaMalloc(&val, edges * sizeof(int));

	cudaMemcpy(row, C.rowPtr, (nodes + 1) * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(col, C.colIndex, edges * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(val, C.val, edges * sizeof(int), cudaMemcpyHostToDevice);

	//int threads = nodes;
	int threads = nodes;
	for (int i = 0; i < NUM_ITER; i++) {
		fun<<<1, threads>>>(row, col, val, edges);
		cudaDeviceSynchronize();
	}

	cudaMemcpy(C.val, val, edges * sizeof(int), cudaMemcpyDeviceToHost);

	for (int i = 0; i < edges; i++) {
		printf("%d ", C.val[i]);
	}
	printf("\n");
	
	return 0;
}

__device__ void find_row_index(int* rows, int col, int size, int* ret) {
	for (int i = 0; i < size; i++) {
		if (rows[i] == col) {
			(* ret) = i;
		}
	}
}
