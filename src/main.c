#include <stdio.h>
#include <stdlib.h>

#include "sparse.h"

int main(void) {
	int nodes = 29;
	int edges = 43;

	struct Triplet T = read_triplet("../data/bn-mouse-cortex/clean.csv", nodes, nodes, edges);

	struct CSR graph = Triplet_to_CSR(&T);

	destroy_Triplet(&T);

	print_CSR(&graph);

	//for 

	return 0;
}
