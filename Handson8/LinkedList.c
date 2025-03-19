#include <stdio.h>
#include <stdlib.h>
#define LLSIZE 100

typedef struct
{
    int key;
    int next; 
    int prev;
} Node;

typedef struct
{
    Node nodes[LLSIZE];
    int head;
    int free;
} LinkedList;

int nodeAlloc(LinkedList* L);
void freeNode(LinkedList* L, int index);
int listSearch(LinkedList* L, int k);
void listInsert(LinkedList* L, int key);
void listDelete(LinkedList* L, int x);
int isEmpty(LinkedList* L);


int main()
{   
    LinkedList linkedlist;
    linkedlist.head = -1;
    linkedlist.free = 0;
    int x = 0;
    for (int i = 0; i < LLSIZE - 1; i++) 
    {
        linkedlist.nodes[i].next = i + 1;
    }
    linkedlist.nodes[LLSIZE - 1].next = -1;
    int node = 0;

    printf("\nIs the linked list currently empty? %s\n", isEmpty(&linkedlist) ? "yes" : "No");

    printf("\nNow filling linkedlist with values\n");
    listInsert(&linkedlist, 10);
    listInsert(&linkedlist, 20);
    listInsert(&linkedlist, 30);
    x = linkedlist.head;
    printf("List: ");
    while (x != -1) 
    {
        printf("%d ", linkedlist.nodes[x].key);
        x = linkedlist.nodes[x].next;
    }


    printf("\n\nIs the linked list currently empty? %s\n", isEmpty(&linkedlist) ? "yes" : "No");
    node = listSearch(&linkedlist, 20); //searches for a specified node and selects it

    printf("\nDeleting node with value 20\n");
    if (node != -1)
    {
        listDelete(&linkedlist, node);
    }
    x = linkedlist.head;
    printf("List: ");
    while (x != -1) 
    {
        printf("%d ", linkedlist.nodes[x].key);
        x = linkedlist.nodes[x].next;
    }

    return 0;
}

int nodeAlloc(LinkedList* L) 
{
    if (L->free == -1) 
    {
        printf("Error: List overflow\n");
        return -1;
    }
    int newNode = L->free;
    L->free = L->nodes[newNode].next;
    return newNode;
}

void freeNode(LinkedList* L, int index) 
{
    L->nodes[index].next = L->free;
    L->free = index;
}

int listSearch(LinkedList* L, int k) 
{
    int x = L->head;
    while (x != -1 && L->nodes[x].key != k) 
    {
        x = L->nodes[x].next;
    }
    return x;
}

void listInsert(LinkedList* L, int key) 
{
    int x = nodeAlloc(L);
    if (x == -1)
    {
        return;
    } 
    
    L->nodes[x].key = key;
    L->nodes[x].next = L->head;
    L->nodes[x].prev = -1;
    if (L->head != -1) 
    {
        L->nodes[L->head].prev = x;
    }
    L->head = x;
}

void listDelete(LinkedList* L, int x) 
{
    if (x == -1) 
    {
        return;
    }
    if (L->nodes[x].prev != -1) 
    {
        L->nodes[L->nodes[x].prev].next = L->nodes[x].next;
    } 
    else 
    {
        L->head = L->nodes[x].next;
    }
    if (L->nodes[x].next != -1) 
    {
        L->nodes[L->nodes[x].next].prev = L->nodes[x].prev;
    }
    freeNode(L, x);
}


int isEmpty(LinkedList* L)
{
    if(L->head == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}