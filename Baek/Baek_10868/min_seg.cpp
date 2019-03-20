#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>


using namespace std;

int board[100001];

int init(vector<int> &tree, int here, int start, int end) {
	if (start == end) {
		return tree[here] = board[start];
	}
	else {
		return tree[here] = min(
			init(tree, here * 2, start, (start + end) / 2),
			init(tree, here * 2 + 1, (start + end) / 2 + 1, end)
		);
	}
}

int solve(vector<int> &tree, int here, int start, int end, int left, int right) {
	if (left > end || right < start) {
		return INT_MAX;
	}
	if (left <= start && end <= right) {
		return tree[here];
	}
	return min(
		solve(tree, here * 2, start, (start + end) / 2, left, right),
		solve(tree, here * 2 + 1, (start + end) / 2 + 1, end, left, right)
	);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> board[i];
	}
	int h = (int)ceil(log2(N));
	vector<int> tree(1 << (h + 1));
	init(tree, 1, 0, N - 1);

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cout << solve(tree, 1, 0, N - 1, a - 1, b - 1) << '\n';
	}
	
	return 0;
	
}

