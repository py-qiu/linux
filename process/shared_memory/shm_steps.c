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
 * A complete sample shows steps from creation of a shm to deletion
 * of the shm.
 */
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#define BUFSZ 2048

int main(int argc, char *argv[])
{
	int shmid;
	char *shmaddr;

	if((shmid = shmget(IPC_PRIVATE, BUFSZ, 0666)) < 0){
		perror("shmget");
		exit(-1);
	}
	printf("### created shared-memory: %d\n", shmid);
	system("ipcs -m | grep 666");
	
	if((shmaddr = (char *)shmat(shmid, NULL, 0)) < (char *)0){
		perror("shmat");
		exit(-1);
	}	
	printf("### attached shared-memory\n");
	system("ipcs -m | grep 666");
	
	if ((shmdt(shmaddr)) < 0){
		perror("shmdt");
		exit(-1);
	}
	printf("### detached shared-memory\n");
	system("ipcs -m | grep 666");

	shmctl(shmid, IPC_RMID, NULL);
	printf("### removed shared-memory\n");
	system("ipcs -m | grep 666");

	return 0;
}
