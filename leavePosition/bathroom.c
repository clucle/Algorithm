#include <stdio.h>

int getLeaveStallsLeft(int sit);
int getLeaveStallsRight(int sit);


int main() {
	int N;
	int K;
	
	int array[72];
	int count = 0;
	
	
	scanf("%d %d", &N, &K);
	
	int iResult = N;
	
	for (; K > 0; K = K/2) {
		array[count] = K;
		count ++;
	}
	
	int iReverse = count - 1;
	
	
	for (; iReverse > 0; iReverse--) {
		
		if (array[iReverse - 1] % 2 == 0) {
			iResult = getLeaveStallsLeft(iResult);
		} else {
			iResult = getLeaveStallsRight(iResult);
		}
	}
	int iLeft = getLeaveStallsLeft(iResult);
	int iRight = getLeaveStallsRight(iResult);
	
	printf("%d %d\n", iLeft, iRight);
	
	return 0;
}

int getLeaveStallsLeft(int sit) {
	int result = sit/2;
	return result;
}
int getLeaveStallsRight(int sit) {
	int result = 0;
	if (sit % 2 == 0) result = (sit/2) - 1;
	else result = sit/2;
	
	return result;
}
