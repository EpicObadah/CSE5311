#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    void **data;
    int size;
    int capacity;
    size_t dataSize;
    int (*compare)(const void*, const void*);
} MinHeap;


int parent(int i) { return (i - 1) >> 1; }
int leftChild(int i) { return (i << 1) | 1; }
int rightChild(int i) { return (i + 1) << 1; }


void swap(void **a, void **b);
void heapify(MinHeap *heap, int root);
void build_min_heap(MinHeap *heap);
void push(MinHeap *heap, void *element);
void* pop(MinHeap *heap);
MinHeap* create_heap(int capacity, size_t dataSize, int (*compare)(const void*, const void*));
int int_compare(const void *a, const void *b);
void print_heap(MinHeap *heap);


int main()
{
    MinHeap *heap = create_heap(10, sizeof(int), int_compare);
    int values[] = {4, 10, 3, 5, 1};
    
    printf("Inserting values by pushing: ");
    for (int i = 0; i < 5; i++) 
    {
        printf("%d ", values[i]);
        push(heap, &values[i]);
    }
    printf("\n\n");
    
    printf("Heap after inserting values (heapified): ");
    for (int i = 0; i < heap->size; i++) 
    {
        printf("%d ", *(int*)heap->data[i]);
    }
    printf("\n\n");
    
    build_min_heap(heap);
    
    printf("Heap after build_min_heap: ");
    for (int i = 0; i < heap->size; i++) 
    {
        printf("%d ", *(int*)heap->data[i]);
    }
    printf("\n\n");
    
    printf("Heap order (popping): ");
    while (heap->size) 
    {
        int *minVal = (int*) pop(heap);
        printf("%d ", *minVal);
    }
    printf("\n\n");
    
    free(heap->data);
    free(heap);
    return 0;
}

void swap(void **a, void **b) 
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int root) 
{
    int smallest = root;
    int left = leftChild(root);
    int right = rightChild(root);

    if (left < heap->size && heap->compare(heap->data[left], heap->data[smallest]) < 0) 
        smallest = left;
    if (right < heap->size && heap->compare(heap->data[right], heap->data[smallest]) < 0) 
        smallest = right;
    
    if (smallest != root) 
    { 
        swap(&heap->data[root], &heap->data[smallest]); 
        heapify(heap, smallest); 
    }
}

void build_min_heap(MinHeap *heap) 
{
    for (int i = (heap->size - 2) >> 1; i >= 0; i--) 
    {
        heapify(heap, i);
    }
}
void push(MinHeap *heap, void *element) 
{
    if (heap->size == heap->capacity) 
    {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(void*));
    }
    heap->data[heap->size] = element;
    int i = heap->size++;
    while (i > 0 && heap->compare(heap->data[i], heap->data[parent(i)]) < 0) 
    {
        swap(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

void* pop(MinHeap *heap) 
{
    if (heap->size == 0) return NULL;
    void *root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);
    return root;
}

MinHeap* create_heap(int capacity, size_t dataSize, int (*compare)(const void*, const void*)) 
{
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->data = malloc(capacity * sizeof(void*));
    heap->size = 0;
    heap->capacity = capacity;
    heap->dataSize = dataSize;
    heap->compare = compare;
    return heap;
}

int int_compare(const void *a, const void *b) 
{
    return (*(int*)a - *(int*)b);
}

