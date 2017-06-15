#include <stdio.h>

typedef struct {
	unsigned int data[100001];
	int last_index;
}Heap;

void delete_heap(Heap* heap);
void insert_heap(Heap* heap, unsigned int d);

int main() {
	int N;
	scanf("%d", &N);
	
	Heap heap;
	int i;
	
	for (i = 0; i < N + 1; i++) {
		heap.data[i] = 0;
	}
	heap.last_index = 0;
	
	
	int input;
	for (i = 0; i < N; i++) {
		scanf("%d", &input);
		
		if (input == 0) {
			delete_heap(&heap);
		} else {
			insert_heap(&heap, input);
		}
		
		/*
		printf("\n");
		int k;
		for (k = 1; k < heap.last_index + 1; k++) {
			printf("%d ", heap.data[k]);
		}
		printf("\n");
		*/
	}
	return 0;
}

void delete_heap(Heap* heap) {
	
	if (heap->last_index == 0) {
		printf("0\n");
		return ;
	}
	
	//printf("%d   %d    %d    \n", heap->data[1], heap->data[2], heap->data[3]);
	printf("%d\n", heap->data[1]);
	
	int saved = heap->data[heap->last_index];
	heap->data[heap->last_index] = 0;
	heap->last_index--;
	
	int parent = 1;
	int child = 2;
	
	while (child <= heap->last_index) {
		if (heap->data[child] < heap->data[child + 1]) {
			child++;
		}
		if (heap->data[child] < saved) {
			break;
		}
		
		heap->data[parent] = heap->data[child];
		parent = child;
		child *=2;
	}
	heap->data[parent] = saved;
}

void insert_heap(Heap* heap, unsigned int d) {
	int index = ++(heap->last_index);
	
	if (index == 1) {
		heap->data[1] = d;
		return ;
	}
	
	
	
	while ((index != 1) && (heap->data[index / 2] < d)) {
		heap->data[index] = heap->data[index / 2];
		index /= 2;
	}
	
	heap->data[index] = d;
}

