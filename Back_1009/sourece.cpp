#include <iostream>

int main() {
	using namespace std;
	int T;
	cin >> T;

	int a, b;

	int arr_1[1] = { 1 };
	int arr_2[4] = { 2,4,8,6 };
	int arr_3[4] = { 3,9,7,1 };
	int arr_4[2] = { 4,6 };
	int arr_5[1] = { 5 };
	int arr_6[1] = { 6 };
	int arr_7[4] = { 7,9,3,1 };
	int arr_8[4] = { 8,4,2,6 };
	int arr_9[2] = { 9,1 };
	int arr_0[1] = { 0 };


	while (T--) {
		cin >> a >> b;
		a = a % 10;
		switch (a) {
		case 1:
			cout << 1;
			break;
		case 2:
			b = b % 4;
			if (b == 0) {
				cout << arr_2[3];
			}
			else {
				cout << arr_2[b - 1];
			}
			break;
		case 3:
			b = b % 4;
			if (b == 0) {
				cout << arr_3[3];
			}
			else {
				cout << arr_3[b - 1];
			}
			break;
		case 4:
			b = b % 2;
			if (b == 0) {
				cout << arr_4[1];
			}
			else {
				cout << arr_4[b - 1];
			}
			break;
		case 5:
			cout << 5;
			break;
		case 6:
			cout << 6;
			break;
		case 7:
			b = b % 4;
			if (b == 0) {
				cout << arr_7[3];
			}
			else {
				cout << arr_7[b - 1];
			}
			break;
		case 8:
			b = b % 4;
			if (b == 0) {
				cout << arr_8[3];
			}
			else {
				cout << arr_8[b - 1];
			}
			break;
		case 9:
			b = b % 2;
			if (b == 0) {
				cout << arr_9[1];
			}
			else {
				cout << arr_9[b - 1];
			}
			break;
		case 0:
			cout << 10;
			break;
		}
		if (T != 0) cout << endl;
	}
	return 0;
}