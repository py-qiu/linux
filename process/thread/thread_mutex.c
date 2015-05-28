/*************************************************************************
    > File Name: thread_mutex.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Sun 24 May 2015 08:30:18 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define THREAD_NUM 3
#define REPEAT_NUM 3
#define DELAY_TIME_LEVELS 6.0

pthread_mutex_t mutex;

void *thrd_func(void *arg)
{
	int thrd_num = (int) arg;
	int delay_time = 0;
	int count = 0;
	int res;
	
	res = pthread_mutex_lock(&mutex);

	if (res)
	{
		printf ("Thread %d lock failed\n", thrd_num);
		pthread_exit(NULL);
	}

	printf("Thread %d is starting\n", thrd_num);

	for (count=0; count<REPEAT_NUM; count++)
	{
		delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX)/2) + 1;
		sleep (delay_time);
		printf ("\tThread %d : job %d delay = %d\n", thrd_num, count, delay_time);
	}

	printf("Thread %d finished\n", thrd_num);

	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

int main()
{
	pthread_t thread[THREAD_NUM];

	int no = 0;
	int res;
	void *thrd_ret;

	srand(time(NULL));

	pthread_mutex_init(&mutex, NULL);

	for (no=0; no < THREAD_NUM; no++)
	{
		res = pthread_create(&thread[no], NULL, thrd_func, (void *)no);
		if (res != 0)
		{
			printf("create thread %d failed\n", no);
			exit(res);
		}
	}

	printf("create threads success\nwaiting for threads to finish\n");

	for (no=0; no<THREAD_NUM; no++)
	{
		printf("waiting to join thread %d\n", no);
		res = pthread_join(thread[no], &thrd_ret);

		if (!res)
		{
			printf("thread %d joined\n", no);
		}
		else
		{
			printf("thread %d join faile\n", no);
		}
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}

