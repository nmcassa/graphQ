#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "sparse.h"
}

#define NUM_ITER 1
#define STRIDE 2

__device__ void num_in_row(int* rows, int* vals, int row, int index, int* count, int size);

__global__ void fun(int* row, int* col, int* val, int size) {
	int index = threadIdx.x * STRIDE;
	for (int i = 0; i < NUM_ITER; i++) {
		int* curr_edge = (int *) malloc(sizeof(int) * 3);

		curr_edge[0] = row[index];
		curr_edge[1] = col[index];
		curr_edge[2] = val[index];

		int num_row = 0;
		num_in_row(row, val, curr_edge[0], threadIdx.x * STRIDE, &num_row, size);
		printf("%d: %d %d %d\n", num_row, curr_edge[0], curr_edge[1], curr_edge[2]);
	}
}

int main(void) {
	int nodes = 9;
	int edges = 15;

	struct Triplet T = read_triplet("../data/nick/clean.csv", nodes, nodes, edges);

	int count = 0;

	int *row, *col, *val;

	cudaMalloc(&row, edges * sizeof(int));
	cudaMalloc(&col, edges * sizeof(int));
	cudaMalloc(&val, edges * sizeof(int));

	cudaMemcpy(row, T.row, edges * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(col, T.col, edges * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(val, T.val, edges * sizeof(int), cudaMemcpyHostToDevice);

	int threads = nodes / STRIDE;
	fun<<<1, threads>>>(row, col, val, edges);
	cudaDeviceSynchronize();

	printf("\n\n%d\n", count);

	return 0;
}

__device__ void num_in_row(int* rows, int* vals, int row, int index, int* count, int size) {
	for (int i = index; i < size; i++) {
		if (rows[i] == row && vals[i] == 1) { //unexplored
			(*count)++;
		} else {
			break;
		}
	}
}


