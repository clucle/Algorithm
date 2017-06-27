#include <stdio.h>
#include <stdlib.h>

inline int max(int x, int y) { return (x>y?x:y); }

typedef struct Node Node;
typedef struct Node {
	int x;
	int y;
	int height;
	int day;
	Node* next;
} Node;

typedef struct Queue Queue;
typedef struct Queue {
	Node* front;
	Node* rear;
} Queue;

void dequeue(Queue* q) {
	if (q == NULL) return ;
	Node* delNode = q->front;
	q->front = q->front->next;
	free(delNode);
}

void enqueue(Queue* q, int height, int y, int x, int day) {
	Node* tmpNode = (Node*)malloc(sizeof(Node));
	tmpNode->height = height;
	tmpNode->y = y;
	tmpNode->x = x;
	tmpNode->day = day;
	tmpNode->next = NULL;
	
	if (q->rear == NULL) {
		q->front = tmpNode;
		q->rear = tmpNode;
	} else {
		q->rear->next = tmpNode;
		q->rear = q->rear->next;
	}
}

int main() {
	int x, y, height;
	int*** map;
	
	scanf("%d %d %d", &x, &y, &height);
	
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	
	
	int i, j, k;
	
	int cnt = 0;
	
	map = (int***)malloc(sizeof(int**) * (height + 2));
	for (i = 0; i < height + 2; i++) {
		map[i] = (int**)malloc(sizeof(int*) * (y + 2));
		for (j = 0; j < y + 2; j++) {
			map[i][j] = (int*)malloc(sizeof(int) * (x + 2));
		}
	}
	
	for (k = 1; k < height + 1; k++) {
		for (i = 0; i < y + 2; i++) {
			map[k][i][0] = -1;
			map[k][i][x + 1] = -1;
		}
		for (j = 0; j < x + 2; j++) {
			map[k][0][j] = -1;
			map[k][y + 1][j] = -1;
		}
		
		for (i = 1; i < y + 1; i++) {
			for (j = 1; j < x + 1; j++) {
				scanf("%d", &map[k][i][j]);
				if (map[k][i][j] == 1)  {
					enqueue(q, k, i, j, 0);
					cnt++;
				}
			}
		}
	}
	
	for (i = 0; i < y + 2; i++) {
		for (j = 0; j < x + 2; j++) {
			map[0][i][j] = -1;
			map[height+1][i][j] = -1;
		}
	}
	
	int result = -1;
	
	int isEnd;
	if (q->front == NULL) {
		isEnd = 1;
	} else {
		isEnd = 0;
	}

	if (cnt == height * x * y) {
		while(q->front != NULL) {
			dequeue(q);
		}
		result = 0;
		isEnd = 1;
	} else {
		while(q->front != NULL) {
			int mheight, my, mx, mday;
			mheight = q->front->height;
			my = q->front->y;
			mx = q->front->x;
			mday = q->front->day;
			
			if (map[mheight - 1][my][mx] == 0) {
				map[mheight - 1][my][mx] = mday + 1;
				enqueue(q, mheight - 1, my, mx, mday + 1);
			}
			if (map[mheight + 1][my][mx] == 0) {
				map[mheight + 1][my][mx] = mday + 1;
				enqueue(q, mheight + 1, my, mx, mday + 1);
			}
			
			if (map[mheight][my - 1][mx] == 0) {
				map[mheight][my - 1][mx] = mday + 1;
				enqueue(q, mheight, my - 1, mx, mday + 1);
			}
			if (map[mheight][my + 1][mx] == 0) {
				map[mheight][my + 1][mx] = mday + 1;
				enqueue(q, mheight, my + 1, mx, mday + 1);
			}
			
			if (map[mheight][my][mx - 1] == 0) {
				map[mheight][my][mx - 1] = mday + 1;
				enqueue(q, mheight, my, mx - 1, mday + 1);
			}
			if (map[mheight][my][mx + 1] == 0) {
				map[mheight][my][mx + 1] = mday + 1;
				enqueue(q, mheight, my, mx + 1, mday + 1);
			}
			dequeue(q);
		}
	
	}
	
	if (isEnd == 1) {
		
	} else {
		for (k = 1; k < height + 1; k++) {
			for (i = 1; i < y + 1; i++) {
				for (j = 1; j < x + 1; j++) {
					if (map[k][i][j] != -1) result = max(result, map[k][i][j]);
					if (map[k][i][j] == 0) {
						k = height + 1;
						i = y + 1;
						j = x + 1;
						result = -1;
						break;
					}
				}
			}
		}
	}
	

	for (k = 0; k < height + 2; k++) {
		for (i = 0; i < y + 2; i++) {
			free(map[k][i]);
		}
	}
	for (k = 0; k < height + 2; k++) {
		free(map[k]);
	}
	free(map);
	
	printf("%d", result);
	return 0;
}
