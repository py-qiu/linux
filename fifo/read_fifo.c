/*************************************************************************
    > File Name: read_fifo.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Wed 20 May 2015 02:28:22 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
	int fd;

	if (argc < 2)
	{
		fprintf(stdout, "Usage: %s <filename>\n", argv[0]);
		exit(-1);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		fprintf(stderr, "open fifo %s for reading failed:%s\n", argv[1], strerror(errno));
		exit(-1);
	}

	fprintf(stdout, "open fifo %s for reading successed.\n", argv[1]);

	char buff[BUFFER_SIZE];
	ssize_t n;

	while(1)
	{
		if ((n = read(fd, buff, BUFFER_SIZE)) < 0)
		{
			fprintf (stderr, "read failed on %s : %s\n", argv[1], strerror(errno));
			exit(-1);
		}
		else if(n ==0)
		{
			fprintf(stderr, "peer closed fifo\n");
			break;
		}
		else
		{
			fprintf(stdout, "read %d bytes from fifo %s\n", n, buff);
		}
	}

	return 0;
}

