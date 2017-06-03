#include <stdio.h>

int main() {
	int N;
	scanf("%d", &N);
	
	long long DP1[91];
	long long DP2[91];
	
	if (N < 3) {
		printf("1");
		return 0;
	} 
	DP1[3] = 1;
	DP2[3] = 1;
	
	int i;
	for (i = 4; i <= N; i++) {
		DP1[i] = DP2[i - 1];
		DP2[i] = DP1[i - 1] + DP2[i - 1];
	}
	
	
	printf("%lld", DP1[N] + DP2[N]);
	return 0;
}
