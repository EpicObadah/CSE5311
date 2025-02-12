#include <stdio.h>
#include <time.h>

int removeDuplicates(int array[], int N);


int main() 
{
    clock_t start;
    clock_t end;
    double elapsedTime = 0;
    int array[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    int N = sizeof(array) / sizeof(array[0]);

    start = clock();
    int newSize = removeDuplicates(array, N);
    end = clock();

    printf("Array with duplicates removed: ");

    for (int i = 0; i < newSize; i++) 
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    return 0;
}

int removeDuplicates(int array[], int N) 
{
    if (N == 0) 
    {
        return 0; 
    }

    int newIndex = 1; 

    for (int i = 1; i < N; i++) 
    {
        if (array[i] != array[i - 1]) 
        { 
            array[newIndex++] = array[i]; 
        }
    }

    return newIndex; 
}