#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int*b);
int randomizedPartition(int Arr[], int pivot, int right);
int ithOrderedStatFinder(int Arr[], int pivot, int right, int i);

int main()
{
    int n = 10;
    int min = 1;
    int max = 100;
    int i = 0; 
    int ithOrderStat = 0;
    double elapsedTime = 0;
    clock_t start;
    clock_t end;
    
    srand(time(0));

    int* arr = (int*)malloc(n*sizeof(int));

    for (int i =0; i< n; i++)
    {
        arr[i] = rand() % (max - min+1) + min;
    }

    for(int i = 0; i< n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    printf("Please enter which order statistic you would like(do not go below/less size of array which is %d in this case) : ", n);
    scanf("%d", &i);
    start = clock();

    ithOrderStat = ithOrderedStatFinder(arr, 0, n-1, i);

    end = clock();
    printf("\nthe %dth order stat is %d",i , ithOrderStat);
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


//Repurposed my randomized quicksort to find the ith order statistic.
int ithOrderedStatFinder(int Arr[], int pivot, int right, int i)
{   
    if(pivot == right)
    {
        return Arr[pivot];
    }

    int q = randomizedPartition(Arr, pivot, right);
    int k = q - pivot + 1;

    if(i == k)
    {
        return Arr[q];
    }
    else if(i < k)
    {
        return ithOrderedStatFinder(Arr, pivot, q-1, i);
    }
    else
    {
        return ithOrderedStatFinder(Arr, q+1, right, i-k);
    }

}