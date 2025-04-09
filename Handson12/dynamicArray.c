#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *array;
    int size;
    int capacity;
} DynamicArray;

void resizeArray(DynamicArray *arr);
void addElement(DynamicArray *arr, int element);
int getElement(DynamicArray *arr, int index);

int main()
{
    DynamicArray arr;
    arr.array = (int *)malloc(2 * sizeof(int));
    arr.size = 0;
    arr.capacity = 2;

    addElement(&arr, 11);
    addElement(&arr, 19);
    addElement(&arr, 100);
    addElement(&arr, 5);
    addElement(&arr, 3);
    addElement(&arr, 1);

    for(int i = 0; i < arr.size; i++)
    {
        printf("Element at index %d: %d\n", i, getElement(&arr,i));
    }

    free(arr.array);
    arr.array = NULL;
    arr.size = 0;
    arr.capacity = 0;
    return 0;
}

void resizeArray(DynamicArray *arr)
{
    arr->capacity *= 2;
    arr->array = (int *)realloc(arr->array, arr->capacity * sizeof(int));
    if(!arr->array)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }
}

void addElement(DynamicArray *arr, int element)
{
    if (arr->size == arr->capacity)
    {
        resizeArray(arr);
    }

    arr->array[arr->size] = element;
    arr->size++;
}

int getElement(DynamicArray *arr, int index)
{
    if(index < 0 || index >= arr->size)
    {
        printf("Index out of bounds\n");
        exit(1);
    }
    return arr->array[index];
}

