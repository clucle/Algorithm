#include <stdio.h>
#include <stdlib.h>

inline int max(int x, int y) {
	return (x>y?x:y);
}

typedef struct Node {
	int y;
	int x;
	int depth;
	struct Node* next;
}Node;

int main() {
	int M, N;
	
	scanf("%d %d", &M, &N);
	int i, j;
	
	int** arr;
	arr = (int**)malloc(sizeof(int*) * (N + 2));
	for (i = 0; i < N + 2; i++) {
		arr[i] = (int*)malloc(sizeof(int) * (M + 2));
	}
	
	for (i = 0; i <= M + 1; i++) {
		arr[0][i] = -1;
		arr[N + 1][i] = -1;
	}
	for (i = 0; i <= N + 1; i++) {
		arr[i][0] = -1;
		arr[i][M+1] = -1;
	}
	
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	Node* end;
	
	for (i = 1; i < N + 1; i++) {
		for (j = 1; j < M + 1; j++) {
			scanf("%d", &arr[i][j]);
			
			if (arr[i][j] == 1) {
				Node* tmp = (Node*)malloc(sizeof(Node));
				tmp->x = j;
				tmp->y = i;
				tmp->depth = 0;
				tmp->next = NULL;
				if (head->next == NULL) {
					head->next = tmp;
					end = tmp;
				} else {
					end->next = tmp;
					end = end->next;
				}
			}
		}
	}
	
	if (head->next == NULL) {
		printf("0");
		return 0;
	}
	
	while (head != end) {
		head = head->next;
		int x = head->x;
		int y = head->y;
		
		if (arr[y-1][x] == 0) {
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->y = y-1;
			tmp->x = x;
			tmp->depth = head->depth + 1;
			tmp->next = NULL;
			
			arr[y-1][x] = tmp->depth;
			
			end->next = tmp;
			end = end->next;
		}
		
		if (arr[y+1][x] == 0) {
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->y = y+1;
			tmp->x = x;
			tmp->depth = head->depth + 1;
			tmp->next = NULL;
			
			arr[y+1][x] = tmp->depth;
			
			end->next = tmp;
			end = end->next;
		}
		
		if (arr[y][x - 1] == 0) {
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->y = y;
			tmp->x = x - 1;
			tmp->depth = head->depth + 1;
			tmp->next = NULL;
			
			arr[y][x - 1] = tmp->depth;
			
			end->next = tmp;
			end = end->next;
		}
		
		if (arr[y][x + 1] == 0) {
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->y = y;
			tmp->x = x + 1;
			tmp->depth = head->depth + 1;
			tmp->next = NULL;
			
			arr[y][x + 1] = tmp->depth;
			
			end->next = tmp;
			end = end->next;
		}
	}
	
	
	int result = 0;
	for (i = 1; i < N + 1; i++) {
		for (j = 1; j < M + 1; j++) {
			if (arr[i][j] == 0) {
				printf("-1");
				return 0;
			}
			result = max(result, arr[i][j]);
		}
	}
	printf("%d", result);
	
	return 0;
}


