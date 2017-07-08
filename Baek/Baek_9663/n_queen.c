#include <stdio.h>
#include <math.h>

int board[15] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int cnt;
int N;

void f(int height, int board[]) {
	if (height == N) {
		cnt++;
		return;
	}
	
	int i;
	for (i = 0; i < N; i++) {
		
		int j;
		for (j = 0; j < height; j++) {
			if (board[j] == i || abs(height - j) == abs(i - board[j])) {
				break;
			}
		}
		
		if (j == height) {
			board[height] = i;
			f(height+1, board);
		}	
	}
}

int main() {

	scanf("%d", &N);
	
	f(0, board);
	printf("%d", cnt);
}
