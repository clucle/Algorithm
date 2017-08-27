#include <stdio.h>
#include <string.h>

inline int max(int a, int b) {
	return (a>b? a: b);
}

int arr[1100][1100] = { {0 } };

int main() {
	char line1[1000];
	char line2[1000];
	
	scanf("%s", &line1);
	scanf("%s", &line2);
	
		
	int n = strlen(line1);
	int m = strlen(line2);
		
	
	int i, j;
	int tmpMax;
	for (i = 1; i <= m ; i ++) {
		for (j = 1; j <= n; j++) {
			if (line1[j - 1] == line2[i - 1]) {
				arr[i][j] = arr[i - 1][j - 1] + 1;
			} else {
				arr[i][j] = max(arr[i][j - 1], arr[i - 1][j]);
			}
		}
	}
	/*
	for (i = 0; i <= m ; i ++) {
		for (j = 0; j <= n; j++) {
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
*/
	printf("%d", arr[m][n]);
	
	return 0;
}
