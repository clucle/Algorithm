#include <stdio.h>
#include <stdlib.h>

int Map[100][100];
int N, M;

typedef struct Node Node;
typedef struct Node {
	int x, y, distance;
	Node* link;
}Node;

typedef struct Queue Queue;
typedef struct Queue {
	Node* head;
	Node* rear;
}Queue;

void bfs();

int main() {
	
	scanf("%d %d", &N, &M);	
	int i, j;
	for(i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			scanf("%1d", &Map[i][j]);
		}
	}
	
	// if (Map[0][0] == '1') printf("A");
	bfs();
	// M-1, M-1
	/*
	for(i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			printf("%d ", Map[i][j]);
		}
		printf("\n");
	}
	*/
	printf("%d", Map[N - 1][M - 1] - 1);
	

}

void bfs() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	
	queue->head = (Node*)malloc(sizeof(Node));
	queue->head->y = 0;
	queue->head->x = 0;
	queue->head->distance = 2;
	queue->head->link = NULL;
	
	queue->rear = queue->head;

	int x, y;
	while (queue->head != NULL) {
		int y = queue->head->y;
		int x = queue->head->x;
		int distance = queue->head->distance;
		//printf("y: %d x: %d\n", y, x);
		if (Map[y][x] == 1) {
			Map[y][x] = distance;
			
			if (y > 0 && Map[y-1][x] == 1) {
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->y = y-1;
				newNode->x = x;
				newNode->distance = distance + 1;
				newNode->link = NULL;
				
				queue->rear->link = newNode;
				queue->rear = queue->rear->link;
			}
			
			if (y + 1 < N && Map[y+1][x] == 1) {
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->y = y+1;
				newNode->x = x;
				newNode->distance = distance + 1;
				newNode->link = NULL;
				
				queue->rear->link = newNode;
				queue->rear = queue->rear->link;
			}
			if (x > 0 && Map[y][x - 1] == 1) {
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->y = y;
				newNode->x = x - 1;
				newNode->distance = distance + 1;
				newNode->link = NULL;
				
				queue->rear->link = newNode;
				queue->rear = queue->rear->link;
			}
			if (x + 1 < M && Map[y][x + 1] == 1) {
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->y = y;
				newNode->x = x + 1;
				newNode->distance = distance + 1;
				newNode->link = NULL;
				
				queue->rear->link = newNode;
				queue->rear = queue->rear->link;
			}
		}
		
		Node* tmp = queue->head;
		queue->head = queue->head->link;
		free(tmp);
		
	}
	
}
