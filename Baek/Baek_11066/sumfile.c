#include <stdio.h>

int arr[520];
int DP[520][520];
int sum[520][520];

int main() {
    int N;
    scanf("%d", &N);
    int n;

    for (n = 0; n < N; n++) {
        int T;
        scanf("%d", &T);

        int t;
        
        for (t = 0; t < T; t++) {
            scanf("%d", &arr[t]);
        }

        int i, j;

        for (i = 0; i < T; i++) {
            sum[i][i] = arr[i];
        }
        for (i = 0; i < T; i++) {
            for (j = i + 1; j < T; j++) {
                sum[i][j] = sum[i][j - 1] + arr[j];
            }
        }

        
        for (i = 0; i < T; i++) {
            for (j = 0; j < T; j++) {
                DP[i][j] = 0;
            }
        }

        int imin;
        int tmp;
        for (i = 1; i < T; i++) {
            for (j = 0; i + j < T; j++) {
                imin = (1 << 30);
                
                for (t = 0; t < i; t++) {

                    tmp = DP[j + t][j] + DP[i + j][j + t + 1];

                    if (imin > tmp) imin = tmp;
                }

                DP[i + j][j] = imin + sum[j][i + j];
            }
        }

        printf("%d\n", DP[T - 1][0]);
    }
    return 0;
}