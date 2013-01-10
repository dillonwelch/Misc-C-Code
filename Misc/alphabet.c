#include <stdio.h>
#include <math.h>

int main()
{
    int num = 0;
    int tens = 0;
    char letter = 'a';
    for(; num <= 26; num++)
    {
        if(num < 10) { printf("%d", tens); }
        printf("%d ", num);
    }
    printf("\n    ");
    for(; letter <= 'z'; letter++)
    {
        printf("%c  ", letter);
    }
    return 0;
}
