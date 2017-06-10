#include <stdio.h>
#include <stdlib.h>

#define INF 999999

typedef struct Node Node;
typedef struct Node {
	int to;      // 갈 곳 
	int weight;  // 가중치
	Node* next;  // 다음 곳 
}Node;

typedef struct distNode distNode;
typedef struct distNode {
	int position;
	distNode* next;
}distNode;

int main() {
	// 최단 거리 저장 
	int dist[20001];
	
	// 최단거리 인 정점의 인덱스 저장 
	int index_dist[20001];
	int index_cnt[20001];
	
	// dist[INF][INF][0]   [2][3][INF]
	// inde[0]  [0]  [시작][1][2][INF] 
	// dist = 2 가 최소이므로 1과 연결 
	
	
	// 간선 저장 
	Node* E[20001];
	
	// 정점, 간선 갯수 
	int nV, nE; 
	scanf("%d %d", &nV, &nE);
	
	// 시작 위치 
	int start;
	scanf("%d", &start);
	
	int i;

	// 노드 초기화 
	for (i = 1; i < nV + 1; i++) {
		E[i] = (Node*)malloc(sizeof(Node));
		E[i]->next = NULL;
		
		// 거리 모두 못가게 만듬 
		dist[i] = INF;
		index_dist[i] = -1;
	}
	
	// 시작위치 거리 0 
	dist[start] = 0;
	index_dist[start] = start;
	
	
	int from, to, weight;
	for (i = 0; i < nE; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		// 노드 생성 
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->to = to;
		tmp->weight = weight;
		
		// 노드 삽입
		tmp->next = E[from]->next;
		E[from]->next = tmp;
	}
	
	/* ------ Logic --------*/	
	int pos = start;
	distNode* head = (distNode*)malloc(sizeof(distNode));
	head->next = NULL;
	
	while(1) {
		
		Node* iter = E[pos];
		int cnt;
		while (iter->next != NULL) {
			iter = iter->next;
			if (iter->weight + dist[pos] < dist[iter->to]) {
				if (dist[iter->to] == INF) dist[iter->to] = 0;
				dist[iter->to] = dist[pos] + iter->weight;
				
				distNode* disttmp = (distNode*)malloc(sizeof(distNode));
				disttmp->position = iter->to;
				disttmp->next = head->next;
				head->next = disttmp;
			}
		}
		
		int min = INF;
		int index_min = -1;
		// INF 아닌것들
		
		distNode* iterDist = head;
		int delcount;
		
		int count_del = 0;
		while (iterDist->next != NULL) {
			iterDist = iterDist->next;
			count_del++;
			if (min >= dist[iterDist->position]) {
				min = dist[iterDist->position];
				index_min = iterDist->position;
				delcount = count_del;
			}
		}
		
		iterDist = head;
		if (delcount > 0) {
			while (--delcount > 0) {
				iterDist = iterDist->next;
			}
			distNode* delDistNode = iterDist->next;
			iterDist->next = delDistNode->next;
			free(delDistNode);
		}
		
		if (index_min == -1) {
			break;
		} else {
			index_dist[index_min] = pos;
			pos = index_min;
		}
	}
	
	
	/*---------------------- */
	
	// 메모리 초기화 
	for (i = 1; i < nV + 1; i++) {
		while(E[i] != NULL) {
			Node* tmp = E[i];
			E[i] = E[i]->next;
			free(tmp);
		}
		free(E[i]);
	}
	
	//결과 출력 
	for (i = 1; i < nV + 1; i++) {
		if (dist[i] == INF) printf("INF\n");
		else printf("%d\n", dist[i]);
	}
	
	return 0;
}
