#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    int value; 
    int arrayIndex; 
    int elementIndex; 
} HeapNode;

void swap(HeapNode *a, HeapNode *b);
void heapify(HeapNode heap[], int size, int root);
void mrgSortedArr(int arr[][4], int K, int N, int output[]);

int main() 
{
    clock_t start;
    clock_t end;
    double elapsedTime = 0;


    int K = 3;
    int N = 4;
    int unsortArr[3][4] = {{1, 3, 5, 7},
                     {2, 4, 6, 8}, 
                     {0, 9, 10, 11}};
                     

    int output[K *N];
    start = clock();
    mrgSortedArr(unsortArr, 3, 4, output);
    end = clock();

    printf("Merged array: ");
    
    for (int i = 0; i < K*N; i++) 
    {
        printf("%d ", output[i]);
    }

    printf("\n\n");
    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);
    return 0;
}

//generic swap function for heap nodes
void swap(HeapNode *a, HeapNode *b) 
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(HeapNode heap[], int size, int root) 
{
    int smallest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    if (left < size && heap[left].value < heap[smallest].value) 
    {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value) 
    {
        smallest = right;
    }
    if (smallest != root) { swap(&heap[root], &heap[smallest]); heapify(heap, size, smallest); }
    

}


void mrgSortedArr(int arr[][4], int K, int N, int output[]) 
{
    HeapNode heap[K]; 
    int size = K;
    int index = 0;
    
    
    for (int i = 0; i < K; i++) 
    {
        heap[i] = (HeapNode){arr[i][0], i, 0};
    }
    for (int i = (K - 1) / 2; i >= 0; i--) 
    {
        heapify(heap, K, i);
    }
    
    while (size > 0) 
    {
        output[index++] = heap[0].value;
        int arrIndx = heap[0].arrayIndex;
        int elementIndx = ++heap[0].elementIndex;
        heap[0] = (elementIndx < N) ? (HeapNode){arr[arrIndx][elementIndx], arrIndx, elementIndx} : heap[--size];
        heapify(heap, size, 0);
    }
}