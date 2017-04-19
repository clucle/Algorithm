#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 8765432
#define MAX_V 20001

/*adj�� �ֱ� ����.. <��������ȣ,����ġ> */
typedef pair<int, int> adjpoint;
/*dist, node*/
typedef pair<int, int> point;
/*[ ] �� ������ �� ������ ���Ͱ�
�� ��ŭ �ִٴ� ����. �� 2���� �迭*/
vector<adjpoint> adj[MAX_V];

int main() {
	int V, E;
	cin >> V >> E;
	int K;//start
	cin >> K;

	/*
	�Է� ��
	5 6
	1
	5 1 1
	1 2 2
	1 3 3
	2 3 4
	2 4 5
	3 4 6

	���
	0
	2
	3
	7
	INF

	*/


	/*adjp�� ���� ���� �� ����ġ ���� �Է�*/
	for (int i = 0; i < E; ++i) {
		int s, e, w;
		cin >> s >> e >> w;
		adj[s].push_back(adjpoint(e, w));
	}

	/*(����) start���� �� ������ �Ÿ�*/
	vector<int> dist(V + 1, INF);//1�������� V���ϱ� V+1��
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

		/*���� ���� ���� �ͺ��� �� ª�� ��θ� �˰� �ִٸ�
		���� ���� ���� �����Ѵ�. ���� 1->2��� ����ġ�� 3�̾
		pq�� �־��µ� �״����� 3->2��尡 ����ġ�� 2������
		1->2��� ���� ���õǾ�� �Ѵ�. dist[2]�� 2���װ�
		pq���� 1->2��尡 ������ �ִ� cost�� 3�̱� �����̴�*/
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