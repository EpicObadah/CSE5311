#include <stdio.h>
#include <stdlib.h>
#define ENLARGE_THRESHOLD 0.75 // used to enlarge the table if it is over 3/4 full in this case. Used define to avoid hardcoring
#define SHRINK_THRESHOLD 0.25 // used to shrink and rehash the table if 1/4 empty in this case. used define to avoid hardcoding
#define SIZEINIT 8

//my doubly linked list structure
typedef struct LL 
{
    int key;
    int hashValue;
    struct LL *prev;
    struct LL *next;
} LL;
//my hashtable structure
typedef struct 
{
    LL **buckets;
    int size;
    int count;
} HashTable;

//my function prototypes
unsigned int hash(int key, int size);
LL* create_node(int key, int value);
HashTable* create_table(int size);
void insert(HashTable* table, int key, int value);
void resize(HashTable* table, int newSize);
LL* search(HashTable* Table, int key);
void remove_key(HashTable* table, int key);



int main()
{
    HashTable* hashtable = create_table(SIZEINIT);
    LL* result = NULL;
    printf("Inserting values into hash table\n\n");
    //inserting keys and values
    insert(hashtable, 12345, 85);
    insert(hashtable, 12346, 90);
    insert(hashtable, 12347, 78);
    insert(hashtable, 12348, 92);
    insert(hashtable, 12349, 88); 

    //show filled table
    for(int i = 0; i < hashtable->size; i++)
    {
        printf("[%d]: ", i);
        LL* current = hashtable->buckets[i];
        while(current)
        {
            printf("(%d, %d) <-> ", current->key, current->hashValue);
            current = current->next;
        }
        printf("NULL\n");
    }
    
    result = search(hashtable,12345); //searching hashtable for a selected key. In this case, 15.
    //if the key is found, it'll print it plus its value
    //if the key isn't found, it'll say it could not find the key.
    if(result)
    {
        printf("\nFound key %d with value %d\n", result->key, result->hashValue);
    }
    else
    {
        printf("Could not find key %d\n", result->key);
    }
    
    printf("\nremoving key %d\n\n", result->key);
    remove_key(hashtable,12345); // removes a selected key.
    
    //show updated table
    for(int i = 0; i < hashtable->size; i++)
    {
        printf("[%d]: ", i);
        LL* current = hashtable->buckets[i];
        while(current)
        {
            printf("(%d, %d) <-> ", current->key, current->hashValue);
            current = current->next;
        }
        printf("NULL\n");
    }
    
    //clear out the table before ending
    for(int i = 0; i < hashtable->size; i++)
    {
        LL* current = hashtable->buckets[i];
        while(current)
        {
            LL* tmp = current;
            current = current->next;
            free(tmp);
        }
    }

    free(hashtable->buckets);
    free(hashtable);
    return 0;
}

unsigned int hash(int key, int size)
{
    const double A = 0.6180339887; //fraction of golden ratio
    return (int)(size * (key * A - (int)(key *A))) % size;
}

LL* create_node(int key, int value)
{
    LL* newNode = (LL*)malloc(sizeof(LL));
    newNode->key = key;
    newNode->hashValue = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

HashTable* create_table(int size)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->buckets = (LL**)calloc(size, sizeof(LL*));
    return table;
}


void resize(HashTable* table, int newSize)
{
    HashTable* newTable = create_table(newSize);
    
    //rehashes the new table depending on the new size that was needed
    for(int i = 0; i < table->size; i++)
    {
        LL* current = table->buckets[i];
        while(current)
        {
            insert(newTable, current->key, current->hashValue);
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
    LL* newNode = NULL;
    //dose the table need to be resized?
    if((float)table->count / table->size >= ENLARGE_THRESHOLD)
    {
        resize(table, table->size *2 );
    }

    unsigned int idx = hash(key, table->size);
    newNode = create_node(key, value);
    
    //inserts to linked list using chaining
    if(!(table->buckets[idx]))
    {
        table->buckets[idx] = newNode;
    }
    else
    {
        LL* head = table->buckets[idx];
        newNode->next = head;
        head->prev = newNode;
        table->buckets[idx] = newNode;
    }
    table->count++;
}

LL* search(HashTable* table, int key)
{
    unsigned int idx = hash(key, table->size);
    LL* current = table->buckets[idx];
    while(current)
    {
        if(current->key == key)
        {
            return current; //returns the node if the key was found
        }
    }
    return NULL; //if the key was not found, returns null
}

void remove_key(HashTable* table, int key)
{
    unsigned int idx = hash(key, table->size);
    LL* current = table->buckets[idx];
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
            
            //does the tible need to shrink?
            if((float)table->count / table->size <= SHRINK_THRESHOLD && table->size > SIZEINIT)
            {
                resize(table, table->size / 2); //shrinks the table by half if it needs to shrink.
            }
            return;
        }
        current = current->next;
    }
}

