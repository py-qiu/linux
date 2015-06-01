/*************************************************************************
  > File Name: fifo_write.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Mon 25 May 2015 09:24:49 PM CST
  > read from MYFILE, write to MYFIFO
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#define MYFIFO "/home/qiu/myfifo"
#define MYFILE "/home/qiu/in"
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
	int fd_fifo;
	int fd;
	int nwrite;
	int nread;
	char buf[BUFFER_SIZE];

/*	if (argc < 2)
	{
		printf("Usage:./fifo_write <filename>\n ");
		exit(-1);
	}

*/	if ((fd_fifo = open(MYFIFO, O_WRONLY)) < 0)
	{
		perror("fail to open fifo");
		exit(-1);
	}

	if ((fd = open(MYFILE, O_RDONLY)) < 0)
	{
		perror("fail to open file");
		close(fd_fifo);
		exit(-1);
	}

	while ((nread = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if ((nwrite = write(fd_fifo, buf, nread)) < 0)
		{
			perror("fail to write");
			close(fd_fifo);
			close(fd);
			exit(-1);
		}
	}

	close(fd_fifo);
	close(fd);

	return 0;
}
