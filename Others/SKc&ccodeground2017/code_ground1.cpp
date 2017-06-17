#include <string>
#include <stdlib.h>
using namespace std;


int solution(string N) {
    int answer = 0;
    
    unsigned long long int arr[10];
    
    
    
    int i;
    for (i = 0; i < 10; i++) {
    	arr[i] = 0;
	}
	
	for (i = 0; i < N.size(); i++) {

    	arr[N.at(i) - 48]++;
	}
	
    for (i = 1; i < 10; i++) {
    	// 짝수개 이상 있으면 0 제외 
    	if (arr[i] > 1) {
    		if (arr[i] % 2 == 0) {
    			answer += arr[i];
    			arr[i] = 0;
			} else {
				answer += (arr[i] - 1);
				arr[i] = 1;
			}	
		}
	}
	if (answer > 0) {
		if (arr[0] > 1) {
    		if (arr[0] % 2 == 0) {
    			answer += arr[0];
    			arr[0] = 0;
			} else {
				answer += (arr[0] - 1);
				arr[0] = 1;
			}
		}
	}
	
	for (i = 1; i < 10; i++) {
		if (arr[i] > 0) {
			answer++;
			break;
		}
	}
	
    return answer;
}

int main() {
	printf("%d", solution("1213002"));
	return 0;
}
