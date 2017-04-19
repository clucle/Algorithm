#include <iostream>
 
using namespace std;
int main() {
    int T;
    cin >> T;
    int num;
    int arr[50];
    int arr_plus[50] = { 0, };
    for(int i = 0; i < T; i++){
        cin >> num;
        arr[i] = num;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                arr_plus[j]++;
            }else{
                arr_plus[i]++;
            }
        }
    }
    for (int i = 0; i < T; i++) {
        cout << arr_plus[i];
        if (i != T - 1) cout << " ";
    }
    return 0;
}