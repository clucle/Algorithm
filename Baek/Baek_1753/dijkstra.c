#include <stdio.h>
#include <stdlib.h>

#define INF 9999999

typedef struct Node Node;
typedef struct Node{
	int to;
	int distance;
	Node* next;
} Node;

typedef struct heapNode {
	int to;
	int distance;
}heapNode;

typedef struct HEAP {
	heapNode data[300001];
	int lastIndex;
}HEAP;



heapNode delete_heap(HEAP* heap) {
	
	if (heap->lastIndex == 0) {
		return ;
	}
	
	heapNode h;
	h.distance = heap->data[1].distance;
	h.to = heap->data[1].to;
	
	//int p;
	//for (p = 0; p < 10; p++) {
		//printf("heap->data[%d]   to = %d   distance = %d\n", p, heap->data[p].to, heap->data[p].distance);
	//}
	
	
	
	heapNode saved = heap->data[heap->lastIndex];
	heap->data[heap->lastIndex].distance = 0;
	heap->data[heap->lastIndex].to = 0;
	
	heap->lastIndex--;
	
	int parent = 1;
	int child = 2;
	
	while (child <= heap->lastIndex) {
		if (heap->data[child].distance > heap->data[child + 1].distance) {
			if (heap->data[child + 1].distance != 0){
				child++;
			}
			
		}
		if (heap->data[child].distance > saved.distance) {
			break;
		}
		
		heap->data[parent] = heap->data[child];
		parent = child;
		child *=2;
		
		
	}
	heap->data[parent] = saved;
	return h;
}

void inserte_heap(HEAP* heap, int to, int distance) {
	int index = ++(heap->lastIndex);
	if (index == 1) {
		heap->data[1].distance = distance;
		heap->data[1].to = to;
		return ;
	}
	
	while ((index != 1) && (heap->data[index / 2].distance > distance)) {
		heap->data[index] = heap->data[index / 2];
		index /= 2;
	}
	//printf("heap->data[%d]   to = %d   distance = %d\n", index, to, distance);
	//printf("heap->data[%d]   to = %d   distance = %d\n", index + 1, to + 1, distance + 1);
	heap->data[index].distance = distance;
	heap->data[index].to = to;
}

int main() {
	
	int result_dist[300001];
	
	int V, E;
	scanf("%d %d", &V, &E);
	
	int K;
	scanf("%d", &K);
	
	int i;
	
	int start, end, distance;
	
	Node* edge[300001];
	
	for (i = 1; i < V + 1; i++) {
		edge[i] = (Node*)malloc(sizeof(Node));
		edge[i]->next = NULL;
		
		result_dist[i] = INF;
	}
	
	for (i = 0; i < E; i++) {
		scanf("%d %d %d", &start, &end, &distance);
		
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->to = end;
		tmp->distance = distance;
		
		tmp->next = edge[start]->next;
		edge[start]->next = tmp;
	}
	HEAP heap;
	heap.lastIndex = 0;
	for (i = 0; i < E; i++) {
		heap.data[i].distance = 0;
		heap.data[i].to = 0;
	}
	
	inserte_heap(&heap, K, 0);
	
	while(heap.lastIndex != 0) {
		heapNode tmp = delete_heap(&heap);
		//printf("POP THIS : to // %d  dist // %d \n", tmp.to, tmp.distance);
		
		if (result_dist[tmp.to] > tmp.distance) {
			result_dist[tmp.to] = tmp.distance;
		} else {
			continue;
		}

		Node* insertNode = edge[tmp.to];
		insertNode = insertNode->next;
		while (insertNode != NULL) {
			//printf("Input %d %d\n", insertNode->to, insertNode->distance + result_dist[tmp.to]);
			inserte_heap(&heap, insertNode->to, insertNode->distance + result_dist[tmp.to]);
			insertNode = insertNode->next;
			
		}
	}
	
	
	
	for (i = 1; i < V + 1; i++) {
		if (result_dist[i] != INF) printf("%d\n", result_dist[i]);
		else printf("INF\n");
		free(edge[i]);
	}

	return 0;
}
