#include <stdio.h>

inline int fmin(int x, int y) {
	return (x > y)? y : x;
}

int main() {
	int N;
	scanf("%d", &N);
	
	int p[1001][3];
	int q[1001][3];
	
	int i;
	int j;
	for (i = 1; i <= N; ++i) {
		scanf("%d %d %d", &p[i][0], &p[i][1], &p[i][2]);
	}
	
	q[1][0] = p[1][0];
	q[1][1] = p[1][1];
	q[1][2] = p[1][2];
	
	for (i = 2; i <= N; ++i) {
		q[i][0] = p[i][0] + fmin(q[i-1][1], q[i-1][2]);
		q[i][1] = p[i][1] + fmin(q[i-1][0], q[i-1][2]);
		q[i][2] = p[i][2] + fmin(q[i-1][0], q[i-1][1]);
	}
	j = q[N][2];
	for (i = 0; i < 2; ++i) {
		if (j > q[N][i]) j = q[N][i];
	}
	printf("%d", j);
}
