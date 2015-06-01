/*************************************************************************
    > File Name: procuder-customer.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Sun 24 May 2015 07:44:00 PM CST
	> 同步练习，创建两个线程，分别扮演生产者和消费者的角色，用信号量控制两个线程之间的同步
	> 创建管道，生产者向管道中写入数据，P信号量avail，V信号量full
	> 消费者从管道中读出数据，P信号量full，V信号量avail
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<errno.h>
#include<semaphore.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUFFER_SIZE 3
#define UNIT_SIZE 5
#define RUN_TIME 30
#define DELAY_TIME_LEVELS 5.0
#define MYFIFO "myfifo"


int fd;
time_t end_time;
sem_t mutex, full, avail;


void *producer(void *arg)
{
	int real_write;
	int delay_time = 0;

	while (time(NULL) < end_time)
	{
		delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX) / 2.0) + 1;
		sleep (delay_time);

		sem_wait(&avail);
		sem_wait(&mutex);

		printf ("\nProcuder : delay = %d\n", delay_time);

		if ((real_write = write (fd, "hello", UNIT_SIZE)) == -1)
		{
			if (errno == EAGAIN)
			{
				printf ("The FIFO has not been read yet.Please try later\n");
			}
		}
		else
		{
			printf ("Write %d to the FIFO\n", real_write);
		}

		sem_post(&full);
		sem_post(&mutex);
	}

	pthread_exit(NULL);
}



void *customer(void *arg)
{
	unsigned char read_buffer[UNIT_SIZE];
	int real_read;
	int delay_time;

	while (time(NULL) < end_time)
	{
		delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX)) + 1;
		sleep (delay_time);

		sem_wait(&full);
		sem_wait(&mutex);

		memset(read_buffer, 0, UNIT_SIZE);

		printf ("\nCustomer : delay = %d\n", delay_time);

		if ((real_read = read (fd, read_buffer, UNIT_SIZE)) == -1)
		{
			if (errno == EAGAIN)
			{
				printf("No data\n");
			}
		}

		printf("Read %s from FIFO\n", read_buffer);
		
		sem_post(&avail);
		sem_post(&mutex);
	}

	pthread_exit(NULL);
}



int main()
{
	pthread_t thrd_prd_id, thrd_cst_id;

	pthread_t mon_th_id;

	int ret;

	srand(time(NULL));

	end_time = time(NULL) + RUN_TIME;

	if ((mkfifo(MYFIFO, O_CREAT|O_EXCL|0666) < 0) && (errno != EEXIST))
	{
		printf("cannot create fifo\n");
		return errno;
	}

	fd = open(MYFIFO, O_RDWR);
	if (fd == -1)
	{
		printf ("open fifo error\n");
		return fd;
	}

	ret = sem_init(&mutex, 0, 1);
	ret += sem_init(&avail, 0, BUFFER_SIZE);
	ret += sem_init(&full, 0, 0);

	if (ret != 0)
	{
		printf("any semaphore initialization failed\n");
		return ret;
	}

	ret = pthread_create(&thrd_prd_id, NULL, producer, NULL);

	if (ret != 0)
	{
		printf("create procuder thread error\n");
		return ret;
	}

	ret = pthread_create(&thrd_cst_id, NULL, customer, NULL);
	
	if (ret != 0)
	{
		printf("create customer thread error\n");
		return ret;
	}

	pthread_join(thrd_prd_id, NULL);
	pthread_join(thrd_cst_id, NULL);

	close(fd);
	unlink(MYFIFO);

	return 0;

}
