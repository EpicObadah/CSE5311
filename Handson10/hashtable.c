#include <stdio.h>
#include <stdlib.h>
#define INITIAL_SIZE 8
#define LOAD_FACTOR 0.75
#define SHRINK_THRESHOLD 0.25

typedef struct Node 
{
    int key;
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct 
{
    Node **buckets;
    int size;
    int count;
} HashTable;

unsigned int hash(int key, int size);
Node* create_node(int key, int value);
HashTable* create_table(int size);
void insert(HashTable* table, int key, int value);
void resize(HashTable* table, int newSize);
Node* search(HashTable* Table, int key);
void remove_key(HashTable* table, int key);



int main()
{
    HashTable* table = create_table(INITIAL_SIZE);
    insert(table, 10, 100);
    insert(table, 20, 200);
    insert(table, 30, 300);
    insert(table, 40, 400);
    insert(table, 50, 500);

    for(int i = 0; i < table->size; i++)
    {
        printf("[%d]: ", i);
        Node* current = table->buckets[i];
        while(current)
        {
            printf("(%d, %d) <->", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }

    Node* result = search(table,30);
    if(result)
    {
        printf("Found key %d with value %d\n", result->key, result->value);
    }

    remove_key(table,30);
    for(int i = 0; i < table->size; i++)
    {
        printf("[%d]: ", i);
        Node* current = table->buckets[i];
        while(current)
        {
            printf("(%d, %d) <->", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }

    for(int i = 0; i < table->size; i++)
    {
        Node* current = table->buckets[i];
        while(current)
        {
            Node* tmp = current;
            current = current->next;
            free(tmp);
        }
    }

    free(table->buckets);
    free(table);
    return 0;
}

unsigned int hash(int key, int size)
{
    const double A = 0.6180339887; //fraction of golden ratio
    return (int)(size * (key * A - (int)(key *A))) % size;
}

Node* create_node(int key, int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

HashTable* create_table(int size)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->buckets = (Node**)calloc(size, sizeof(Node*));
    return table;
}


void resize(HashTable* table, int newSize)
{
    HashTable* newTable = create_table(newSize);
    for(int i = 0; i < table->size; i++)
    {
        Node* current = table->buckets[i];
        while(current)
        {
            insert(newTable, current->key, current->value);
            current = current->next;
        }
    }
    free(table->buckets);
    table->buckets = newTable->buckets;
    table->size = newSize;
    table->count = newTable->count;
    free(newTable);
}

void insert(HashTable* table, int key, int value)
{
    if((float)table->count / table->size >= LOAD_FACTOR)
    {
        resize(table, table->size *2 );
    }

    unsigned int idx = hash(key, table->size);
    Node* newNode = create_node(key, value);
    if(!table->buckets[idx])
    {
        table->buckets[idx] = newNode;
    }
    else
    {
        Node* head = table->buckets[idx];
        newNode->next = head;
        head->prev = newNode;
        table->buckets[idx] = newNode;
    }
    table->count++;
}

Node* search(HashTable* table, int key)
{
    unsigned int idx = hash(key, table->size);
    Node* current = table->buckets[idx];
    while(current)
    {
        if(current->key == key)
        {
            return current;
        }
    }
    return NULL;
}

void remove_key(HashTable* table, int key)
{
    unsigned int idx = hash(key, table->size);
    Node* current = table->buckets[idx];
    while(current)
    {
        if(current->key == key)
        {
            if(current->prev)
            {
                current->prev->next = current->next;
            }
            else if(current->next)
            {
                current->next->prev = current->prev;
            }
            else if(current == table->buckets[idx])
            {
                table->buckets[idx] = current->next;
            }
            free(current);
            table->count--;
            if((float)table->count / table->size <= SHRINK_THRESHOLD && table->size > INITIAL_SIZE)
            {
                resize(table, table->size / 2);
            }
            return;
        }
        current = current->next;
    }
}

