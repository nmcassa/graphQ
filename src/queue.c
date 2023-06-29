#include "queue.h"

void init_Queue(struct Queue* A, int size) {
	A->size = size;
	A->front = 0;
}

int* dequeue(struct Queue* A, struct Triplet* T) {
	if (is_empty(A)) {
		printf("failure");
		return get_edge(T, A->front - 1);
	}
	A->front++;

	return get_edge(T, A->front - 1);
}

int is_empty(struct Queue* A) {
	if (A->front == A->size) {
		return 1;
	}
	return 0;
}

int num_in_row(struct Queue *A, struct Triplet* T, int row) {
	int count = 0;
	for (int i = A->front; i < A->size; i++) {
		if (T->row[i] == row) {
			count++;
		}
	}
	return count;
}
