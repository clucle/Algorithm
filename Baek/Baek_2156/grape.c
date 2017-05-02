#include <stdio.h>

inline int max(int a, int b) {
	return (a>b?a:b);
}

int main() {
	int N;
	scanf("%d", &N);
	
	int arr[10000];
	int i;
	for (i = 0; i < N; i++) {
		scanf("%d", &arr[i]);	
	}
	
	if (N == 1) {
		printf("%d", arr[0]);
		return 0;
	}
	
	int D[10000][3];
	D[0][0] = arr[0]; D[0][1] = 0; D[0][2] = 0;
	D[1][0] = arr[0] + arr[1]; D[1][1] = arr[1]; D[0][2] = 0;
	D[2][0] = D[1][1] + arr[2];
	D[2][1] = max(D[0][0], D[0][1]) + arr[2];
	D[2][2] = arr[2];
	
	for (i = 3; i < N; i++) {
		D[i][0] = max(D[i-1][1], D[i-1][2]) + arr[i];
		D[i][1] = max(max(D[i-2][0], D[i-2][1]), D[i-2][2]) + arr[i];
		D[i][2] = max(D[i-3][0], D[i-3][1])	+ arr[i];
	}
	
	//for (i = 0; i < N; i++) {
	//	printf("%d %d %d\n", D[i][0], D[i][1], D[i][2]);
	//}
	
	i = N-3;
	if (i < 0) i = 0;
	int maxr = 0;
	for (; i < N; i++) {
		if (maxr < max(D[i][0], D[i][1])) maxr = max(D[i][0], D[i][1]);
		maxr = max(maxr, D[i][2]);
	}
	
	printf("%d", maxr);
	return 0;
}
