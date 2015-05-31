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
#include<sys/stat.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stdout, "Usage :%s <filename>\n", argv[0]);
		exit(-1);
	}

	if (mkfifo(argv[1], 0644) < 0)
	{
		fprintf(stderr, "mkfifo() failed :%s : %s\n", argv[1], strerror(errno));
		exit(-1);
	}

	return 0;
}
