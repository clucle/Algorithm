#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <cstdio>

using namespace std;

set<string> retSaved;
set<char> savedPositionAlpha[11];
int N, L;
string retString;
int myend = 0;

void findString(int index, string prev) {
    if (myend == 1) return ;

    set<char>::iterator iter;
    for (iter = savedPositionAlpha[index].begin();
        iter != savedPositionAlpha[index].end(); ++iter) {

        set<string>::iterator iter2;
        int isNotExist = 1;
        for (iter2 = retSaved.begin(); iter2 != retSaved.end(); ++iter2){
            if (prev + (*iter) == (*iter2).substr(0, index + 1)) {
                isNotExist = 0;
            }
        }

        if (isNotExist) {
            retString = prev + (*iter) + (*retSaved.begin()).substr(index + 1);
            myend = 1;
            return ;
        } else {
            if (index < L) findString(index + 1, prev + (*iter));
        }
    }
}



int main() {
    int T;

    scanf("%d", &T);
    int t = 1;
    string s;

    char buffer[100];

    int i, j;
    for (t = 1; t <= T; t++) {
        scanf("%d %d", &N, &L);
        for (i = 0; i < N; i++) {
            scanf("%10s", buffer);
            retSaved.insert(buffer);
            for (j = 0; j < L; j++) {
                savedPositionAlpha[j].insert(buffer[j]);
            }
        }

        retString = "-";
        myend = 0;
        findString(0, "");

        printf("Case #%d: %s\n", t, retString.c_str());
       
        retSaved.clear();
        for (j = 0; j < L; j++) {
            savedPositionAlpha[j].clear();
        }
    }    
}