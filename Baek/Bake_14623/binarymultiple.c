#include <stdio.h>
#include <string.h>

int main() {
	char first[60];
	char second[60];
	
	scanf("%s", first);
	scanf("%s", second);
	
	int arr[80];
	
	int i;
	for (i = 0; i < 80; i++) {
		arr[i] = 0;
	}
	
	int lenFirst = strlen(first);
	int lenSecond = strlen(second);
	
	int j;
	for (j = 0; j < lenSecond; j++) {
		if (second[lenSecond - j - 1] == '1') {
			for (i = 0; i < lenFirst; i++) {
			
				if (arr[j + i] > 1) {
					arr[j + i] -= 2;
					arr[j + i + 1]++;
				}
				
				if (first[lenFirst - i - 1] == '1') {
					arr[j + i]++;
					if (arr[j + i] > 1) {
						arr[j + i] -= 2;
						arr[j + i + 1]++;
					}
				}
			}	
		}
	}
	
	for (i = 80; i >=0; i--) {
		if (arr[i] == 1) break;
	}

	for (; i >= 0; i--) {
		printf("%d", arr[i]);
	}
	return 0;
	
	
}
