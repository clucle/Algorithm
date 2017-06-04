#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	unsigned int arr = 0;
	int N;
	scanf("%d", &N);
	int i;
	char* input;
	input = (char*)malloc(6);
	int index;
	
	for (i = 0; i < N; i++) {
		scanf("%s", input);
		scanf("%d", &index);
		
		if (strcmp(input, "add") == 0) {
			arr |= (1<<index);
			// index 번째 비트를 1로 만든다 
			// 1 을 index만큼 left shift 시켜서 or 연산 
		} else if (strcmp(input, "remove") == 0) {
			arr &= ~(1<<index);
			// index 번째 비트를 0으로 만든다
			// index위치만 0으로 하고 나머지 1로 해서 and 연산 
		} else if (strcmp(input, "check") == 0) {
			// 연산자 순위 때문에 괄호 순서 중요 
			if ((arr & (1<<index)) == 0) {
				printf("0\n");
			} else {
				printf("1\n");
			}
			// index 번째 비트만 1로 해서 &연산
			// 자리가 같은곳에 1이 있다면 0이 아닌 수가 나옴 
		} else if (strcmp(input, "toggle") == 0) {
			arr ^= (1<<index);
			// index 번째 비트를 1로 만든다 
			// 1 을 index만큼 left shift 시켜서 xor 연산(반전) 
		} else if (strcmp(input, "all") == 0) {
			arr &= 0;
			arr--;
		} else if (strcmp(input, "empty") == 0) {
			arr &= 0;
			//0 과 and를 하면 0이 되겠지 
		}
	} 
	
	
}
