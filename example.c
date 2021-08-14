#include "stdio.h"
#include "stdlib.h"
int main()
{
	char *pname = (char*) malloc(sizeof(char) * 100);
	pname = "Twan Bolwerk";
	printf("Helllo, %s", pname);
}
