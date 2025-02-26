#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int*b);
int randomizedPartition(int Arr[], int pivot, int right);
int randomizedQuicksort(int Arr[], int pivot, int right);

int main()
{
    int n = 10;
    int min = 1;
    int max = 100;
    double elapsedTime = 0;
    clock_t start;
    clock_t end;
    
    srand(time(0));

    int* arr = (int*)malloc(n*sizeof(int));

    for (int i =0; i< n; i++)
    {
        arr[i] = rand() % (max - min+1) + min;
    }

    start = clock();

    randomizedQuicksort(arr, 0, n-1);

    end = clock();

    elapsedTime = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    free(arr);
    return 0;
}

void swap(int *a, int*b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int randomizedPartition(int Arr[], int pivot, int right)
{
    int randIndex = pivot + rand() % (right-pivot+1);
    swap(&Arr[randIndex], &Arr[right]); 


    int pivotVal = Arr[right];
    int i = pivot-1;

    for(int j = pivot; j < right; j++)
    {
        if (Arr[j] <= pivotVal)
        {
            i = i + 1;
            swap(&Arr[i], &Arr[j]);
        }
    }

    swap(&Arr[i+1], &Arr[right]);
    return i + 1;
}

int randomizedQuicksort(int Arr[], int pivot, int right)
{
    if (pivot < right)
    {
        int q = randomizedPartition(Arr, pivot, right);
        randomizedQuicksort(Arr, pivot, q-1);
        randomizedQuicksort(Arr, q+1, right);
    }
}