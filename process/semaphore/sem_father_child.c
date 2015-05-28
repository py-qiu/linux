/*************************************************************************
  > File Name: 5.6.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Thu 21 May 2015 03:51:35 PM CST
  > semaphore basic operation, cooperated with shared memory
  > 读信号量初始化为0，写信号量初始化为1
  > 父进程P操作写信号量，V操作读信号量
  > 子进程P操作读信号量（阻塞等待），V操作写信号量
  > 父进程/子进程交替PV读写信号量，父进程写，然后子进程读
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<errno.h>

#define WRITE 1
#define READ 0

union semun 
{
	int		val;	/* Value for SETVAL */
	struct semid_ds *buf;	/* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;	/* Array for GETALL, SETALL */
	struct seminfo  *__buf;	/* Buffer for IPC_INFO (Linux-specific) */
};

pid_t pid;

int main()
{
	/*
	 *create key
	 */
	key_t key;
	if ((key = ftok("./", 100)) < 0)
	{
		perror("fail to ftok");
		exit(-1);
	}

	/*
	 *create shmid
	 */
	int shmid;
	if ((shmid = shmget(key, 1024, IPC_CREAT|0666)) < 0)
	{
		perror("fail to shmget");
		exit(-1);
	}

	/*
	 *shmat
	 */
	char *shmaddr;
	shmaddr = (char *)shmat(shmid, NULL, 0);

	/*
	 *semget, create 2 sem
	 */
	int semid;
	if ((semid = semget(key, 2, IPC_CREAT|0666)) < 0)
	{
		perror("fail to semget");
		exit(-1);
	}

	/*
	 *semctl, 初始化信号量数量
	 */
	union semun semarg;
	struct sembuf mysembuf;

	semarg.val = 0;/*read semaphore initialized value 0*/
	semctl(semid, READ, SETVAL, semarg);

	semarg.val = 1;/*write semaphore initialized vakue 1*/
	semctl(semid, WRITE, SETVAL, semarg);

	/*
	 *fork
	 */

	if ((pid = fork()) < 0)
	{
		perror("fail to fork");
		exit(-1);
	}
	else if (pid == 0) //child, read, wait for sem
	{
		while (1)
		{
			mysembuf.sem_num = 0;/*第1个信号量, 0序*/
			mysembuf.sem_op = -1;/*读信号量减1，否则阻塞*/
			mysembuf.sem_flg = 0;/*flag默认值为0*/

			semop(semid, &mysembuf, 1);/*child process read from buff*/
			printf("read from buf:\n%s", shmaddr);

			mysembuf.sem_num = 1;/*第2个信号量，0序*/
			mysembuf.sem_op = 1;/*写信号量加1*/
			mysembuf.sem_flg = 0;

			semop(semid, &mysembuf, 1);
		}
	}
	else//father
	{
		while(1)
		{
			mysembuf.sem_num = 1;
			mysembuf.sem_op = -1; /*写信号量减1，否则阻塞*/
			mysembuf.sem_flg = 0;

			semop(semid, &mysembuf, 1);
			printf("write ro shared memory:\n");
			fgets(shmaddr, 64, stdin);

			mysembuf.sem_num = 0;
			mysembuf.sem_op = 1;/*读信号量加1*/
			mysembuf.sem_flg = 0;

			semop(semid, &mysembuf, 1);

			//sleep(1);
		}
	}

	return 0;
}
