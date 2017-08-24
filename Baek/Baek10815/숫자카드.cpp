#include <stdio.h>
#include <set>

int main() {
	int N;
	scanf("%d", &N);
	int i;
	int num;
	
	std::set<int> s;
	
	for (i = 0; i < N; i++) {
		scanf("%d", &num);
		s.insert(num);
	}
	
	std::set<int>::iterator iter;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &num);
		iter = s.find(num);
		if (iter != s.end())
			printf("1 ");
		else
			printf("0 ");

	}	
	return 0;
}
