#ifndef Queue_
#define Queue_

#include "sparse.h"

struct Queue {
	int front;
	int size;
};

void init_Queue(struct Queue* A, int size);
int* dequeue(struct Queue* A, struct Triplet* T);

int is_empty(struct Queue* A);
int num_in_row(struct Queue *A, struct Triplet* T, int row);

#endif
