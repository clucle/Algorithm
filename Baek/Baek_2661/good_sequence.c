#include <stdio.h>

int N;
int end;


void f(int n, int board[]) {
	if (end == 1) {
		return;
	}
	
	if (n == N) {
		// end
		int i;
		for (i = 1; i < N; i++) {
			printf("%d", board[i]);
		}
		end = 1;
	}
	
	if (n == 1) {
		board[1] = 1;
		f(2, board);
		
		return;
	} 
	
	// 1~3 순서대로 체크 
	int num;
	
	// 수열 확인 변수 
	int tmp_position; 
	int pos;
	int check_position = n / 2;
	
	for (num = 1; num < 4; num++) {
		board[n] = num;
		for (tmp_position = 1; tmp_position < check_position + 1; tmp_position++) {
			// tmp_position == 1
			// board[n] = board[n - 1]
			
			//tmp_position == 2
			// board[n] = board[n - 2]
			// board[n - 1] = board[n - 3]
			
			//tmp_position == 3
			// board[n] = board[n - 3]
			// board[n - 1] = board[n - 4]
			// board[n - 2] = board[n - 5]
			
			for (pos = 0; pos < tmp_position; pos++) {
				//printf("board[%d] = %d, board[%d] = %d\n", n- pos,board[n- pos],n - tmp_position - pos,board[n- tmp_position-pos] );
				if (board[n - pos] != board[n - tmp_position - pos]) {
					break;
				}
			}
			if (pos == tmp_position) {
				break;
			} 
		}
		if (tmp_position == check_position + 1) {
			f(n+1, board);
		}
		
	}
}

int main() {

	scanf("%d", &N);
	N++;
	
	end = 0;
	int board[81] = {1, };
	f(1, board);
	
	return 1;
}
