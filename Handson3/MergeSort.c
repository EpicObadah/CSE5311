#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

int main()
{
    clock_t start;
    clock_t end;
    double elapsedTime = 0;
    int arr[] = {5,2,4,7,1,3,2,6};
    int size = sizeof(arr) / sizeof(arr[0]);

    srand(time(0));

    printf("unsorted arry : \n");

    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    start = clock();

    mergeSort(arr, 0, size - 1);

    end = clock();

    printf("Sorted array: \n");

    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    return 0;
}

void merge(int arr[], int left, int mid, int right)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int sizeLeft = mid-left + 1;
    int sizeRight = right - mid;
    int tmpLeft[sizeLeft];
    int tmpRight[sizeRight];

    for(i = 0; i < sizeLeft; i++)
    {
        tmpLeft[i] = arr[left + i];
    
        for(j = 0; j < sizeRight; j++)
        {
            tmpRight[j] = arr[mid + 1 + j];
        }
    }

    i = 0;
    j = 0;
    k = left;
    while(i < sizeLeft && j < sizeRight)
    {
        if(tmpLeft[i] <= tmpRight[j])
        {
            arr[k] = tmpLeft[i];
            i++;
        }
        else
        {
            arr[k] = tmpRight[j];
            j++;
        }
        k++;
    }

    while (i < sizeLeft)
    {
        arr[k] = tmpLeft[i];
        i++;
        k++;
    }

    while (j < sizeRight)
    {
        arr[k] = tmpRight[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if(left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}