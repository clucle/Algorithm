#include <iostream>

int main() {
	using namespace std;
	int T;
	cin >> T;
	int n, m;
	int s;
	int result;
	while (T--) {
		result = 1;
		cin >> n >> m;

		s = m - n; // 8C7�̳� 8C1�̳� �Ȱ��� for ���Ϸ���
		if (s > (m / 2)) {
			s = m - s;
		}
		for (int i = 0; i < s; i++) {
			result = result * (m - i)/(i + 1);
		}
		cout << result;
		if (T != 0) cout << endl;
	}
}