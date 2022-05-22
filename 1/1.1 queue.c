#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int * array;
};

struct Queue * createQueue(unsigned capacity) {
    struct Queue * queue = (struct Queue * ) malloc(
        sizeof(struct Queue));
    queue -> capacity = capacity;
    queue -> front = queue -> size = 0;

    queue -> rear = capacity - 1;
    queue -> array = (int * ) malloc(
        queue -> capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue * queue) {
    return (queue -> size == queue -> capacity);
}

int isEmpty(struct Queue * queue) {
    return (queue -> size == 0);
}

void enqueue(struct Queue * queue, int item) {
    if (isFull(queue))
        return;
    queue -> rear = (queue -> rear + 1) %
        queue -> capacity;
    queue -> array[queue -> rear] = item;
    queue -> size = queue -> size + 1;
    printf("add %d \n", item);
}

int dequeue(struct Queue * queue) {
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue -> array[queue -> front];
    queue -> front = (queue -> front + 1) %
        queue -> capacity;
    queue -> size = queue -> size - 1;
    printf("delete %d \n", item);
    return item;
}

void print(struct Queue * queue) {
    int i;
	printf("queue: ");
    for (i = queue -> front; i <= queue -> rear; i++) {
		if (isEmpty(queue)) printf("");
        else printf("%d ", queue -> array[i]);
	}
	printf("\n");
}

int main() {
    int i;
    struct Queue * queue = createQueue(10);
    printf("ENQUEUE 1-10\n\n");
	for (i = 1; i <= 10; i++) {
        enqueue(queue, i);
        print(queue);
    }
	printf("\n\nDEQUEUE 1-10\n\n");
    for (i = 0; i < 10; i++) {
        dequeue(queue);
        print(queue);
    }
    return 0;
}
