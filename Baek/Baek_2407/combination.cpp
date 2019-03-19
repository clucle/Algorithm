#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> v;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int board[101];
int rest[101];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, r;
	cin >> n >> r;
	// n! / r! (n - r)!
	int mymin = min(r, n - r);
	v.resize(200);
	for (int i = 1; i <= 200; i++) {
		v[i] = 0;
	}
	v[0] = 1;

	for (int i = 1; i <= mymin; i++) {
		board[i] = n - i + 1;
		rest[i] = i;
	}

	for (int i = 1; i <= mymin; i++) {
		for (int j = 1; j <= mymin; j++) {
			if (rest[i] == 1) break;
			int g = gcd(board[j], rest[i]);
			if (g > 1) {
				board[j] /= g;
				rest[i] /= g;
			}
		}
	}

	for (int i = 1; i <= mymin; i++) {
		int pos = 0;
		vector<int> newV;
		newV.resize(200);
		for (int i = 0; i < 200; i++) {
			newV[i] = 0;
		}
		int size = 0;
		for (int j = 200; j >= 0; j--) {
			if (v[j] != 0)  {
				size = j;
				break;
			}
		}

		while (board[i] > 0) {
			int curNum = board[i] % 10;
			board[i] /= 10;
			if (curNum == 0) {
				pos++;
				continue;
			}
			vector<int> tmpV;
			tmpV.resize(200);
			for (int j = 0; j < 200; j++) {
				tmpV[i] = 0;
			}

			int bonus = 0;
			int s;
			for (s = 0; s <= size; s++) {
				int here = curNum * v[s] + bonus;
				bonus = here / 10;
				tmpV[s + pos] = here % 10;
			}
			if (bonus > 0) {
				tmpV[s + pos] = bonus;
			}
			for (int j = 0; j < 200; j++) {
				newV[j] += tmpV[j];
				newV[j + 1] += newV[j] / 10;
				newV[j] %= 10;
			}
			pos++;
		}

		for (int p = 0; p < 200; p++) {
			v[p + 1] += newV[p] / 10;
			v[p] = newV[p] % 10;
		}
	}
	int size = 0;
	for (int j = 200; j >= 0; j--) {
		if (v[j] != 0)  {
			size = j;
			break;
		}
	}
	for (int s = size; s >= 0; s--) {
		cout << v[s];
	}
}

// 2407 combination