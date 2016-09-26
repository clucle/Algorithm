#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 8765432
#define MAX_V 20001

/*adj에 넣기 위함.. <다음노드번호,가중치> */
typedef pair<int, int> adjpoint;
/*dist, node*/
typedef pair<int, int> point;
/*[ ] 는 사이즈 안 정해진 벡터가
그 만큼 있다는 것임. 즉 2차원 배열*/
vector<adjpoint> adj[MAX_V];

int main() {
	int V, E;
	cin >> V >> E;
	int K;//start
	cin >> K;

	/*
	입력 식
	5 6
	1
	5 1 1
	1 2 2
	1 3 3
	2 3 4
	2 4 5
	3 4 6

	결과
	0
	2
	3
	7
	INF

	*/


	/*adjp에 연결 관계 및 가중치 정보 입력*/
	for (int i = 0; i < E; ++i) {
		int s, e, w;
		cin >> s >> e >> w;
		adj[s].push_back(adjpoint(e, w));
	}

	/*(최종) start에서 각 노드까지 거리*/
	vector<int> dist(V + 1, INF);//1번노드부터 V개니까 V+1개
	dist[K] = 0;

	/*
	5 1 1 -> adj[5][0] = <1,1>
	1 2 2 -> adj[1][0] = <2,2>
	1 3 3 -> adj[1][1] = <3,3>
	2 3 4 -> adj[2][0] = <3,4>
	2 4 5 -> adj[2][1] = <4,5>
	3 4 6 -> adj[3][0] = <4,6>
	
	*/



	
	priority_queue <point> pq;
	pq.push(point(0, K));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		/*만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면
		지금 꺼낸 것을 무시한다. 만약 1->2노드 가중치가 3이어서
		pq에 넣었는데 그다음에 3->2노드가 가중치가 2였으면
		1->2노드 경우는 무시되어야 한다. dist[2]는 2일테고
		pq안의 1->2노드가 가지고 있는 cost는 3이기 때문이다*/
		if (cost > dist[here])continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (nextDist < dist[there]) {
				dist[there] = nextDist;
				pq.push(point(-nextDist, there));
			}
		}

	}

	for (int i = 1; i <= V; ++i) {
		if (dist[i] == INF)cout << "INF" << endl;
		else cout << dist[i] << endl;
	}

	
	system("pause");
	return 0;
}