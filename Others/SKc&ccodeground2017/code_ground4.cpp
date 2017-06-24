#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> truck, vector<int> w) {
    vector<int> answer;
    answer.assign(w.size(), -1);
    
    int i;
    int j;
    // 짐의 갯수 만큼 i = 짐 번호 
	for (i = 0; i < w.size(); i++) {
		// 트럭의 댓수 만큼 k는 트럭번호 
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
