#include <stdio.h>

int main(void) {
	long long f[91];
	f[0] = 0;
	f[1] = 1;
	
	int n;
	scanf("%d", &n);
	
	if (n > 91) return 0;
	
	int i;
	for (i = 2; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	
	printf("%lld", f[n]);
	
	return 0;
}
