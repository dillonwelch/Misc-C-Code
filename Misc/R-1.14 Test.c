#include <stdio.h>

int main()
{
    int n = 50;
    int count = 0;

    int s = 0;
    int i, j;
    int holder = n*n;
    for(i = 1; i <= holder; i++)
    {
        for(j = 1; j <= i; j++)
        {
            s += i;
            count++;
        }
    }

    printf("S: %d\nCount: %d\n", s, count);

    return 0;
}
