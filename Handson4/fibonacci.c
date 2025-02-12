#include <stdio.h>

int fib(int n);

int main()
{
    int n = 5;
    int result = fib (n);

    printf("fib(%d) = %d\n", n, result);

    return 0;
}

int fib(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return fib(n-1) + fib(n-2);
}