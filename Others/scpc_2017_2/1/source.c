#include <stdio.h>
#include <stdlib.h>

int Answer;

int main(void)
{
	int T, test_case;

	// freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
		int N;
		scanf("%d ", &N);
		
		char* arr = (char*)malloc(sizeof(char) * N);
		gets(arr);
		
		N--;
		int state = 0;
		if (arr[N] == 'C') {
			printf("Case #%d\n", test_case+1);
	    	printf("NO\n", Answer);
	    	continue;
		} else if (arr[N] == 'A') {
			state = 1;//맨뒤가 A 
		} else {
			state = 2;//맨뒤가 B 
		}
		
		while (N-- > 0) {
			if (state == 1) {
				if (arr[N] == 'B') {
					state = 3;
				}
			} else if(state == 2) {
				if (arr[N] == 'A') {
					state = 4;
				}
			} else if(state == 3) {
				if (arr[N] == 'B') {
					Answer = -1;
				}
				state = 5;
			} else if(state == 4) {
				if (arr[N] == 'A') {
					Answer = -1;
				}
				state = 6;
			}
			
		}
		
		printf("Case #%d\n", test_case+1);
		if (Answer == -1) printf("NO\n");
		else printf("YES\n");
        
	}

	return 0;
}
