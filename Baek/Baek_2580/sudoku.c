#include <stdio.h>

int end;

void f(int board[]) {
	if (end == 1) {
		return;	
	}
	
	int i, j, k, x, y;
	
	int position_x;
	int position_y; 
	
	for (i = 0; i < 81; i++) {
		if (board[i] == 0) {
			x = i % 9;
			y = i / 9;
			
			position_x = x / 3;
			position_y = y / 3;
			
			
			for (j = 1; j < 10; j++) {
				for (k = 0; k < 9; k++) {
					if (board[k * 9 + x] == j) {
						break;	
					}
				}
				
				if (k == 9) {
					for (k = 0; k < 9; k++) {
						if (board[y*9 + k] == j) {
							break;	
						}
					}
				} else {
					continue;
				}
				// 가로세로 다 통과
				int t;
				if (k == 9) {
					int pos = position_y * 27 + position_x * 3;
					
					for (t = 0; t < 3; t++) {
						for (k = pos; k < pos + 3; k++) {
							if (board[k] == j) {
								break;	
							}
						}
						if (k == pos + 3) {
							pos += 9;	
						} else {
							break;
						}
					}
					
					if (t == 3) {
						board[i] = j;
						f(board);
						board[i] = 0;
					}
				}

			}
			break;
		}
	}
	
	if (i == 81) {
		for (i = 0; i < 81; i++) {
			printf("%d ", board[i]);
			if (i % 9 == 8) {
				printf("\n");
			}
		}
		end = 1;
	}
}

int main() {
	int board[81];
	
	int i;
	for (i = 0; i < 81; i++) {
		scanf("%d", &board[i]);
	}
	end = 0;
	f(board);
		
	return 1;
}
