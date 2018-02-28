#include <cstdio>
#include <queue>

char arr[2][100100];
int DP[2][100100];

using namespace std;

int N, k;


int main() {
    
    scanf("%d %d", &N, &k);
    int i, j;

    scanf("%s", arr[0]);
    scanf("%s", arr[1]);
    
    queue<pair<int,int> > q;
    queue<pair<int,int> > tmpQ;

    q.push(make_pair(0,0));
    DP[0][0] = 1;
 
    int turn = 1;
    int ret = 0;
    
    while (!q.empty()) {

        pair<int,int> item = q.front();
        q.pop();

        int line = item.first;
        int index = item.second;

        if (index + k >= N)  {
            ret = 1;
            break;
        }
        
        if (arr[line][index + 1] == '1' && DP[line][index + 1] == 0) {
            tmpQ.push(make_pair(line, index + 1));
            DP[line][index + 1] = turn + 1;
        }

        if (arr[line][index - 1] == '1' && DP[line][index - 1] == 0 && index > turn)  {
            tmpQ.push(make_pair(line, index - 1));
            DP[line][index - 1] = turn + 1;
        }

        if (arr[(line + 1) % 2][index + k] == '1' && DP[(line + 1) % 2][index + k] == 0) {
            tmpQ.push(make_pair((line + 1) % 2, index + k));
            DP[(line + 1) % 2][index + k] = turn + 1;
        }

        if (q.empty()) {
            turn++;
            swap(q, tmpQ);
        }

    }

    printf("%d\n", ret);
    /*
    for (j = 0; j < 2; j++) {
        for (i = 0; i < N; i++) {
            printf("%d ", DP[j][i]);
        }
        printf("\n");
    }
    */
}

