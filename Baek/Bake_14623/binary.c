#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	char B1[31];
	char B2[31];
	scanf("%s", B1);
	scanf("%s", B2);
	
	int i;
	int size_B1 = strlen(B1);
	int size_B2 = strlen(B2);
	
	unsigned long long num1 = 0;
	unsigned long long num2 = 0;
	
	for (i = size_B1; i > -1; i--) {
		if (B1[size_B1 - i] == 49) num1 += pow(2, i - 1);
	}
	
	for (i = size_B2; i > -1; i--) {
		if (B2[size_B2 - i] == 49) num2 += pow(2, i - 1);
	}
	
	unsigned long long result = num1 * num2;
	printf("result1: %lld\n", num1);
	printf("result2: %lld\n", num2);
	printf("result = %lld\n", result);
	
	i = 63;
	for (; i > -1; i--) {
		if ((result & (1ULL<<i)) != 0) {
			break;
		}
	}
	
	for (; i > -1; i--) {
		if ((result & (1ULL<<i)) == 0) printf("0");
		else printf("1");
	}
}
