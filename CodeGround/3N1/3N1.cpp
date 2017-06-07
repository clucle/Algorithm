/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <stdio.h>

unsigned long long min(unsigned long long x, unsigned long long y) {
	return (x<y?x:y);
}
unsigned long long findmin(int start, int end, unsigned long long num) {
	if (start == end) {
		return num;
	}
	if (num < 5) {
		return findmin(start+1, end, num*2);
	}
	if (num%3 == 1) {
		if ((num - 1)/3 % 2 == 0) return findmin(start+1, end, num*2);
		else return min(findmin(start+1, end, (num - 1)/3), findmin(start+1, end, num*2));
	}
	return findmin(start+1, end, num*2);
}


int Answer;

int main(void)
{
	int T, test_case;
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		        
        int n;
		scanf("%d", &n);
		
		unsigned long long min = findmin(0, n, 1);
		unsigned long long max = 0;
		max |= (1ULL<<n);
		
        
		printf("Case #%d\n", test_case+1);
        printf("%llu %llu\n", min, max);
        
	}

	return 0;//Your program should return 0 on normal termination.
}
