#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>
#include <stack>
#include <cstring>

using namespace std;

using ll = long long;

int N;
int arr[101][101];

int board[101][101];

bool isValid(int r, int c)
{
	if (r < 1 || r > N || c < 1 || c > N)
		return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	std::set<int> s;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> arr[i][j];
			s.insert(arr[i][j]);
		}
	}

	int src = arr[1][1];
	int dst = arr[N][N];

	if (src > dst)
		swap(src, dst);
	// src < dst

	int rDiff[4] = {0, 0, 1, -1};
	int cDiff[4] = {1, -1, 0, 0};

	int best = 201;
	for (auto e : s)
	{
		int start = e;
		int end = 201; // end is already good

		if (start > src)
			break;

		while (start + 1 < end)
		{
			memset(board, 0, sizeof(board));
			int mid = start + (end - start) / 2;
			queue<pair<int, int>> q;
			if (e <= arr[1][1] && arr[1][1] <= mid)
			{
				q.push({1, 1});
				board[1][1] = 1;
			}

			while (!q.empty())
			{
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				if (r == N && c == N)
					break;

				for (int d = 0; d < 4; d++)
				{
					int nr = r + rDiff[d];
					int nc = c + cDiff[d];

					if (!isValid(nr, nc))
						continue;
					if (board[nr][nc])
						continue;
					if (e <= arr[nr][nc] && arr[nr][nc] <= mid)
					{
						q.push({nr, nc});
						board[nr][nc] = 1;
					}
				}
			}

			if (board[N][N])
			{
				best = min(best, mid - e);
				end = mid;
			}
			else
			{
				start = mid;
			}
		}

		//
		{
			int start = e;
			int end = e; // end is already good

			memset(board, 0, sizeof(board));
			queue<pair<int, int>> q;
			if (e <= arr[1][1] && arr[1][1] <= e)
			{
				q.push({1, 1});
				board[1][1] = 1;
			}

			while (!q.empty())
			{
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				if (r == N && c == N)
					break;

				for (int d = 0; d < 4; d++)
				{
					int nr = r + rDiff[d];
					int nc = c + cDiff[d];

					if (!isValid(nr, nc))
						continue;
					if (board[nr][nc])
						continue;
					if (e <= arr[nr][nc] && arr[nr][nc] <= e)
					{
						q.push({nr, nc});
						board[nr][nc] = 1;
					}
				}
			}

			if (board[N][N])
			{
				best = min(best, 0);
			}
		}
	}

	cout << best << '\n';

	return 0;
}