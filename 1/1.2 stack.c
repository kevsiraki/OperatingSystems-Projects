#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};
 
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}
 
void push(struct Stack* stack, int item, _Bool toPrint) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    if(toPrint) printf("push: %d \n", item);
}
 
int pop(struct Stack* stack, _Bool toPrint) {
    if (isEmpty(stack))
        return INT_MIN;
    if(toPrint) printf("pop %d \n", stack->array[stack->top] +1);
    return stack->array[stack->top--];
}

void print(struct Stack * stack) {
	if (isEmpty(stack)) 
		return;
    int x = stack->top;
    pop(stack,0);
	printf("%d ",x+1);
	print(stack);
    push(stack,x,0);
}
 
int main() {
    struct Stack* stack = createStack(10);
    int i;
 	printf("PUSH 1-10\n\n");
	for (i = 1; i <= 10; i++) {
        push(stack, i,1);
        printf("stack: ");
		print(stack);
        printf("\n");
    }
	printf("\n\nPOP 1-10\n\n");
    for (i = 0; i < 10; i++) {
        pop(stack,1);
        printf("stack: ");
        print(stack);
        printf("\n");
    }
    return 0;
}
