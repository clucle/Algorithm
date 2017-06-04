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
			// index ��° ��Ʈ�� 1�� ����� 
			// 1 �� index��ŭ left shift ���Ѽ� or ���� 
		} else if (strcmp(input, "remove") == 0) {
			arr &= ~(1<<index);
			// index ��° ��Ʈ�� 0���� �����
			// index��ġ�� 0���� �ϰ� ������ 1�� �ؼ� and ���� 
		} else if (strcmp(input, "check") == 0) {
			// ������ ���� ������ ��ȣ ���� �߿� 
			if ((arr & (1<<index)) == 0) {
				printf("0\n");
			} else {
				printf("1\n");
			}
			// index ��° ��Ʈ�� 1�� �ؼ� &����
			// �ڸ��� �������� 1�� �ִٸ� 0�� �ƴ� ���� ���� 
		} else if (strcmp(input, "toggle") == 0) {
			arr ^= (1<<index);
			// index ��° ��Ʈ�� 1�� ����� 
			// 1 �� index��ŭ left shift ���Ѽ� xor ����(����) 
		} else if (strcmp(input, "all") == 0) {
			arr &= 0;
			arr--;
		} else if (strcmp(input, "empty") == 0) {
			arr &= 0;
			//0 �� and�� �ϸ� 0�� �ǰ��� 
		}
	} 
	
	
}
