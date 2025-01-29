#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int arr[], int n);

int main()
{
    int n = 250000; 
    int min = 1;
    int max = 100;
    double elapsedTime = 0;
    clock_t start;
    clock_t end;

    srand(time(0));

    int* arr = (int*)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (max-min+1) + min;
    }
/*
    printf("Unsorted Array : \n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
*/
    printf("\n");

    start = clock();

    bubble_sort(arr, n);

    end = clock();
/*
    printf("Insertion Sorted Array : \n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
*/
    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    free(arr);
    return 0;
}

void bubble_sort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}