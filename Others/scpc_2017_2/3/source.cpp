#include <cstdio>
#include <set>
#include <cstdlib>
#include <iostream>
#include <math.h> 

int Answer;

using namespace std;

int f (int x, int y) {
	int n;
	while (1) {
		n = x % y;
		if (n == 0) return y;
		x = y;
		y = n;
	}
}

int main(void)
{
	int T, test_case;
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int arr[100000];

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
		int N, M;
		scanf("%d%d", &N, &M);
		
		int i, j;
		for (i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}
		
		int b, l, r;
		set<int> s;
		

		for (i = 0; i < M; i++) {
			scanf("%d%d%d", &b, &l, &r);
			
			int cnt = 0;
			for (j = 1; j * j <= b; j++) { if (b % j == 0) { cnt++; if (j * j < b) { cnt++; } } }

			
			//printf("약수의 갯수 : %d\n", cnt);
		
			int k;
			s.insert(1);
			for (j = l - 1; j < r; j++) {
				
				int gcm = f(b, arr[j]);
				s.insert(gcm);
				
				int t = sqrt(gcm);
				for (k = 2; k < t + 1; k++) {
					if (gcm % k == 0) {
						s.insert(k);
						s.insert(gcm / k);
					}
				}
			}
			
			set<int>::iterator iter;
		    for (iter = s.begin(); iter != s.end(); ++iter){
		    	//cout << "넣 : " << *iter << " "; 
		        cnt--;
		    }

		    Answer += cnt;
		    s.clear();
		}
		
		
		
		printf("Case #%d\n", test_case+1);
	    printf("%d\n", Answer);
        
	}

	return 0;//Your program should return 0 on normal termination.
}
