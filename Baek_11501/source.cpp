#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int T, N;
vector<int> arr;


int main() {
	long long int ans = 0;
	int count = 0;
	scanf("%d", &T);
	while (T--) {
		
		scanf("%d", &N);
		arr = vector<int>(N, 0);
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}

		auto ma = max_element(arr.begin(), arr.end());
		ans = 0;
		count = 0;
		for (int i = 0; i < N; i++) {
			if (arr[i] == *ma) {
				if(i != N-1) ma = max_element(arr.begin() + i + 1, arr.end());
				ans += arr[i] * count;
				count = 0;
				continue;
			}
			ans -= arr[i];
			count++;
		}

		printf("%llu\n", ans);
	}

	return 0;
}