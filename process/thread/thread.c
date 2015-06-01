/*************************************************************************
    > File Name: thread.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Mon 25 May 2015 08:57:48 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define THREAD_NUM 3
#define REPEAT_NUM 5
#define DELAY_TIME_LEVELS 6.0

void *thrd_func(void *arg)
{
	int thrd_num = (int)arg;
	int delay_time = 0;
	int count = 0;

	printf("Thread %d is starting\n", thrd_num);

	for (count=0; count<REPEAT_NUM; count++)
	{
		delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX)) + 1;
		sleep(delay_time);
		printf ("\t Thread %d : job %d delay = %d\n", thrd_num, count, delay_time);
	}

	printf ("Thread %d finished\n", thrd_num);

	pthread_exit(NULL);
}


int main()
{
	pthread_t thread[THREAD_NUM];

	int no = 0;
	int res = 0;

	void *thrd_ret;

	srand(time(NULL));

	for (no=0; no<THREAD_NUM; no++)
	{
		res = pthread_create(&thread[no], NULL, thrd_func, (void *)no);
		if (res != 0)
		{
			printf ("create thread %d failed\n", no);
			exit(res);
		}
	}

	printf("create threads success\nWaiting for threads to finish\n");

	for (no=0; no<THREAD_NUM; no++)
	{
		printf("waiting to join thread %d\n", no);
		res = pthread_join(thread[no], &thrd_ret);

		if (!res)
		{
			printf("Thread %d joined\n", no);
		}
		else
		{
			printf ("Thread %d join failed\n", no);
		}
	}

	return 0;
}
