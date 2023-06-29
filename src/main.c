#include <stdio.h>
#include <stdlib.h>

#include "sparse.h"
#include "queue.h"

void explore(struct Triplet* T, int index) {
	int* curr_edge = get_edge(T, index);

	if (curr_edge[2] == 2) { return; }
	printf("%d: %d %d %d\n", index, curr_edge[0], curr_edge[1], curr_edge[2]);

	int num_row = num_in_row(T, curr_edge[0], index);

	if (num_row == 0) { return; }

	for (int i = 0; i < num_row; i++) {
		int next_node = find_row_index(T, T->col[i + index]);
		T->val[i + index] = 2;
		explore(T, next_node);
	}
}

int main(void) {
	int nodes = 9;
	int edges = 16;

	struct Triplet T = read_triplet("../data/nick/clean.csv", nodes, nodes, edges);

	//struct CSR graph = Triplet_to_CSR(&T);
	//destroy_Triplet(&T);
	//print_CSR(&graph);

	int count = 0;

	while (T.nz != 0) {
		int curr_index = index_first_unexplored(&T);
		if (curr_index == -1) { break; }
		explore(&T, curr_index);
		printf("HERE\n");
		count++;
	}

	printf("\n\n%d\n", count);

	return 0;
}
