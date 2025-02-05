#include <stdio.h>
#include <time.h>

void function(int n);

int main()
{
    int n = 10000;
    double elapsedTime = 0;
    clock_t start;
    clock_t end;

    start = clock();

    function(n);

    end = clock();

    elapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n\nelapsed time : %.6f seconds\n", elapsedTime);

    return 0;
    
}

void function(int n)
{
    int x = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            x = x+1;
        }
    }
}