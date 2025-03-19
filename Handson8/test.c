#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 100 // Define the maximum size of the stack

typedef struct {
    int data[STACK_SIZE];
    int top;
} Stack;

// Function to initialize the stack
void initializeStack(Stack* S) {
    S->top = 0;
}

// Function to check if the stack is empty
bool stackEmpty(Stack* S) {
    return S->top == 0;
}

// Function to push an element onto the stack
void push(Stack* S, int x) {
    if (S->top == STACK_SIZE) {
        printf("Error: Stack overflow\n");
        return;
    }
    S->data[S->top] = x;
    S->top = S->top + 1;
}

// Function to pop an element from the stack
int pop(Stack* S) {
    if (stackEmpty(S)) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    S->top = S->top - 1;
    return S->data[S->top];
}

// Function to display stack contents (for testing)
void displayStack(Stack* S) {
    printf("Stack: ");
    for (int i = 0; i < S->top; i++) {
        printf("%d ", S->data[i]);
    }
    printf("\n");
}

int main() {
    Stack S;
    initializeStack(&S);
    
    push(&S, 10);
    push(&S, 20);
    push(&S, 30);
    displayStack(&S);
    
    printf("Popped: %d\n", pop(&S));
    displayStack(&S);
    
    printf("Popped: %d\n", pop(&S));
    displayStack(&S);
    
    return 0;
}
