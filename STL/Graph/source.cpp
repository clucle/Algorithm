#include <iostream>
#include <vector>
using namespace std;

int N, L;
vector<pair<int, int> > v[100];
int main() {
	cin >> N >> L; //�����̶� ���� ��

	for (int i = 0; i < L; i++) {
		int N_1, N_2, weigh; //N_1 ~ N_2 �� ����ġ ����
		cin >> N_1 >> N_2 >> weigh;

		pair<int, int> p1; //(�ٸ����, ����ġ)
		p1.first = N_2; p1.second = weigh;
		v[N_1].push_back(p1);

		pair<int, int> p2; //(�ٸ����, ����ġ)
		p2.first = N_1; p2.second = weigh;
		v[N_2].push_back(p2);
	}
	int k;
	for (int i = 1; i<=N; i++) {
		cout << i << "�� ���� : ";
		k = v[i].size();
		for (int j = 0; j< k; j++) {
			cout << v[i][j].first << " ";
			cout << v[i][j].second << " ";
			cout << " ";
		}
		cout << endl;
	}
	system("pause");

	return 0;
}