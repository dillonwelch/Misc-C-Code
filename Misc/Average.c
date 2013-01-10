#include <stdio.h>

int main()
{
	int i = 1;
	int j = 1;
	double sum = 0;
	for(; i <= 6; i++)
	{
		j = i;
		for(; j <= 6; j++)
		{
			sum += i + j;
		}
	}
	sum = sum /  21;
	printf("%f\n", sum);	
    
    return 0;
}