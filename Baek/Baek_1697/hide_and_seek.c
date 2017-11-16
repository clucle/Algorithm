#include <stdio.h>
#include <stdlib.h>

int f_min(int a, int b) { return (a < b) ? a : b; }

typedef struct node node;
struct node
{
    node *next;
    int me;
    int count;
};

int arr[100001] = {
    0,
};
int you;
node *last;

int main()
{
    int me;
    scanf("%d %d", &me, &you);

    node *q = (node *)malloc(sizeof(node));
    q->next = NULL;
    q->me = me;
    q->count = 0;
    last = q;

    while (q != NULL)
    {
        
        int me = q->me;

        if (me == you)
        {
            printf("%d", q->count);
            break;
        }

        if ((me * 2 < 100001) && arr[me * 2] == 0)
        {
            arr[2 * me] = 1;
            node *tmp = (node *)malloc(sizeof(node));
            last->next = tmp;
            tmp->me = me * 2;
            tmp->next = NULL;
            tmp->count = q->count + 1;
            last = tmp;
        }
        if (arr[me - 1] == 0)
        {
            arr[me - 1] = 1;
            node *tmp = (node *)malloc(sizeof(node));
            last->next = tmp;
            tmp->me = me - 1;
            tmp->next = NULL;
            tmp->count = q->count + 1;
            last = tmp;
        }
        if (arr[me + 1] == 0)
        {
            arr[me + 1] = 1;
            node *tmp = (node *)malloc(sizeof(node));
            last->next = tmp;
            tmp->me = me + 1;
            tmp->next = NULL;
            tmp->count = q->count + 1;
            last = tmp;
        }
        node* tmp = q;
        q = q->next;
        free(tmp);
    }
}
