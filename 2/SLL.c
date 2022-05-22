/*
Kevin Siraki
COMP 322
Singly Linked List
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;                        
    struct node *next;           
} *firstNode;

void print() {
    struct node *tmp;
    int i = 1;
    if(firstNode == NULL) printf("NULL list.");
    else {
        tmp = firstNode;
        while(tmp != NULL) {
            printf("node %d = %d\n", i, tmp->data);       
            tmp = tmp->next; 
			i++;                    
        }
    }
} 

void makeSLL(int n) {
    struct node *nextNode, *tmp;
    int data, i;
    firstNode = (struct node *)malloc(sizeof(struct node));
    if(firstNode == NULL) printf("Cannot allocate.");
    else {
        printf("enter node 1: ");
        scanf("%d", &data);
        firstNode->data = data;      
        firstNode->next = NULL; 
        tmp = firstNode;
        for(i=2; i<=n; i++) {
            nextNode= (struct node *)malloc(sizeof(struct node));
            if(nextNode == NULL) {
                printf("Cannot allocate.");
                break;
            }
            else {
                printf("enter node %d: ", i);
                scanf(" %d", &data);
                nextNode->data = data;      
                nextNode->next = NULL; 
                tmp->next = nextNode; 
                tmp = tmp->next; 
            }
        }
    }
}

int main() {
    int n;
    printf("Size of SLL: ");
    scanf("%d", &n);
    makeSLL(n);
    printf("\nSLL Contents: \n");
    print();
    return 0;
}

