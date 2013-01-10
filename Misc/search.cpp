#include <stdio.h>
#include <stdlib.h> // malloc()
#include <ctype.h>  // isdigit() and isalpha()
#include <string.h> // strlen()

int search(char *search, char *packet)
{
	int searchCounter = 0;
	int packetCounter = 0;
	size_t packetSize = strlen(packet);
	size_t searchSize = strlen(search);
	for(; packetCounter <= packetSize; packetCounter++)
	{
	    //printf("Search is: %d\n", search[searchCounter]);
		if(search[searchCounter] == 116)
			return 1;

		if(search[searchCounter] != packet[packetCounter])
		{
            printf("(fail)Search is: %c and packet is: %c\n",search[searchCounter], packet[packetCounter]);
			searchCounter = 0;
		}
		else
		{
		    //printf("Search is: %c and packet is: %c\n",search[searchCounter], packet[packetCounter]);
		    searchCounter++;
		}

	}
	//printf("%s", "Fail!\n");
	return 0;

}

int main()
{
    char *a = (char*)malloc(sizeof(char) * 9);
    char *b = (char*)malloc(sizeof(char) * 5);
    memset(a, '\0', 9);
    memset(b, '\0', 5);
    strcpy(a, "Rawrtest");
    //*(a + 8) = '\0';
    //*(b + 4) = '\0';
    strcpy(b, "Rawr");

    printf("%s\n%s\n", a, b);

    if(search(a, b))
    {
        printf("This line has the search term: %s", a);
    }
}
