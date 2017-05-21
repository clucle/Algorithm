# include <stdio.h>
# include <string.h>

int main() {
	char str[101];
	scanf("%s", str);
	
	int len = strlen(str);
	
	int N;
	scanf("%d", &N);
	
	
	char find[20];
	int D[20];

	int turn;
	for (turn = 0; turn < N; turn++) {
		scanf("%s", find);
		int init_d;
		for (init_d = 0; init_d < 20; init_d ++) {
			D[init_d] = 0;
		}
		
		char str2[101];
		strcpy(str2, str);
		
		int i;
		int j;
		for (j = 0; j < 26; j++) {
			if (strstr(str2, find) != NULL) {
				printf("%s", str2);
				return 0;
			}
			
			for (i = 0; i < len; i++) {
				str2[i]++;
				if (str2[i] == 123 || str2[i] == 91) str2[i] -= 26;
			}
			
		}
	}
	
	return 0;
}
