/*************************************************************************
  > File Name: fifo_read.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Mon 25 May 2015 09:31:37 PM CST
  > read from MYFIFO, write to MYFILE
  > run first, create myfifo 
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>


#define MYFIFO "/home/qiu/myfifo"
#define MYFILE "/home/qiu/out"
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
	char buf[BUFFER_SIZE];
	int fd_fifo;
	int fd;
	int nread;
	int nwrite;

	if (access(MYFIFO, F_OK) == -1)//如果管道文件不存在
	{
		if (mkfifo(MYFIFO, 0666) < 0)
		{
			perror("fail to mkfifo");
			exit(-1);
		}
	}

	if ((fd_fifo = open(MYFIFO, O_RDONLY)) < 0)
	{
		perror("fail to open fifo");
		exit(-1);
	}

	if ((fd = open(MYFILE, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
	{
		perror("fail to open output file");
		close(fd_fifo);
		exit(-1);
	}

	while (1)
	{
		if ((nread = read(fd_fifo, buf, BUFFER_SIZE)) > 0)
		{
			if ((nwrite = write(fd, buf, nread)) < 0)
			{
				perror("fail to write");
				close(fd_fifo);
				close(fd);
				exit(-1);
			}
		}
		else
		{
			break;
		}
	}

	close(fd_fifo);
	close(fd);

	return 0;
}
