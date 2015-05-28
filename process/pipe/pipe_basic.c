/*************************************************************************
    > File Name: pipe.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Mon 25 May 2015 08:56:40 PM CST
	> pipe create and test, father send data to pipe[1] and wait for child to exit
	  child receive data from pipe[0], and then exit.
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

#define MAX_DATA_LEN 256
#define DELAY_TIME 1

int main()
{
	pid_t pid;
	int pipe_fd[2];
	char buffer[MAX_DATA_LEN];
	const char data[] = "Pipe test program";
	int real_read;
	int real_write;

	memset(&buffer, 0, sizeof(buffer));

	if (pipe(pipe_fd) < 0)
	{
		perror("fail to pipe");
		exit(-1);
	}
	/*
	 *子进程关闭写，fd[1], 睡眠，然后从读fd[0]中读取数据
	 */
	if ((pid = fork()) == 0)//child
	{
		close(pipe_fd[1]);
		sleep(DELAY_TIME);

		if ((real_read = read(pipe_fd[0], buffer, MAX_DATA_LEN)) > 0)
		{
			printf("%d bytes read from the pipe is '%s'\n", real_read, buffer);
		}

		close(pipe_fd[0]);
		exit(0);
	}
	/*
	 *父进程关闭读fd[0],向fd[1]写数据，然后等待子进程结束回收
	 */
	else if(pid > 0)//father
	{
		close(pipe_fd[0]);
		if ((real_write = write(pipe_fd[1], data, strlen(data))) != -1)
		{
			printf("parent wrote %d bytes :'%s'\n", real_write, data);
		}

		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		exit(0);
	}

	return 0;
}
