#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> truck, vector<int> w) {
    vector<int> answer;
    answer.assign(w.size(), -1);
    
    int i;
    int j;
    // ���� ���� ��ŭ i = �� ��ȣ 
	for (i = 0; i < w.size(); i++) {
		// Ʈ���� ��� ��ŭ k�� Ʈ����ȣ 
		for (j = 0; j < truck.size(); j++) {
    		if (w[i] < truck[j] + 1) {
    			answer[i] = j + 1;
    			truck[j] -= w[i];
				break; 
			}
		}
	}
    
    return answer;
}

int main() {
	vector<int> truck;
	truck.push_back(1);
	truck.push_back(4);
	truck.push_back(5);
	truck.push_back(2);
	truck.push_back(4);
	
	vector<int> w;
	w.push_back(2);
	w.push_back(4);
	w.push_back(4);
	w.push_back(3);
	w.push_back(2);
	
	
	vector<int> k = solution(truck, w);
	
}
