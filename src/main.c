#include <stdio.h>
#include <stdlib.h>

#include "sparse.h"
#include "queue.h"

int main(void) {
	int nodes = 29;
	int edges = 43;

	struct Triplet T = read_triplet("../data/bn-mouse-cortex/clean.csv", nodes, nodes, edges);

	//struct CSR graph = Triplet_to_CSR(&T);
	//destroy_Triplet(&T);
	//print_CSR(&graph);

	struct Queue Q;
	init_Queue(&Q, edges);

	int ones = num_in_row(&Q, &T, T.row[Q.front]);
	int* first = dequeue(&Q, &T);
	int twos = num_in_row(&Q, &T, T.row[Q.front]);
	int* second = dequeue(&Q, &T);

	printf("%d %d %d:\t%d\n", first[0], first[1], first[2], ones);


	printf("%d %d %d:\t%d\n", second[0], second[1], second[2], twos);
	
	return 0;
}
