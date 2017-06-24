#include <vector>
#include <iostream>
using namespace std;

int solution(vector<vector<int> > board, vector<int> nums) {
    // N 2이상 500 이하
	int board_size = board.size(); 
	int answer = 0;
    
    int map[500][500];
    
    
    int i;
    int j;
    int k;
    
    for(i = 0; i < board_size; i++){
        for(j = 0; j < board_size; j++){
            map[i][j] = 0; // 체크 안된상태 
        }
    }
    
	for (k = 0; k < nums.size(); k++) {
		for(i = 0; i < board_size; i++){
	        for(j = 0; j < board_size; j++){
	            if (nums[k] == board[i][j]) {
	            	map[i][j] = 1;
	            	break;
				}
	        }
	        if (map[i][j] == 1) break;
	    }
	}
	
	int cnt;
	for(i = 0; i < board_size; i++){
        cnt = 0;
		for(j = 0; j < board_size; j++){
            if (map[i][j] == 0) break;
            cnt++;
        }
        if (cnt == board_size) answer++;
    }
    
	for(i = 0; i < board_size; i++){
        cnt = 0;
		for(j = 0; j < board_size; j++){
            if (map[j][i] == 0) break;
            cnt++;
        }
        if (cnt == board_size) answer++;
    }
	cnt = 0;
	for(i = 0; i < board_size; i++) {
        if (map[i][i] == 0) break;
		cnt++;
	}
	if (cnt == board_size) answer++;
	
	cnt = 0;
	for(i = 0; i < board_size; i++) {
        if (map[board_size - i - 1][i] == 0) break;
		cnt++;
	}
	if (cnt == board_size) answer++;

	return answer;
}


int main() {
	vector<vector<int> > arr(4, vector<int>(4, 0));
	arr[0][0] = 11;
	arr[0][1] = 13;
	arr[0][2] = 15;
	arr[0][3] = 16;
	
		arr[1][0] = 12;
	arr[1][1] = 1;
	arr[1][2] = 4;
	arr[1][3] = 3;
	
		arr[2][0] = 10;
	arr[2][1] = 2;
	arr[2][2] = 7;
	arr[2][3] = 8;
	
		arr[3][0] = 5;
	arr[3][1] = 14;
	arr[3][2] = 6;
	arr[3][3] = 9;
	
	
	vector<int> v;
	v.push_back(14);
	v.push_back(3);
	v.push_back(2);
	v.push_back(4);
	v.push_back(13);
	v.push_back(1);
	v.push_back(16);
	v.push_back(11);
	v.push_back(5);
	v.push_back(15);


	int qq = solution(arr, v);
	printf("%d", qq);
}
