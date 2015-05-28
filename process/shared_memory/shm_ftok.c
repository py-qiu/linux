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
 * by ftok() and shmget().
 *
 * No matter who call shmget() first, there's only ONE IPC 
 * object instance only if the callers provide same key.
 * The first caller will create the instance due to kernel
 * would check and find the key has nothing associated with
 * existing IPC object, while for the second caller, the 
 * system call just return the id associated with the same 
 * IPC object which has been created before.
 *
 * demo method: run this program several times, only one IPC
 * shm object would be created.
 * Note, if we have launched multiple program instances,
 * after termination the first one, the IPC object would be
 * removed due to the nattach is zero. That's why you may see 
 * "shmctl error: Invalid argument" for left processes when
 * they are terminated.
 */
#include <sys/types.h>
#include <sys/ipc.h>	/* ftok */
#include <unistd.h>	/* fork */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
#include <sys/shm.h>	/* shmget, shmctl */


#define PATH_NAME	"."
#define PROJ_ID		100

#define BUFSZ		2048

int main(int argc, char *argv[])
{
	key_t	key;
	int	shmid;

	if ((key = ftok(PATH_NAME, PROJ_ID)) < 0) {
		perror("ftok error");
		exit(1);
	}
	printf("process(pid=%d) created key = %#x\n", 
		getpid(), key);
		
	if((shmid = shmget(key, BUFSZ, IPC_CREAT | 0666)) < 0){
		perror("shmget");
		exit(-1);
	}
	printf("process(pid=%d) created shared-memory id=%d\n",
		getpid(), shmid);
		
	printf("ready to terminate?");
	getchar();
	
	if (-1 == shmctl(shmid, IPC_RMID, NULL)) {
		perror("shmctl error");
	}

	exit(0);
}
