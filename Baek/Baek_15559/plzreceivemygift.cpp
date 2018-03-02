#include <cstdio>
#include <queue>

using namespace std;

int N, M;
bool visited[1010][1010];
char map[1010][1010];

int isValid(int y, int x) {
    if (y < 0 || y >= N || x < 0 || x >= M) {
        return 0;
    }
    return 1;
}

int main() {

    scanf("%d %d", &N, &M);

    int i, j;
    for (i = 0; i < N; i++) {
        scanf("%s", map[i]);
    }
    
    int ret = 0;

    queue<pair<int, int> > q;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {

            if (visited[i][j] == false) {
                ret++;
                q.push(make_pair(i, j));
                while (!q.empty()) {
                    int y = q.front().first;
                    int x = q.front().second;

                    //printf("%d %d\n", y, x);

                    q.pop();
                    
                    if (visited[y][x] == true) continue;
                    visited[y][x] = true;

                    if ((isValid(y - 1, x) && !visited[y - 1][x]) && map[y - 1][x] == 'S') q.push(make_pair(y - 1, x));
                    if ((isValid(y + 1, x) && !visited[y + 1][x]) && map[y + 1][x] == 'N') q.push(make_pair(y + 1, x));
                    if ((isValid(y, x - 1) && !visited[y][x - 1]) && map[y][x - 1] == 'E') q.push(make_pair(y, x - 1));
                    if ((isValid(y, x + 1) && !visited[y][x + 1]) && map[y][x + 1] == 'W') q.push(make_pair(y, x + 1));

                    
                    switch(map[y][x]) {
                        case 'N':
                            if (isValid(y - 1, x) && !visited[y - 1][x]) {
                                q.push(make_pair(y - 1, x));
                            }
                            break;
                        case 'S':
                            if (isValid(y + 1, x) && !visited[y + 1][x]) {
                                q.push(make_pair(y + 1, x));
                            }
                            break;
                        case 'W':
                            if (isValid(y, x - 1) && !visited[y][x - 1]) {
                                q.push(make_pair(y, x - 1));
                            }
                            break;
                        case 'E':
                            if (isValid(y, x + 1) && !visited[y][x + 1]) {
                                q.push(make_pair(y, x + 1));
                            }
                            break;
                    }


                }
            }

        }
    }
    printf("%d", ret);
    return 0;
}
