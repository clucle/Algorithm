// 0으로 무한루프랑, long long을 신경써야됐다

#include<iostream>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<functional>

using namespace std;

int arr[102][102];
long long dp[102][102];
int visited[102][102];
int n;

inline int isValidate(int y, int x) {
    if (y <= n && x <= n) return 1;
    return 0;
}

long long dfs(int y, int x) {
    long long cnt = 0;
    if (visited[y][x]) {
        return dp[y][x];
    }
    if (arr[y][x] == 0) {
        dp[y][x] = 0;
        visited[y][x] = 1;
        return 0;
    }
    if (isValidate(y + arr[y][x], x)) {
        cnt += dfs(y + arr[y][x], x);
    }
    if (isValidate(y, x + arr[y][x])) {
        cnt += dfs(y, x + arr[y][x]);
    }
    dp[y][x] = cnt;
    visited[y][x] = 1;
    return cnt;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            dp[i][j] = 0;
            visited[i][j] = 0;
        }
    }
    visited[n][n] = 1;
    dp[n][n] = 1;
    cout << dfs(1, 1);
	return 0;
}
