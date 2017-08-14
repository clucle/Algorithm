#include <stdio.h>


inline int max(int a, int b) {
	return (a>b? a: b);
}

int main() {
	
	int N;
	scanf("%d", &N);
	
	int arr[10] = { 0, };
	
	int n;
	while (N > 0) {
		n = N % 10;
		N /= 10;
		arr[n]++;
	}
	
	int i;
	int imax = 0;
	for (i = 0; i < 10; i++) {
		if (i != 6 && i != 9) imax = max(imax, arr[i]);
	}
	
	int fmax = max(arr[6], arr[9]);
	
	if (imax > fmax) {
		printf("%d", imax);
	} else {
		printf("%d", max(imax, (arr[6] + arr[9] + 1)/2));
	}
	
	return 0;
}
