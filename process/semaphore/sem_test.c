/*************************************************************************
    > File Name: sem_test.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 26 May 2015 06:59:59 PM CST
	> semaphore和fork的联合测试，和另外的sem_op_lib.c文件联合使用
		新建信号量sem_id，初始化信号量值为0，创建子进程，父进程阻塞等待信号量可用，子进程v操作使信号量变为可用

	函数输出结果为：
		child process will wait for some seconds
		The returned value is %d in the child process(PID = %d)
		The returned value is %d in the father process(PID = %d)
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<unistd.h>

#define DELAY_TIME 3
/*
 *封装函数：信号量的初始化，删除，P操作，V操作
 */
extern int init_sem(int sem_id, int init_value);
extern int del_sem(int sem_id);
extern int sem_p(int sem_id);
extern int sem_v(int sem_id);

int main()
{
	pid_t result;
	int sem_id;

	sem_id = semget(ftok(".", 100), 1, 0666|IPC_CREAT);
	init_sem(sem_id, 0);

	result  = fork();

	if (result == -1)
	{
		printf("fail to fork");
		exit(-1);
	}
	else if(result == 0)
	{
		printf("child process will wait for some seconds\n");
		sleep(DELAY_TIME);
		printf("The returned value is %d in the child process(PID = %d)\n", result, getpid());
		sem_v(sem_id);
	}
	else
	{
		sem_p(sem_id);
		printf("The returned value is %d in the father process(PID = %d)\n", result, getpid());
		sem_v(sem_id);
		del_sem(sem_id);
	}

	return 0;
}
