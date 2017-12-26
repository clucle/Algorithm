#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>


using namespace std;

int N, M;

vector<vector<int > > node;
int* visited;
int* room;

int dfs(int here) {
    if (visited[here]) return 0;
    visited[here] = 1;

    int i;
    for (i = 0; i < node[here].size(); i++) {
        int there = node[here][i];
        if (!room[there] || dfs(room[there])) {
            room[there] = here;
            return 1;
        }
    }
    return 0;
}

int bmatch() {
    int ans = 0;
    int i;
    for (i = 1; i < N + 1; i++) {
        memset(visited, 0, sizeof(int) * (N + 1));
        if (dfs(i)) ans++;
    }

    return ans;
}

int main() {

    scanf("%d%d", &N, &M);
    node.resize(N + 1);

    int Si;
    int i, j;
    int Ti;
    
    for (i = 1; i < N + 1; i++) {
        scanf("%d", &Si);
        for (j = 0; j < Si; j++) {
            scanf("%d", &Ti);
            node[i].push_back(Ti);
        }
    }

    visited = (int*)malloc(sizeof(int) * (N + 1));
    room = (int*)malloc(sizeof(int) * (M + 1));

    printf("%d", bmatch());
    
    free(visited);
    free(room);
}