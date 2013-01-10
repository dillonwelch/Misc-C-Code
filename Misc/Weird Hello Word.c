#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* p = new char[12];
	*p = 0x48;
	++p;
	*p = 0x65;
	++p;
	*p = 0x6c;
	++p;
	*p = 0x6c;
	++p;
	*p = 0x6f;
	++p;
	*p = 0x20;
	++p;
	*p = 0x57;
	++p;
	*p = 0x6f;
	++p;
	*p = 0x72;
	++p;
	*p = 0x6c;
	++p;
	*p = 0x64;
	++p;
	*p = 0x0;
	--p;
	--p;
	--p;
	--p;
	--p;
	--p;
	--p;
	--p;
	--p;
	--p;
	--p;
	printf(p);
	delete p;


a:
	goto a;
	return 0;
}