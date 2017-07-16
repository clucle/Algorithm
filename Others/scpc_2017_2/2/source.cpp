#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class runner {
public:
	int start, inter;
};

bool cmp(const runner &a, const runner &b){
	return a.inter > b.inter;
}

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	//freopen("input.txt", "r", stdin);
	
	scanf("%d", &T);
	for(test_case = 0; test_case  < T; test_case++)
	{
		int N;
		Answer = 0;
		scanf("%d", &N);
		
		vector<runner> r(5);
		
		int i, j;
		int s, l, d;

		for (i = 0; i < N; i++) {
			scanf("%d%d%d", &s, &l, &d);
			
			if(N>3)
				continue;
				
			r[i].inter = l;
			
			int cnt = 0;
			int index;
			while (d != 0) {
					
				if ((l - d) % s == 0) {
					index = (l - d) / s;
				} else {
					index = (l - d) / s + 1;
				}

				cnt += index;
				d += s * index;	
				d %= l;
				
			}
			
			r[i].start = cnt;
			
			cnt = 0;
			d += s;
			while (d != 0) {
					
				if ((l - d) % s == 0) {
					index = (l - d) / s;
				} else {
					index = (l - d) / s + 1;
				}

				cnt += index;
				d += s * index;	
				d %= l;
				
			}
			r[i].inter = cnt + 1;
		}
		
		
		if(N <= 3)
		{
			sort(r.begin(), r.end(), cmp);
	
			long long int t;
			t = r[0].start;
			if (t == 0) t+=r[0].inter;
			for (; ; t+=r[0].inter) {
				for (j = 1; j < N; j++) {
					if ((t - r[j].start) % r[j].inter != 0) break;
				}
				if (j == N) {
					Answer = t;
					break;
				}
			}
		}
		
		r.clear();

		printf("Case #%d\n", test_case+1);
	    printf("%d\n", Answer);
	}

	return 0;
}
