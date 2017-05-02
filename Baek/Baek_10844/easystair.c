#include <stdio.h>

int main(void) {
	int N;
	scanf("%d", &N);
	
	
	long long D[101][10];
	
	int i;
	D[0][0] = 0;
	for (i = 1; i < 10; i++) {
		D[0][i] = 1;
	}
	
	int j;
		
	for (i = 1; i < N; i++) {
		for (j = 0; j < 10; j++) {
			if (j == 0) D[i][j] = D[i-1][j+1] % 1000000000;
			else if (j == 9) D[i][j] = D[i-1][j-1] % 1000000000;
			else D[i][j] = (D[i-1][j-1] + D[i-1][j+1]) % 1000000000;
		}
	}
	i--;
	long long sum = 0;
	for (j = 0; j < 10; j++) {
		sum += D[i][j] % 1000000000;
	}
	printf("%d", sum%1000000000);
	return 0;
}
