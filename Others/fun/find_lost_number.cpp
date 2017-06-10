#include <stdio.h>

int main() {
	unsigned int a = 0, b = 0;
	
	unsigned int n;
	unsigned int x;
	
	printf("1~n 까지 정렬되어있지 않은 숫자 (중복x)\n");
	printf("에서 숫자 k (1<= x <= n) 가 빠졌을때 찾기\n");
	printf("n 값 : ");
	scanf("%d", &n);
	printf("x 값 : ");
	scanf("%d", &x);
	
	int i;
	// 정렬 안되어있다고 가정
	// 결국 다돌리면 똑같음 
	for (i = 1; i <= n; i++) {
		a^=i;
		if (i==x) continue;
		b^=i;
	}
	printf("빠진 숫자 : %d", a^b);
}
