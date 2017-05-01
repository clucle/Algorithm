#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node {
	int data;
	Node* Node;
}Node;


void addNode(Node* head, int data);
void DelNode(Node* head);

int main() {
	int N;
	scanf("%d", &N);
	
	if (N == 1) {
		printf("0");
		return 0;
	}
	
	int j;
	
	Node* head1 = (Node*)malloc(sizeof(Node));
	head1->data = -1;
	head1->Node = NULL;
	
	addNode(head1, N);
	
	Node* head2 = (Node*)malloc(sizeof(Node));
	head2->data = -1;
	head2->Node = NULL;
	
	int count = 0;
	
	Node* tmpNode;
	
	for (j = 0; j < N; j++) {
		count++;
		tmpNode = head1->Node;
		//printf("%d\n", tmpNode->data);
		while (tmpNode != NULL) {
			
			if(tmpNode->data%3 == 0) {
				if (tmpNode->data / 3 == 1) {
					j = N;
					break;
				}

				addNode(head2, tmpNode->data / 3);
			}
			if(tmpNode->data%2 == 0) {
				if (tmpNode->data / 2 == 1) {
					j = N;
					break;
				}
				addNode(head2, tmpNode->data / 2);
			}
			
			if (tmpNode->data == 1) {
				j = N;
				break;
			}
			addNode(head2, tmpNode->data - 1);
			tmpNode = tmpNode->Node;
		}
		
		DelNode(head1);
		head1->Node = head2->Node;
		head2->Node = NULL;
	}
	printf("%d", count);

	return 0;
}

void addNode(Node* head, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->Node = head->Node;
	head->Node = newNode;
}

void DelNode(Node* head) {
	Node* tmpNode, *DelNode;
	tmpNode = head->Node;
	head->Node = NULL;
	while (tmpNode != NULL) {
		DelNode = tmpNode;
		tmpNode = tmpNode->Node;
		free(DelNode);
	}
	
}
