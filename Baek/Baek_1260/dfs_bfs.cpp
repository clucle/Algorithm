
#include <set>
#include <queue>
#include <iostream>

using namespace std;
typedef long long ll;

set<int> s[1010];

int visited[1010];

void init() {
    int i;
    for (i = 0; i < 1010; i++) {
        visited[i] = 0;
    }
}

void dfs(int mynum) {
    if (visited[mynum] == 1) return;
    visited[mynum] = 1;
    cout << mynum << ' ';
    for (std::set<int>::iterator it = s[mynum].begin(); it != s[mynum].end(); ++it)
        dfs(*it);
}

void bfs(int mynum) {
    queue<int> q;
    q.push(mynum);
    while (!q.empty()) {
        int here = q.front();
        if (visited[here]) {
            q.pop();
            continue;
        }
        cout << here << ' ';
        visited[here] = 1;
        q.pop();
        for (std::set<int>::iterator it = s[here].begin(); it != s[here].end(); ++it) {
            if (!visited[*it]) {
                q.push(*it);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, M, V;

    cin >> N >> M >> V;

    int i;
    int a, b;
    for (i = 0; i < M; i++) {
        cin >> a >> b;
        if (a != b) {
            s[a].insert(b);
            s[b].insert(a);
        }
    }

    init();
    dfs(V);
    cout << '\n';
    init();
    bfs(V);

    return 0;
}