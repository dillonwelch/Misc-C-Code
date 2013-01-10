#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int seed = (int) time(NULL);
	srand(seed);
	int i = 0;
	int j = 0;
	int sum = 0;
	int amount = atoi(argv[1]);
	for(j = 0; j < amount; j++)
	{
		sum = 0;
		for(i = 0; i < amount; i++)
		{
			sum += (rand() % 100);
		}
		printf("Mean %d: %d\n", j + 1, sum / amount);
	}

	return 0;
}