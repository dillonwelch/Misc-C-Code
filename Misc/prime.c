#include <stdio.h>
#include <math.h>   // Square root

// Tests if a number is prime. Returns true if it's prime, false if not (or if it's 0 or 1)
int prime (int n)
{
    int isPrime = 0;
    if(n < 2)
    {
        return isPrime;
    }
    else
    {
	int z;
        for (z = 2; z <= sqrt((double)(n)); z++)
        {
            if(n % z == 0)
            {
		printf("%d is divided by %d\n", n, z);
                return isPrime;
            }
        }
	isPrime = 1;
        return isPrime;
    }
}

int main(int argc, char *argv[])
{
	prime(atoi(argv[1]));
}
