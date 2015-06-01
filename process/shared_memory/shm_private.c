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
 * This sample demos how to create SysV share memory object
 * by shmget() w/ IPC_PRIVATE.
 * IPC_PRIVATE isn't a flag field but a key_t type. 
 * If this special value is used for key, the system call 
 * ignores everything but the least significant 9 bits of 
 * shmflg and creates a new shared memory segment (on success).
 */ 
#include <sys/ipc.h>
#include <sys/shm.h>	/* shmget, shmctl */
#include <unistd.h>	/* fork */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */

#define BUFSZ		2048

int main()
{
	pid_t	pid;
	int	shmid;
	
	if((shmid = shmget(IPC_PRIVATE, BUFSZ, 0666)) < 0){
			perror("shmget");
			exit(-1);
	}
	printf("process(pid=%d) created shared-memory id=%d\n",
			getpid(), shmid);
	
	if ((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	}
	
	if (pid == 0) {
		printf("process(pid=%d) inherited shared-memory id=%d\n",
			getpid(), shmid);
					
	} else {
		sleep(1); /* just for display */
		printf("ready to show IPC share memory status?");
		getchar();

		printf("two processes get the same shared memory object\n");
		printf("------ Shared Memory Segments --------\n");
		printf("key        shmid      owner      "\
			"perms      bytes      nattch     status\n");
		system("ipcs -m | grep 666");
		
		printf("ready to terminate?");
		getchar();
		
		if (-1 == shmctl(shmid, IPC_RMID, NULL)) {
			perror("shmctl error");
		}
		
		printf("removed shared-memory\n");
		printf("------ Shared Memory Segments --------\n");
		printf("key        shmid      owner      "\
			"perms      bytes      nattch     status\n");
		system("ipcs -m | grep 666");

	}

	exit(0);
}

