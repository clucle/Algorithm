#include <stdio.h>

int main() {
	unsigned int a = 0, b = 0;
	
	unsigned int n;
	unsigned int x;
	
	printf("1~n ���� ���ĵǾ����� ���� ���� (�ߺ�x)\n");
	printf("���� ���� k (1<= x <= n) �� �������� ã��\n");
	printf("n �� : ");
	scanf("%d", &n);
	printf("x �� : ");
	scanf("%d", &x);
	
	int i;
	// ���� �ȵǾ��ִٰ� ����
	// �ᱹ �ٵ����� �Ȱ��� 
	for (i = 1; i <= n; i++) {
		a^=i;
		if (i==x) continue;
		b^=i;
	}
	printf("���� ���� : %d", a^b);
}
