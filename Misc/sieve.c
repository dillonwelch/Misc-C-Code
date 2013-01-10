#include <stdio.h>

#define AMOUNT 30

int main(int argc, char *argv[])
{
    int total;
    int printFinalOnly;
    if(argc > 1)
    {
        total = atoi(argv[1]);
        if(argc > 2)
        {
            printFinalOnly = 1;
        }
        else
        {
            printFinalOnly = 0;
        }
    }
    else
    {
        total = AMOUNT;
    }
    int index = 0;
    int number = 2;
    int sieve[total];
    sieve[index] = number;
    index++;
    number++;
    int test = 1;
    for(; index < total; number++)
    {
        int i = 0;
        test = 1;
        while(i < index && sieve[i] * sieve[i] <= number)
        {
            if(number % sieve[i] == 0)
            {
                test = 0;
                break;
            }
            else
            {
                i++;
            }
        }
        if(test == 1)
        {
            sieve[index] = number;
            index++;
        }
    }
    if(printFinalOnly == 0)
    {
        for(index = 0; index < total; index++)
        {
            printf("Prime #%d is :%d\n", index + 1, sieve[index]);
        }
    }
    else
    {
        printf("Prime #%d is: %d\n", total, sieve[total - 1]);
    }
}
