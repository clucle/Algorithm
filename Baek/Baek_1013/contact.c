#include <stdio.h>
#include <string.h>

int get0[10] = {6, 2, 3, 3, 6, 8, 9, 6, 3, 9};
int get1[10] = {1, 9, 9, 4, 5, 5, 7, 1, 7, 9};

int main() {

    int T;
    char k[201];

    scanf("%d", &T);

    while(T--) {
        scanf("%s", k);

        int len = strlen(k);
        int i;
        int state = 0;
        for (i = 0; i < len; i++) {
            if (state == 9) break;
            if (k[i] == '0') state = get0[state];
            else state = get1[state];
        }

        if (state == 4 || state == 5 || state == 7) printf ("YES\n");
        else printf("NO\n");
    }

    return 0;
}