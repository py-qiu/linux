/*
 *test size of buffer, 65536
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

int main(void)
{
	int	fd[2];
	int	count = 0;
	
	if (pipe(fd) < 0) {
		perror("pipe error\n");
		goto _exit_error;
	}
	/* 
	 * Till now, we create a pipe in kernel
	 * fd[0] is for read; fd[1] is for write
	 * fd[0] and f[1] are both hold by parent process
	 */
	 
	while (1) 
	{
		if(-1 == write(fd[1], "a", 1)) 
		{
			perror("write error");
			break;
		}
		printf("count = %d.\n", ++count);
	}
	
	return 0;
	
_exit_error:
	return 1;
}
