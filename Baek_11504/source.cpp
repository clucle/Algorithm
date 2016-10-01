#include <cstdio>
#include <stdlib.h>
#include <math.h>

int main(){
	
	int T;
	int N, M;
	int num_input;
	int X = 0, Y = 0;
	int Z;
	int board[100];

	scanf("%d", &T);
	while (T--) {
		int count = 0;
		X = 0;
		Y = 0;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < M; i++) {
			scanf("%d", &num_input);
			X = X + num_input * pow(10, (M - i - 1));
		}
		for (int i = 0; i < M; i++) {
			scanf("%d", &num_input);
			Y = Y + num_input * pow(10, (M - i - 1));
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &board[i]);
		}
		for (int i = 0; i < N; i++) {
			Z = 0;
			for (int j = 0; j < M; j++) {
				Z += board[(i + j)%N] * pow(10, (M-j-1));
			}
			if (X <= Z && Z <= Y) count++;
		}
		printf("%d\n", count);
	}

	return 0;
}