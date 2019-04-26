/*
 * pipeReader.c
 */

// C program to open and read from a FIFO

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
	int fd = open(PIPE_PATH, O_RDONLY | O_CREAT); 
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	while (1) 
	{ 
		int readRes = read(fd, buf, MAX_BYTES);
		if (readRes < 0)
		{
			perror("read");
			exit(1);
		}
		else if (readRes == 0)
		{
			continue;
		}
		printf("Received: %s\n", buf);
	} 
	fd = close(fd); 
	if (fd < 0)
	{
		perror("close");
		exit(1);
	}
	return 0; 
} 

