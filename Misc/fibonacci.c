#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Fibonacci numbers defined as:
 * F(0) = 0.
 * F(1) = 1.
 * F(n) = F(n-1) + F(n-2).
 */

double* rawr; // Array to store calculated fibonacci numbers.

/*
 * Fibonacci:
 * Takes a number and calculates its fibonacci number.
 */
double fibonacci(int number)
{
    double fib = number;
    if(number == 0) // F(0).
    {
        return 0;
    }
    else if(number == 1) // F(1).
    {
        return 1;
    }
    else
    {
        if(rawr[number] != '\0') // If this fibonacci has already been calculated, get it from the array.
        {
            return rawr[number];
        }
        else // Otherwise calculate the previous two numbers, and then store the number in rawr.
        {
            fib = fibonacci(fib - 1) + fibonacci(fib - 2);
            rawr[number] = fib;
            return fib;
        }
    }
}

int main(int argc, char* argv[])
{
    int n = 0;   // Fibonacci number to calculate.
    int FIBLEN;  // Length of fibonacci array (rawr).
    int display;  // Whether to display the rest of the fibonacci numbers.
    if(argc > 1) // If a value was passed in.
    {
        n = atoi(argv[1]);
        if(argc > 2)
        {
            display = 1;
        }
        else
        {
            display = 0;
        }
    }
    else         // Otherwise get one from the user.
    {
        printf("Input the value for n: ");
        scanf("%d", &n);
    }
    FIBLEN = n;

    int index = 0;
    rawr = malloc((FIBLEN + 1) * sizeof(double));
    rawr[0] = 0; // F(0) = 0.
    rawr[1] = 1; // F(1) = 1.
    int i = 2;
    for(; i < FIBLEN + 1; i++) // NULL out the rest of the array.
    {
        rawr[i] = '\0';
    }

    double fib = fibonacci(n);
    if(display == 1)
    {
        for(i = 0; i < FIBLEN; i++)
        {
            printf("F(%d) is: %.0f\n", i, rawr[i]);
        }
    }
    printf("F(%d) is: %.0f\n", n, fib);
    return 0;
}
