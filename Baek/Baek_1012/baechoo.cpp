#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node {
	int x, y;
	Node* next;
}Node;

int map[52][52];
	

void DSP(int x, int y) {
	map[x][y] = 0;
	if (x > 0 && map[x-1][y] == 1) DSP(x-1, y);
	if (y > 0 && map[x][y - 1] == 1) DSP(x, y-1);
	if (map[x+1][y] == 1) DSP(x+1, y);
	if (map[x][y+1] == 1) DSP(x, y+1);
}

int main() {
	int N;
	scanf("%d", &N);
	
	int X, Y, K;

	int i;
	for (i = 0; i < N; i++) {
		
		Node* stack = (Node*)malloc(sizeof(Node));
		stack->x = -1;
		stack->y = -1;
		stack->next = NULL;
		
		scanf("%d%d%d",&X, &Y, &K);	
		int x, y;
		X++;Y++;
		for (x = 0; x < X; x++) {
			for (y = 0; y < Y; y++) {
				map[x][y] = 0;
			}
		}
		
		int k;
		for (k = 0; k < K; k++) {
			scanf("%d%d", &x, &y);
			Node* tmp = (Node*)malloc(sizeof(Node));
			tmp->x = x;
			tmp->y = y;
			tmp->next = stack->next;
			
			stack->next = tmp;
			
			map[x][y] = 1;
		}
		
		
		int result = 0;
		while (stack->next != NULL) {
			Node* delNode = stack;
			stack = stack->next;
			
			int px = stack->x;
			int py = stack->y;
			if (map[px][py] == 1) {
				result++;
				DSP(px, py);
			}
			
			free(delNode);
		}
		printf("%d\n", result);
		
	}
	
	
}
