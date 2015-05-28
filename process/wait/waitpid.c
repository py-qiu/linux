/*
 * (C) Copyright 2014
 * http://www.farsight.com.cn/
 * http://nj.hqyj.com/
 * 
 * This program is distributed in the purpose for training only
 * and hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Revision history
 * ------------------------------------------------------
 * 20140928	unicornx	initial archived
 */
/*
 * demo how to use waitpid() to wait the exit of child process
 * w/o blocking.
 * note we use "while" not "for" to wait because we can not
 * accuately expect when the child will exit though here in
 * this sample we know child will sleep 5 sec, considering
 * a extreme condition the child process may be blocked by the
 * kernel for quite a long time due to some unexpected reasons.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid;

	printf("parent[pid=%d] is born\n", getpid());
		 
	if (-1 == (pid = fork())) {
		perror("fork error");
		return 1;
	}
	
	if (pid == 0){
		printf("child[pid=%d] is born\n", getpid());
		sleep(10);
		printf("child is over\n");
	}
	else{ //parent
		pid_t pid_w;
		while((pid_w = waitpid(pid, NULL, WNOHANG)) == 0) {
			printf("child is still living, parent wait w/o HAND and returns with 0\n");
			sleep(1);
		}
		printf("waitpid returns with pid = %d.\n", pid_w);
		
		printf("father is over\n");
	}
	
	return 0;
}
