#include <stdio.h>

int Answer;

int main(void)
{
	int T, test_case;

	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		
		int N;
		scanf("%d", &N);
		N ++;
		
		int i = 31;
		while (i-- > 0) {
			if ((N & (1<<i)) != 0) {
				break;
			}
		}
		
		printf("Case #%d\n", test_case+1);
        
        i--;
		
		do {
			if ((N & (1<<i)) == 0) {
				printf("4");
			} else {
				printf("7");
			}
		} while (i-- > 0);
        
        printf("\n");
	}

	return 0;
}
