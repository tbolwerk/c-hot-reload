#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* concat(char* aa, char* bb)
{
	char *a = aa;
	char *b = bb;

	while(*a)
	{
		++ a;
	}

	while(*b)
	{
		*a = *b;
		++ b;
		++ a;
	}
	*a = '\0';
	return aa;	
}

int main()
{
	char *lname = malloc(sizeof(char) * 100);
	char *fname = malloc(sizeof(char) * 100);
	fname = "Twan";
	lname = "Bolwerk";
	char* result = malloc(sizeof(char) * 200);
 	printf("My first name is %s", fname);
	return 0;
}
