#include <stdio.h>

inline int max(int a, int b){
	return (a > b)? a: b;
} 

int main() {
	int N;
	scanf("%d", &N);
	
	int score[300];
	int arr[300][2];
	int i;
	for (i = 0; i < N; i++) {
		scanf("%d", &score[i]);
	}
	arr[0][0] = score[0];
	arr[0][1] = score[0];
	
	arr[1][0] = score[0] + score[1];
	arr[1][1] = score[1];
	
	
	for (i = 2; i < N; i++) {
		arr[i][0] = arr[i-1][1] + score[i];
		arr[i][1] = max(arr[i-2][0], arr[i-2][1]) + score[i];
	}
	printf("%d", max(arr[N-1][0], arr[N-1][1]));
}
