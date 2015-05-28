/*************************************************************************
    > File Name: shmem_basic_father_child.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 26 May 2015 07:18:21 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>

#define BUFFER_SIZE 2048

int main()
{
	pid_t pid;
	int shmid;
	char *shm_addr;
	char flag[] = "WROTE";
	char buff[BUFFER_SIZE];
	
	/*
	 *create shared_memory, IPC_PRIVATE
	 */
	if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666)) < 0)
	{
		perror("fail to shmget");
		exit(-1);
	}
	else
	{
		printf("create shared-memory :%d\n", shmid);
	}

	system("ipcs -m");


	/*
	 *create child process
	 */
	pid = fork();
	if (-1 == pid)
	{
		perror("fail to fork");
		exit(-1);
	}
	else if (0 == pid)//child
	{
		/*
		 *child process shmat 
		 */
		if ((shm_addr = shmat(shmid, 0, 0)) == (void *) -1)
		{
			perror("child : fail to shmat");
			exit(-1);
		}
		else
		{
			printf("child : attach memory %p\n", shm_addr);
		}

		system("ipcs -m");
		

		/*
		 *child process wait for data from shared_memory
		 */
		while (strncmp(shm_addr, flag, strlen(flag)))
		{
			printf("child : wait for enable data\n");
			sleep(5);
		}

		strcpy(buff, shm_addr+strlen(flag));
		printf("Child : shared memory %s\n", buff);

		/*
		 *child process shmdt
		 */
		if (shmdt(shm_addr) < 0)
		{
			perror("fail to shmdt");
			exit(-1);
		}
		else
		{
			printf("child : deattach shared memory\n");
		}

		system("ipcs -m");

		
		/*
		 *child process IPC_RMID
		 */
		if (shmctl(shmid, IPC_RMID, NULL) < 0)
		{
			perror("fail to  IPC_RMID");
			exit(-1);
		}
		else
		{
			printf("delete shared memory\n");
		}

		system ("ipcs -m");
	}
	else//father process
	{
		/*
		 *father process shmat
		 */
		if ((shm_addr = shmat(shmid, 0, 0)) == (void *)-1)
		{
			perror("parent : fail to shmat");
			exit(-1);
		}
		else
		{
			printf("parent :attach memory : %p\n", shm_addr);
		}

		sleep(1);

		/*
		 *father process write data to shared_memory
		 */
		printf("\nInput some string:\n");
		fgets(buff, BUFFER_SIZE, stdin);
		strncpy(shm_addr+strlen(flag), buff, strlen(buff));
		strncpy(shm_addr, flag, strlen(flag));

		/*
		 *father process shmdt
		 */
		if ((shmdt(shm_addr)) < 0)
		{
			perror("parent : fail to shmdt");
			exit(-1);
		}
		else
		{
			printf("parent : deattach shared memory\n");
		}

		/*
		 *father process waitpid child process
		 */
		system("ipcs -m");
		waitpid(pid, NULL, 0);
		printf("finished\n");
	}

	return 0;
}
