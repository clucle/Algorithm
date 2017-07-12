#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node {
	int dest;
	Node* Node;
}Node;

Node** Vertex;
int* NodeDepth;
int* NodeParent;

void dfs(int here, int depth) {
	Node* tmpNode = Vertex[here]->Node;
	
	int there;
	while(tmpNode != NULL) {
		there = tmpNode->dest;
		if (NodeDepth[there] == -1) {
			NodeDepth[there] = depth + 1;
			NodeParent[there] = here;

			dfs(there, depth + 1);
		}
		tmpNode = tmpNode->Node;
	}
}

int lca(int a, int b) {
	if (NodeDepth[a] < NodeDepth[b]) {
		a += b;
		b = a - b;
		a -= b;
	}
	// a 쪽 depth가 더 깊음
	while (NodeDepth[a] != NodeDepth[b]) {
		a = NodeParent[a];
	}
	
	while(a != b) {
		a = NodeParent[a];
		b = NodeParent[b];
	}
	
	return a;
}

int main() {
	int N, i;
	scanf("%d", &N);
	
	N++;
	// 공간 할당 
	Vertex = (Node**)malloc(sizeof(Node) * N);
	for (i = 1; i < N; i++) {
		Vertex[i] = (Node*)malloc(sizeof(Node));
		Vertex[i]->dest = i;
		Vertex[i]->Node = NULL;
	}
	NodeDepth = (int*)malloc(sizeof(Node) * N);
	for (i = 1; i < N; i++) {
		NodeDepth[i] = -1;
	}
	NodeDepth[1] = 0;
	
	NodeParent = (int*)malloc(sizeof(Node) * N);
	for (i = 1; i < N; i++) {
		NodeParent[i] = -1;
	}
	NodeParent[1] = 0;
	
	N-=2;
	
	int a, b;
	for (i = 0; i < N; i++) {
		
		scanf("%d %d", &a, &b);
		
		Node* tmpNode = NULL;
		
		tmpNode = (Node*)malloc(sizeof(Node));
		tmpNode->dest = b;
		tmpNode->Node = Vertex[a]->Node;
		Vertex[a]->Node = tmpNode;
		
		tmpNode = (Node*)malloc(sizeof(Node));
		tmpNode->dest = a;
		tmpNode->Node = Vertex[b]->Node;
		Vertex[b]->Node = tmpNode;
	}
	
	dfs(1, 0);
	
	N+=2;
	
	int M;
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}
	
	// 공간 해제 
	for (i = 1; i < N; i++) {
		free(Vertex[i]);
	}
	free(Vertex);
	free(NodeDepth);
	
	
	return 1;
}
