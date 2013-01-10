#include <stdio.h>
#include <math.h>

double remainder(double a, double b)
{
    int counter = 0;
    while(a >= b)
    {
        a = a - b;
        counter++;
        //printf("Counter is: %d\n", counter);
        //printf("A is: %d\n", a);
    }
    return (int)a;
}

int main()
{
    double m = 7;
    int e = 13;
    double n = 85;
    int d = 5;
    double c = remainder(pow(m, e), n);
    printf("Test: %.0f\n", (pow(m, e) - c)/85);
    m = remainder(pow(c, d), n);

    printf("Encrypt. C is: %.0f\n", c);
    printf("Decrypt. M is: %.0f\n", m);
    //double c = pow(m, e) % n;

    //printf("%.0f\n", c);
    return 0;
}
