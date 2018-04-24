#include <stdio.h>
#include <stdlib.h>

struct node {
    int k;
    struct node* left;
    struct node* right;
};

int main() {
    int N;
    scanf("%d", &N);

    struct node* head = (struct node*)malloc(sizeof(node));
    struct node* tmp = head;
    head -> k = 1;
    int i;
    for (i = 2; i <= N; i++) {
        struct node* newNode = (struct node*)malloc(sizeof(node));
        newNode -> k = i;
        newNode -> left = tmp;
        
        tmp->right = newNode;
        tmp = newNode;
    }
    tmp->right = head;
    head->left = tmp;

    tmp = head;
    
    int M;
    scanf("%d", &M);

    int k;
    struct node* tmpLeft;
    struct node* tmpRight;
    int left, right;
    int sum = 0;
    while(M--) {
        scanf("%d", &k);
        tmpLeft = tmp;
        tmpRight = tmp;
        left = 0;
        right = 0;
        while (tmpLeft -> k != k) {
            left++;
            tmpLeft = tmpLeft->left;
        }
        while (tmpRight -> k != k) {
            right++;
            tmpRight = tmpRight->right;
        }
        if (left > right) {
            tmp = tmpRight;
            sum += right;
        } else {
            tmp = tmpLeft;
            sum += left;
        }

        tmpLeft = tmp->left;
        tmpRight = tmp->right;
        free(tmp);
        if (tmp == tmpLeft) {
            break;
        }
        tmpLeft->right = tmpRight;
        tmpRight->left = tmpLeft;
        tmp = tmp->right;
    }
    printf("%d", sum);
}