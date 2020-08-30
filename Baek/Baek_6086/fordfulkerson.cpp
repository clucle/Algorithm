#include <map>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

map<char, int> mapCharToInt;

void initMapCharToInt()
{
    mapCharToInt.clear();
    for (char c = 'a'; c <= 'z'; c++) {
        mapCharToInt[c] = c - 'a';
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        mapCharToInt[c] = c - 'A' + 26;
    }
}

const int MAX_N = 52;

int c[MAX_N][MAX_N] = {0, };
int f[MAX_N][MAX_N] = {0, };

vector<int> Graph[MAX_N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    initMapCharToInt();

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        char a, b; int capacity;
        cin >> a >> b >> capacity;

        int _a = mapCharToInt[a];
        int _b = mapCharToInt[b];

        c[_a][_b] += capacity;
        c[_b][_a] = c[_a][_b];

        Graph[_a].push_back(_b);
        Graph[_b].push_back(_a);
    }

    int start = mapCharToInt['A'];
    int end = mapCharToInt['Z'];
    int ret = 0;

    int visited[MAX_N];
    while(true) {
        fill(visited, visited + MAX_N, -1);
        queue<int> q;
        q.push(start);

        while (!q.empty() && visited[end] == -1) {
            int here = q.front();
            q.pop();

            for (int there : Graph[here]) {
                if (c[here][there] - f[here][there] > 0 && visited[there] == -1) {
                    q.push(there);
                    visited[there] = here;
                    if (there == end) break;
                }
            }
        }

        if (visited[end] == -1) break;

        int max_flow = 1 << 9;
        for (int i = end; i != start; i = visited[i]) {
            max_flow = min(max_flow, c[visited[i]][i] - f[visited[i]][i]);
        }

        for (int i = end; i != start; i = visited[i]) {
            f[visited[i]][i] += max_flow;
            f[i][visited[i]] -= max_flow;
        }

        ret += max_flow;
    }

    cout << ret << '\n';
}
