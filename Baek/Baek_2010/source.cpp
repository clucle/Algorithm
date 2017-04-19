#include <iostream>

using namespace std;
int main(){
    int T = 0;
    cin >> T;
    int num = 0;
    int result_num = 0;
    while(T--){
        cin >> num;
        result_num += (num - 1);
    }
    cout << result_num + 1;
    return 0;
}