#include<iostream>
#include<vector>
#include<utility>
#include<queue>

using namespace std;

int visited[1010];
vector<pair<int , int> > v[1010];

struct node {
	int to;
	int dist;
};

bool operator<(node a, node b) {
	return a.dist > b.dist;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int n, m;
	cin >> n >> m;
	
	int a, b, c;
	for (int i = 1; i <= n; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}
	priority_queue<node> pq;
	node tmp;
	tmp.to = 1;
	tmp.dist = 0;
	pq.push(tmp);
	int result = 0;
	while (!pq.empty()) {
		node n = pq.top();
		pq.pop();
		int here = n.to;
		int dist = n.dist;
		if (visited[here]) continue;
		visited[here] = 1;
		result += dist;
		for (int i = 0; i < v[here].size(); i++) {
			if (!visited[v[here][i].first]) {
				node tmp;
				tmp.to = v[here][i].first;
				tmp.dist = v[here][i].second;
				pq.push(tmp);
			}
		}
	}
	cout << result;
	return 0;
}
