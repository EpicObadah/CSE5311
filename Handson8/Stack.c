#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 100

typedef struct
{
    int data[STACKSIZE];
    int top;
} Stack;

int isEmpty(Stack* S);
void push(Stack* S, int x);
int pop(Stack* S);

int main()
{
    Stack stack;
    stack.top = 0;

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("current stack: ");
    for (int i = 0; i < stack.top; i++)
    {
        printf("%d ", stack.data[i]);
    }

    printf("\n");

    printf("first pop : %d\n", pop(&stack));
    for (int i = 0; i < stack.top; i++)
    {
        printf("%d ", stack.data[i]);
    }

    printf("\nsecond pop : %d\n", pop(&stack));
    for (int i = 0; i < stack.top; i++)
    {
        printf("%d ", stack.data[i]);
    }
}



int isEmpty(Stack* S)
{
    if(S->top == 0)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
    
}

void push(Stack* S, int x)
{
    if (S->top == STACKSIZE)
    {
        printf("Stack overflow\n");
        return;
    }

    S->data[S->top] = x;
    S->top = S->top + 1;
}

int pop(Stack* S)
{
    if (isEmpty(S))
    {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    
    S->top = S->top - 1;
    return S->data[S->top];
}

