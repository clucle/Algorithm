#include <stdio.h>
#include <stdlib.h>

int FindId(int* arr, int a) {
    while (arr[a] != a) {
        a = arr[a];
    }
    return a;
}

void Join(int* arr, int* rank, int a, int b) {
    int tmpa, tmpb;
    tmpa = FindId(arr, a);
    tmpb = FindId(arr, b);

    if (rank[tmpa] > rank[tmpb]) {
        arr[tmpb] = tmpa;
    } else if (rank[tmpa] < rank[tmpb]) {
        arr[tmpa] = tmpb;
    } else {
        arr[tmpa] = tmpb;
        rank[tmpb]++;
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int act, a, b;
    int* arr = (int*)malloc(sizeof(int) * (n + 1));
    int* rank = (int*)malloc(sizeof(int) * (n + 1));

    for (a = 0; a < n + 1; a++) {
        arr[a] = a;
        rank[a] = 0;
    }

    while (m-- > 0) {
        scanf("%d %d %d", &act, &a, &b);
        if (act) {
            if (FindId(arr, a) == FindId(arr, b)) printf("YES\n");
            else printf("NO\n");
        } else {
            Join(arr, rank, a, b);
        }
    }

    free(arr);
    free(rank);

    return 0;
}