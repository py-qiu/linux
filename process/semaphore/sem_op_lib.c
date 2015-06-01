/*************************************************************************
    > File Name: sem_com.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 26 May 2015 06:40:46 PM CST;
	> 对semaphore 的初始化，删除，P操作，V操作进行封装
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define DELAY_TIME 3

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

int init_sem(int sem_id, int init_value)
{
	union semun sem_union;
	sem_union.val = init_value;
	if (semctl(sem_id, 0, SETVAL, sem_union) < 0)
	{
		perror("fail to init sem");
		exit(-1);
	}

	return 0;
}

int del_sem(int sem_id)
{
	union semun sem_union;
	if (semctl(sem_id, 0, IPC_RMID, sem_union) < 0)
	{
		perror("fail to delete sem");
		exit(-1);
	}

	return 0;
}


int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_b, 1) < 0)
	{
		perror("fail to p sem");
		exit(-1);
	}

	return 0;
}

int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_b, 1) < 0)
	{
		perror("fail to V sem");
		exit(-1);
	}

	return 0;
}
