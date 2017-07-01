#include <stdio.h>

int Answer;
int MAP[200000];

inline int max(int x, int y) {
	return (x>y?x:y);
}

int main(void)
{
	int T, test_case;
		
		
	freopen("input2.txt", "r", stdin);
	
	setbuf(stdout, NULL);

	scanf("%d", &T);

	int i;
	
	int l; 
	
	for(test_case = 0; test_case < T; test_case++)
	{
		scanf("%d", &l);
		Answer = 0;
		
		
		for (i = 0; i < l; i++) {
			scanf("%d", &MAP[i]);
		}
		
		if (l < 2) {
			printf("Case #%d\n", test_case+1);
	        printf("%d\n", Answer);
	        continue;
		}
		
		
		int max = 0;
		int state = 0;
		

		
		for (i = 1; i < l; i++) {
			if (MAP[i - 1] < MAP[i]) {
				state = 1;
				Answer+=2;
				break;
			} else if (MAP[i - 1] > MAP[i]){
				state = -1;
				break;
			}
		}
		
		// 증가 감소가 없음 
		if (state == 0) {
			printf("Case #%d\n", test_case+1);
        	printf("%d\n", Answer);
        	continue;
		}
		
		for (; i < l; i++) {
			if (MAP[i - 1] < MAP[i]) {
				if (state == -1) {
					Answer += 2;
				}
				state = 1;
			} else if (MAP[i - 1] > MAP[i]){
				state = -1;
			}
		}

		printf("Case #%d\n", test_case+1);
	        	printf("%d\n", Answer);
        
	}

	return 0;//Your program should return 0 on normal termination.
}
