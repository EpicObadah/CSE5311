#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int arr[], int n);

int main()
{
    int n = 1000; 
    int min = 1;
    int max = 100;
    double elapsedTime = 0;
    clock_t start;
    clock_t end;

    srand(time(0));

    int arr[n];

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

    insertion_sort(arr, n);

    end = clock();

    printf("Insertion Sorted Array : \n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    return 0;

}

void insertion_sort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j]; //swap
            j--;
        }

        arr[j+1] = key;
    }
}

