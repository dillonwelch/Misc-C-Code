#include <stdio.h>
#include <stdlib.h>

#define INF 1000000;
#define numOfWorms 32

int numOfSystems = 0;
int numOfWormholes = 0;

typedef struct
{
	int u;
	int v;
	int w;
} Wormhole;

int main()
{
	int numOfCases = 0;

	scanf("%d", &numOfCases);
	while(numOfCases > 0)
	{
		scanf("%d", &numOfSystems); 						
		scanf("%d", &numOfWormholes); 					


		Wormhole wormholes[100000];
		
		int i = 0;
		int j = 0;

		int holder = 0;
		while (holder < numOfWormholes)
		{
			int x = 0;
			int y = 0;
			int t = 0;
			scanf("%d", &x);
			scanf("%d", &y);
			scanf("%d", &t);

			wormholes[holder].u = x;
			wormholes[holder].v = y;
			wormholes[holder].w = t;
			holder++;
		}
		
		int d[numOfSystems];
		int possible = 0;	

		for(i = 0; i < numOfWormholes; ++i)
		{
			d[i] = INF;
		}

		d[0] = 0;

		for(i = 0; i < numOfSystems; ++i)
		{
			for(j = 0; j < holder; ++j)
			{
				if(d[wormholes[j].u] + wormholes[j].w < d[wormholes[j].v])
				{
					d[wormholes[j].v] = d[wormholes[j].u] + wormholes[j].w;
					if(i == numOfSystems - 1)
						possible = 1;
						
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

		numOfCases--;
	}
	return 0;
}
		