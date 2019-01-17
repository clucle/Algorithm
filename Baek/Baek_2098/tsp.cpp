#include <iostream>
#include <algorithm>

using namespace std;

int INF = 100000000;
// 1 <= N <= 16
int N;

// 2^16 - 1 = 65536
// dp[cur][visited]
int dp[16][65536];
int arr[16][16];

int tsp(int cur, int visited) {
	visited |= (1 << cur);
	if (visited == (1 << N) - 1) {
		if (arr[cur][0] == 0) return INF;
		else return arr[cur][0];
	}
	int& ret = dp[cur][visited];
	if (ret != 0) return ret;
	ret = INF;
	for (int i = 0; i < N; i++) {
		if (visited & (1 << i)) continue;
		if (arr[cur][i] == 0) continue;
		ret = min(ret, tsp(i, visited) + arr[cur][i]);
	}
	return ret;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	cout << tsp(0, 0);
}
