#include <stdio.h>
#include <stdlib.h>

int main() {
	int height;
	int width;
	int x;
	int y;
	int K;
	
	scanf("%d %d %d %d %d", &height, &width, &x, &y, &K);
	
	int **board;
	board = (int**)malloc( sizeof(int*) * height );
	int i;
	int j;
	int input;
	for (i = 0; i<height; i++) {
	    board[i] = (int*)malloc( sizeof(int) * width );
	    for (j = 0; j < width; j++) {
	    	scanf("%d", &input);
	    	board[i][j] = input;
		}
	}

	int top = 0;
	int bottom = 0;
	int west = 0;
	int east = 0;
	int north = 0;
	int south = 0;
	int tmp;
	int wrong;
	
	for (i = 0; i < K; i++) {
		wrong = 0;
		scanf("%d", &input);
		switch(input) {
			case 1:
				y++;
				if (y >= width) {
					y--;
					wrong = 1;
					break;	
				}
				tmp = top;
				top = west;
				west = bottom;
				bottom = east;
				east = tmp;
				break;
			case 2:
				y--;
				if (y < 0)  {
					y++;
					wrong = 1;
					break;	
				}
				tmp = top;
				top = east;
				east = bottom;
				bottom = west;
				west = tmp;
				break;
			case 3:
				x--;
				if (x < 0) {
					x++;
					wrong = 1;
					break;	
				}
				tmp = top;
				top = south;
				south = bottom;
				bottom = north;
				north = tmp;
				break;
			case 4:
				x++;
				if (x >= height) {
					x--;
					wrong = 1;
					break;	
				}
				tmp = top;
				top = north;
				north = bottom;
				bottom = south;
				south = tmp;
				break;
		}
		if (!wrong) {
			if (board[x][y] != 0) {
				bottom = board[x][y];
				board[x][y] = 0;
			}
			else {
				board[x][y] = bottom;
			}
			printf("%d\n", top);	
		}

	}

	return 0;
}
