#include <stdio.h>

inline long long max(long long x, long long y) {
	return (x>y? x:y);
}

int main() {
	long long map[301][301];
	
	long long N;
	long long Size;

	scanf("%d %d", &N, &Size);
	
	long long i, j;
	
	for (i = 0; i < 301; i++) {
		for (j = 0; j < 301; j++) {
			map[i][j] = 0;
		}
	}
	
	int x, y;
	
	for (i = 0; i < N; i++) {
		scanf("%d %d", &x, &y);
		map[x][y] = Size - x - y;
		if (map[x][y] < 0) map[x][y] = 0;
	}
	
	long long D[301][301];
	D[0][0] = map[0][0];
	
	for (i = 1; i < 301; i++) {
		D[i][0] = D[i-1][0] + map[i][0];
	}
	for (i = 1; i < 301; i++) {
		D[0][i] = D[0][i - 1] + map[0][i];
	}
	
	for (i = 1; i < 301; i++) {
		for (j = 1; j < 301; j++) {
			D[i][j] = max(D[i-1][j], D[i][j-1]) + map[i][j];
		}
	}
	
	long long result = 0;
	if (Size >= 600) result = D[300][300];
	else {
		for (i = 0; i < Size + 1; i++) {
			result = max(D[i][Size - i], result);
		}
	}
	
	printf("%d", result);
	
	return 0;
}
