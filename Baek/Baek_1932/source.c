#include <stdio.h>

inline int max(int a, int b) {
	return (a>b) ? a: b;
}

int main() {
	int k[500];
	int result[500][500];
	
	int n;
	scanf("%d", &n);
	
	int i = 0;
	int j = 0;
	
	result[0][0] = 0;
	
	scanf("%d", &result[0][0]);
	
	for (i = 1;i < n; i++) {
		for (j = 0; j < i + 1; j++) {
			scanf("%d", &k[j]);
			
			if (j == 0) {
				result[i][0] = k[0] + result[i - 1][0];
				continue;
			}
			if (j == i){
				result[i][j] = k[j] + result[i - 1][j - 1];
				continue;
			} 
			
			result[i][j] = k[j] + max(result[i-1][j-1], result[i-1][j]);
			
		}
	}
	
	int q = n-1;
	int max = 0;
	
	
	for (i = 0;i < n; i++) {
		if (result[q][i] > max) max = result[q][i];
	}
	
	printf("%d", max);
	return 0;
}
