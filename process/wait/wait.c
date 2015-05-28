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
 * demo how to use wait() to erase zombies.
 * demo how to use macros WIFEXITED/WEXITSTATUS to get
 * exit status of the child process.
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
		return -1;
	}
	
	if (pid == 0){
		printf("child[pid=%d] is born\n", getpid());
		sleep(10);
		printf("child is over\n");
		
		exit(123); //return 123; 
	}
	else{
		pid_t pid_w;
		int status;
				
		pid_w = wait(&status);
		if (pid_w < 0) {
			perror("wait error");
			return 1;
		}
		
		if (WIFEXITED(status)) { 
			status = WEXITSTATUS(status);
			printf("wait returns with pid = %d. return status is %d\n", pid_w, status);
		} else {
			printf("wait returns with pid = %d. the child is terminated abnormally\n", pid_w);
		}
		
		printf("father is over\n");
		
		return 0;
	}
}
