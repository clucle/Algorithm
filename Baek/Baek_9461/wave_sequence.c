#include <stdio.h>

int main() {
    unsigned long long arr[100];
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 1;
    arr[3] = 2;
    arr[4] = 2;
    arr[5] = 3;
    arr[6] = 4;
    arr[7] = 5;
    arr[8] = 7;
    arr[9] = 9;
    int i;
    for (i = 10; i < 100; i++) {
        arr[i] = arr[i - 1] + arr[i - 5];
    }

    int N;
    scanf("%d", &N);

    int k;
    for (i = 0; i < N; i++) {
        scanf("%d", &k);
        printf("%lld\n", arr[k - 1]);
    }

    return 0;
    
}