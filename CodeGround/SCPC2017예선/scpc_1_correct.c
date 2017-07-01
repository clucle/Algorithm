
#include <stdio.h>

#include <stdlib.h>

inline int max(int x, int y) {
	return (x>y?x:y);
}

int Answer;

typedef struct Node Node;
typedef struct Node {
	int cnt;
	char d;
	Node* next;
}Node;

int main(void)
{
	int T, test_case;


 	freopen("scpc1.txt", "r", stdin);

	setbuf(stdout, NULL);

	char input;
	
	

	scanf("%d\n", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		
		
		Answer = 0;
		
		scanf("%c", &input);
		Node* stack;
        stack = (Node*)malloc(sizeof(Node));
	    stack->d = -1;
	    stack->cnt = 0;
	    stack->next = NULL;
	    
	    
	    
		while (input != '\n') {
			// ¿­±â 
			
			
			if (input == '[' || input == '(' || input == '{') {
				Node* tmpStack = (Node*)malloc(sizeof(Node));
				tmpStack->cnt = 0;
				tmpStack->d = input;
				tmpStack->next = stack->next;
				
				stack->next = tmpStack;
			}
			// ´Ý±â 
			else {
				if (stack->next != NULL) {
					
					
					if (input < 50) input++;
					input -= 2;
					
					if (stack->next->d == input) {
						
						Node* tmpStack = stack->next;
						stack->next = tmpStack->next;
						
						if (stack->next == NULL) {
							stack->cnt += (tmpStack->cnt + 1);
							Answer = max(Answer, stack->cnt);
						} else {
							stack->next->cnt += (tmpStack->cnt + 1);
							Answer = max(Answer, stack->next->cnt);
						}

						free(tmpStack);
						
					} else {
						
						while (stack != NULL) {
							Node* tmpStack = stack;
							Answer = max(Answer, tmpStack->cnt);
							stack = stack->next;
							free(tmpStack);
						}
						
						stack = (Node*)malloc(sizeof(Node));
						stack->cnt = 0;
					    stack->d = -1;
					    stack->next = NULL;
					    
					}
					
					
				} else {
					Answer = max(Answer, stack->cnt);
					stack->cnt = 0;
				}
			}
			scanf("%c", &input);
		}
		
		while (stack != NULL) {
			Node* tmpStack = stack;
			Answer = max(Answer, tmpStack->cnt);
			stack = stack->next;
			free(tmpStack);
		}

		Answer *= 2;

		printf("Case #%d\n", test_case+1);
	    printf("%d\n", Answer);
        
	}

	return 0;//Your program should return 0 on normal termination.
}
