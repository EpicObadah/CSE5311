#include <stdio.h>
#include <stdlib.h>
#define QUEUESIZE 100

typedef struct 
{
    int data[QUEUESIZE];
    int head;
    int tail;
    int length;
} Queue;

int isEmpty(Queue* Q);
void enqueue(Queue* Q, int x);
int dequeue(Queue* Q);

int main()
{
    Queue queue;
    queue.head = 0;
    queue.tail = 0;
    queue.length = QUEUESIZE;

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    printf("Queue: ");
    for (int i = queue.head; i != queue.tail; i = (i + 1) % queue.length) {
        printf("%d ", queue.data[i]);
    }
    printf("\n");

    printf("dequeue : %d\n", dequeue(&queue));
    for (int i = queue.head; i != queue.tail; i = (i + 1) % queue.length) {
        printf("%d ", queue.data[i]);
    }
    printf("\n");

    printf("dequeue : %d\n", dequeue(&queue));
    for (int i = queue.head; i != queue.tail; i = (i + 1) % queue.length) {
        printf("%d ", queue.data[i]);
    }
    printf("\n");
    return 0;
}

int isEmpty(Queue* Q)
{
    if(Q->head == Q->tail)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(Queue* Q, int x)
{
    int newTail = (Q->tail + 1) % Q->length;
    if (newTail == Q->head)
    {
        printf("Error: overflow");
        return;
    }

    Q->data[Q->tail] = x;
    Q->tail = newTail;
}

int dequeue(Queue* Q)
{
    if (isEmpty(Q))
    {
        printf("Error: underflow");
        exit(EXIT_FAILURE);
    }

    int x = Q->data[Q->head];
    Q->head = (Q->head + 1) % Q->length;
    return x;
}

