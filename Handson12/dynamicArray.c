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
void deleteElement(DynamicArray *arr, int index);

int main()
{
    DynamicArray arr;
    arr.array = (int *)malloc(2 * sizeof(int));
    arr.size = 0;
    arr.capacity = 2;

    printf("\nInserting elements into the dynamic array which is currently empty.\n\n");

    addElement(&arr, 11);
    addElement(&arr, 19);
    addElement(&arr, 100);
    addElement(&arr, 5);
    addElement(&arr, 3);
    addElement(&arr, 1);

    printf("Array after inserting 6 elements\n");

    for(int i = 0; i < arr.size; i++)
    {
        printf("Element at index %d: %d\n", i, getElement(&arr,i));
    }

    deleteElement(&arr, 1);

    printf("\n\nArray after deleting the element at index 1\n");

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

void deleteElement(DynamicArray *arr, int index)
{
    if(index < 0 || index >= arr->size)
    {
        printf("Index out of bounds\n");
        exit(1);
    }

    for(int i = index; i < arr->size - 1; i++)
    {
        arr->array[i] = arr->array[i+1];
    }

    arr->size--;
}