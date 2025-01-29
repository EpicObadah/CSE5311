#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int arr[], int n);

int main()
{
    int n = 100000; 
    int min = 1;
    int max = 100;
    int arr[n];
    double elapsedTime = 0;
    clock_t start;
    clock_t end;

    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (max-min+1) + min;
    }
    
    printf("Unsorted Array : \n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    start = clock();

    selection_sort(arr, n);

    end = clock();

    printf("Selection Sorted Array : \n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    return 0;
    
}

void selection_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
    

        for(int j= i+1; j<n; j++)
        {
            if(arr[j] < arr[min])
            {
                 min = j;
            }
        }

        if(min != i)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}