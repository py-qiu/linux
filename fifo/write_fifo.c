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

	if ((fd = open(argv[1], O_WRONLY)) < 0)
	{
		fprintf(stderr, "open fifo %s for writing failed:%s\n", argv[1], strerror(errno));
		exit(-1);
	}

	fprintf(stdout, "open fifo %s for writing successed.\n", argv[1]);

	char buff[BUFFER_SIZE];
	ssize_t n;

	while (fgets(buff, BUFFER_SIZE, stdin))
	{
		if ((n = write(fd, buff, strlen(buff))) < 0)
		{
			fprintf (stderr, "write failed on %s : %s\n", argv[1], strerror(errno));
			break;
		}
	}

	return 0;
}

