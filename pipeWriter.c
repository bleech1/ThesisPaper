/*
 * pipeWriter.c
 */

// C program to open and write to a FIFO

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

// path to pipe
#define PIPE_PATH "./my_pipe"
#define MAX_BYTES 100

int main() 
{ 
	char buf[MAX_BYTES]; 
	// Open FIFO as writer
	int fd = open(PIPE_PATH, O_WRONLY | O_CREAT); 
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	while (1) 
	{ 
		// get input from user
		char *result = fgets(buf, MAX_BYTES, stdin); 
		if (result == NULL)
		{
			perror("fgets");
			exit(1);
		}

		// write input into the pipe
		int writeRes = write(fd, buf, strlen(buf)+1); 
		if (writeRes < 0)
		{
			perror("write");
			exit(1);
		}
	} 
	fd = close(fd); 
	if (fd < 0)
	{
		perror("close");
		exit(1);
	}
	return 0; 
} 

