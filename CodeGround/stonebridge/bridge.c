#include <stdio.h>
#include <stdlib.h>

int main() {
	// Test case
	int T;
	
	// N : cnt stones
	// K : limit  1 <= distance <= K
	// L : cnt bombs;
	int N, K, L;
	
	// DP : cnt route for index N, distance K
	int** DP;
	// DPSUM : sum 
	int* DPSUM;
	
	// bomb: bomb array (2, 4) => has bomb in 2, 4
	int* bomb;
	
	setbuf(stdout, NULL);
	
	scanf("%d", &T);
	int test_case;
	
	
	for (test_case = 0; test_case < T; test_case++) {
		
		/*---------- INput ----------*/
		scanf("%d %d %d", &N, &K, &L);
		
		// when (L > 0) -> init bomb
		if (L > 0) {
			bomb = (int*)malloc(sizeof(int) * L);
			int index_bomb;
			for (index_bomb = 0; index_bomb < L; index_bomb++) {
				scanf("%d", &bomb[index_bomb]);	
			}
		}
		
		/*---------- Exception ----------*/
		if (K == 1 & L > 0) {
			printf("Case #%d\n", test_case+1);
			printf("0\n");
			free(bomb);
			continue;
		}
		if (K == 1 & N > 1) {
			printf("Case #%d\n", test_case+1);
			printf("0\n");
			continue;
		}
		
		/*---------- Init ----------*/
		// init DP
		DP = (int**)malloc(sizeof(int*) * N);
		DPSUM = (int*)calloc(N, sizeof(int));
		int index_DP;
		for (index_DP = 0; index_DP < N; index_DP++) {
			DP[index_DP] = (int*)calloc(K, sizeof(int));
		}
		

		/*---------- Logic ----------*/
		int index_N, index_K;
		int cnt_bomb = 0; // bomb count
		for (index_N = 0; index_N < N; index_N++) {
			
			// 폭탄 터진 자리 
			if (L > 0) {
				if (bomb[cnt_bomb] == index_N + 1) {
					for (index_K = 0; index_K < K; index_K++) {
						if (index_K > index_N) break;
						DP[index_N][index_K] = 0;
					}
					cnt_bomb++;
					DPSUM[index_N] = 0;
					continue;
				}
			}
			//폭탄 안터졌을때 
			for (index_K = 0; index_K < K; index_K++) {
				// index K가 i보다 큰 곳은 무조건 0 
				if (index_N == index_K) {
					DP[index_N][index_K] = 1;
					DPSUM[index_N] += DP[index_N][index_K];
				}
				
				if (index_N - index_K < 1) break;
				//printf("DPSUM[%d] = %d ,index_N = %d, index_K = %d\n", index_N - index_K - 1, DPSUM[index_N - index_K - 1], index_N, index_K);
				DP[index_N][index_K] = (DPSUM[index_N - index_K - 1] - DP[index_N - index_K - 1][index_K]) % 1000000009;
				DPSUM[index_N] = (DPSUM[index_N] + DP[index_N][index_K]) % 1000000009;
			}
			
			/*
			printf("\n");
			int test1, test2;
			for (test1 = 0; test1 < N; test1++) {
				for (test2 = 0; test2 < K; test2++) {
					printf("%d ", DP[test1][test2]);
				}
				printf("\n");
			}*/
		}
				
		printf("Case #%d\n", test_case+1);
		printf("%d\n", DPSUM[N-1]);
		
		
		for (index_DP = 0; index_DP < N; index_DP++) {
			free(DP[index_DP]);
		}
		free(DP);
		free(DPSUM);
		if (L > 0) free(bomb);
	}
	
	return 0;
}
