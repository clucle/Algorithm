#include <iostream>

int main() {
	using namespace std;

	int T;
	cin >> T;

	for (int p = 0; p < T; p++) {// T만큼 반복한다
		
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		int n;
		cin >> n;

		int rx, ry, r;
		bool xy1_in_r;
		bool xy2_in_r;

		int result = 0;

		for (int i = 0; i < n; i++) {
			cin >> rx >> ry >> r;
			xy1_in_r = ((x1 - rx)*(x1 - rx) + (y1 - ry)*(y1 - ry) < r*r) ? true : false;
			xy2_in_r = ((x2 - rx)*(x2 - rx) + (y2 - ry)*(y2 - ry) < r*r) ? true : false;

			if (xy1_in_r != xy2_in_r) result++;
		}
		cout << result;
		if (p != T - 1) cout << endl;
	}

	return 0;
}
