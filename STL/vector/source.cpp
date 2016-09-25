#include <iostream>
#include <vector>

int main() {
	using namespace std;
	int T;
	cin >> T;
	vector<int> v;
	for (int i = 0; i < T; i++) {
		v.push_back(i);
	}
	//v[T] = {0,1,2, .... ,T-2, T-1}

	v.insert(v.begin() + 1, 55);
	//뒤에있는거 밀면서 추가
	//v[T+1] = {0,55,1, .... ,T-2, T-1}

	v.clear();
	//v[] = {}

	cout << v.size();
	//원소 갯수

	cout << endl;
	system("pause");
}