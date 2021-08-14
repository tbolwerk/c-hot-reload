#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdbool.h"
#include "string.h"

#define VERBOSE false
#define BUFFER_SIZE 10000
#define PROGRAM_NAME main
int main(int argc, char **argv)
{
	if(argc != 2){
		fprintf(stderr, "No file_namegiven [string]");
		exit(EXIT_FAILURE);
	}
	char c, *file_name;
	FILE *fp;
	bool anyChange;
	char buffer[1000];

	file_name = argv[1];
	while(true)
	{
		fp = fopen(file_name, "r");
		
		if(fp == NULL)
		{
			fprintf(stderr, "Error while opening file");
			exit(EXIT_FAILURE);
		}
		anyChange = false;
		int i = 0;
		while((c = fgetc(fp)) != EOF){
			if(i > BUFFER_SIZE)
			{
				fprintf(stderr, "Error buffersize overflow");
				exit(EXIT_FAILURE);
			}	
			if(VERBOSE)
			{
				fprintf(stdout, "%c", c);
			}
			if((buffer[i] == c) == 0)
			{
				buffer[i] = c;
				if(anyChange == false){
					anyChange = true;
				}
			}
			i ++;
		}
		if(anyChange == true)
		{
			if(VERBOSE)
			{
				fprintf(stdout, "Filename: %s\n", file_name);
				fprintf(stdout, "Change detected\n");
			}
			int pid = fork();
			if(pid == 0)
			{
				char *compile_args[] = {"cc", file_name, "-o","PROGRAM_NAME",NULL};
				execvp(compile_args[0],compile_args);
				exit(EXIT_SUCCESS);
			}
			wait(&pid);
			pid = fork();
			if(pid == 0)
			{
				char *executable = "./PROGRAM_NAME";
				char *args[] = { executable ,NULL};
				execv(args[0], args);
				exit(EXIT_SUCCESS);
			}
			wait(&pid);
			fprintf(stdout, "\n");
		}
		
		fclose(fp);
		sleep(1);
	}
	return 0;
}
