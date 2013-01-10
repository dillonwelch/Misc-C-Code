#include <stdio.h>
#include <stdlib.h>

#define INF 1000000;        // Infinity

int numOfSystems = 0;	// Number of star systems
int numOfWormholes = 0;  // Number of wormholes

// Structure for individual wormholes
typedef struct
{
	int u;  // start point
	int v;  // end point
	int w; // weight
} Wormhole;

void test()
{
	int i = 0;
	printf("1\n3000 3000\n");
	for(; i < 3000; i++)
	{
		if(i % 10 != 0) { printf("%d %d 1\n", i, i + 1); }
		else { printf("%d %d -1000 \n", i, i + 1);	}
	}
}

int main()
{
	int numOfCases = 0;

	scanf("%d", &numOfCases); // Get the amount of cases to test
	while(numOfCases > 0)
	{
		scanf("%d", &numOfSystems); 	// Get the amount of star systems	
		scanf("%d", &numOfWormholes); // Get the amount of wormholes

		/*Wormhole wormholes[numOfWormholes * numOfWormholes];*/
		Wormhole *wormholes = (Wormhole*) malloc(sizeof(Wormhole) * numOfWormholes); // Array of wormholes
		
		int i = 0; // Counter variables for loops
		int j = 0;
		
		int holder = 0; // Counter for going through and getting each wormhole
		while (holder < numOfWormholes) // Go through and get the start point, end point, and weight for each wormhole.
		{
			int x = 0;
			int y = 0;
			int t = 0;
			scanf("%d", &x);
			scanf("%d", &y);
			scanf("%d", &t);
			Wormhole wormy;		// My pet wormy!
			wormy.u = x;
			wormy.v = y;
			wormy.w = t;
			wormholes[holder] = wormy;
			//wormholes[holder].v = y;
			//wormholes[holder].w = t;
			holder++;
		}
		
		/* int d[numOfSystems]; */
		int *d = (int*) malloc(sizeof(int) * numOfSystems); // D[x] distance array for each star system
		int possible = 0;	// Whether or not it is possible to go back in time
		
		for(i = 0; i < numOfWormholes; ++i) // Set the distances for each node to infinity
		{
			d[i] = INF;
		}
		
		d[0] = 0;	// D[v] = 0

		for(i = 0; i < numOfSystems; ++i)	// N iterations of relaxation algorithm
		{
			for(j = 0; j < holder; ++j)
			{
				if(d[wormholes[j].u] + wormholes[j].w < d[wormholes[j].v])
				{
					d[wormholes[j].v] = d[wormholes[j].u] + wormholes[j].w;
					if(i == numOfSystems - 1)
					{
						possible = 1;	// If the Nth iteration finds a relaxation, this means there is a negative cycle
					}
				}
			}
		}

		if(possible == 1)
		{
			printf("possible\n");
		}
		else
		{
			printf("not possible\n");
		}
		printf("wormholes: %d d: %d\n", (int) sizeof(Wormhole) * numOfWormholes, (int) sizeof(int) * numOfSystems);  // Test to see the size of the wormhole array
		free(wormholes);
		free(d);
		numOfCases--;
		/* test(); */
	}
	return 0;
}
		