#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<int> prime;

bool isPrime(int n) {
	for (int k = 2; k <= sqrt(n); k++) {
		if (n%k == 0) return false;
	}
	return true;
}

int findx(int n) {
	if (n < 2) {
		return -1;
	}
	int index = 0;	
	for (index = 0; index < prime.size(); index++) {
		if (n <= prime[index]) {
			break;
		}
	}

	return prime[index - 1];
}

bool findy(int n) {
	int tmp = n;
	if (n < 4) return false;
	while (true) {
		tmp = findx(tmp);
		cout << "tmp" << tmp << endl;
		if (tmp == -1) {
			return false;
		}
		int h = n - tmp;
		if (isPrime(h)) {
			cout << h << " " << tmp << " ";
			return true;
		}
	}
}

int main() {
	int count;
	for (int i = 2; i < 1000; i++) {
		if (isPrime(i)) {
			prime.push_back(i);
		}
	}
	int T = 50;
	int T_next = T;
	int num_minus;


	while (T_next > 4) {
		T_next = findx(T_next - 1);
		num_minus = T - T_next;
		printf("1:%d\n", num_minus);
		if (findy(num_minus) == true) {
			cout << T_next << endl;
			break;
		}
	}
	
	cin >> T;
	return 0;
}