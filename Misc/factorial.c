#include <stdio.h>
#include <assert.h>

long int factorial(long int n)
{
    long int f = 1; // The factorial.

    while(n > 1)
    {
        f = f * n;
        n--;
        if(f == 0)
        {
            printf("%d\n", n);
            return f;
        }
    }
    return f;
}

int main()
{
    long int n = 0;
    int k = 0;
    int choose = 0;
    while(1)
    {
        printf("Please input the number to find the factorial of or -1 to exit.\n");
        scanf("%d", &n);
        if(n == -1) { break; }
        if(n < -1) { printf("Please input a positive number."); continue; }
        printf("The factorial of %d is %d\n", n, factorial(n));

        /* printf("Please input n and k (input -1 and -1 to exit).\n");
        scanf("%d", &n);
        scanf("%d", &k);
        if(n == -1 && k == -1) { break; }
        if(n < 0 || k < 0) { printf("Please input positive numbers if you do not wish to exit, and -1 for both if you do.\n"); continue; }
        if(n < k) { printf("N > K.\n"); continue; }
        choose = factorial(n) / (factorial(k) * (factorial(n - k)));
        printf("N choose k is: %d\n", choose); */

        /* /* /* /* /* */

/** /** /** */

    }
    return 0;
}
