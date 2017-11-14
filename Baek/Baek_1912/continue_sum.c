#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int N = 0;
    scanf("%d", &N);

    int i = 0;
    long long num;
    long long max;

    long long prev = 0;
    long long cur = 0;

    scanf("%lld", &num);
    max = num;
    if (prev > 0) {
        cur = prev + num;
    } else {
        cur = num;
    }
    if (max < cur) max = cur;
    prev = cur;

    for (i = 2; i < N + 1; i++) {
        scanf("%lld", &num);
        if (prev > 0) {
            cur = prev + num;
        } else {
            cur = num;
        }
        if (max < cur) max = cur;
        prev = cur;
    }

    printf("%lld", max);

    return 0;
}