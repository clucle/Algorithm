#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;

inline int max(int a, int b) {
    return (a>b?a:b);
}

pair<int, int> arr[1000010];

int main() {
    int N;
    scanf("%d", &N);

    int i;
    for (i = 0; i < N; i++) {
        scanf("%d%d", &arr[i].first, &arr[i].second);
    }

    sort(arr, arr + N);

    int start = arr[0].first;
    int end = arr[0].second;

    int sum = 0;
    for (i = 1; i < N; i++) {
        if (end >= arr[i].first) {
            end = max(arr[i].second, end);
        } else {
            sum += end - start;
            start = arr[i].first;
            end = arr[i].second;
        }
    }

    sum += end - start;
    printf("%d", sum);

    return 0;
}