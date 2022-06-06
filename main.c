#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdbool.h"
#include "string.h"
 #include <errno.h>

#define VERBOSE false
#define BUFFER_SIZE 1000000
int main(int argc, char **argv)
{
	if(argc < 2 || argc > 3){
		fprintf(stderr, "No file_name given [string]\n");
		exit(EXIT_FAILURE);
	}
	char c, *file_name, *command;
	FILE *fp;
	bool anyChange;
	char buffer[BUFFER_SIZE];

	file_name = argv[1];
	if(argv[2])
	{
		command = argv[2];
	}else{
		command = "cc";
	}

	while(true)
	{
		fp = fopen(file_name, "r");
		
		if(fp == NULL)
		{
			fprintf(stderr, "Error while opening file");
			// exit(EXIT_FAILURE);
			continue;
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
				remove("exec-hot-reload");
			}
			wait(&pid);
			pid = fork();
			if(pid == 0)
			{
				char *compile_args[] = {command, file_name, "-o","exec-hot-reload",NULL};
				execvp(compile_args[0],compile_args);
				exit(EXIT_SUCCESS);
			}
			wait(&pid);
			pid = fork();
			if(pid == 0)
			{
				char *executable = "exec-hot-reload";
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
	
	free(file_name);
	return 0;
}
