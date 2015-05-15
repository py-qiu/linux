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
#include <stdio.h>
#include <stdlib.h>

#include "sequeue.h"

sequeue_t *CreateEmptySequeue()
{
	sequeue_t *queue;

	queue = (sequeue_t *)malloc(sizeof(sequeue_t));

	if (NULL == queue) return NULL;
	
	/* initially use the first array element as cycle-head */
	queue->front = queue->rear = 0;

	return queue;
}

void DestroySequeue(sequeue_t *queue)
{
	if (queue) {
		free(queue);
	}
}

int EmptySequeue(sequeue_t *queue)
{
	if (!queue) return -1;
	return (queue->front == queue->rear ? 1 : 0);
}

int FullSequeue(sequeue_t *queue)
{
	if (!queue) return -1;

	return ((queue->rear + 1) % N == queue->front ? 1 : 0);
}

void ClearSequeue(sequeue_t *queue)
{
	if (!queue) return;
	
	queue->front = queue->rear = 0;

	return;
}

int EnQueue(sequeue_t *queue, data_t x)
{
	if (!queue) return - 1;

	if (1 == FullSequeue(queue)) return -1; /* full */

	queue->rear = (queue->rear + 1) % N;
	queue->data[queue->rear] = x;

	return 0;
}

int DeQueue(sequeue_t *queue, data_t *x)
{
	if (!queue) return -1;

	if (1 == EmptySequeue(queue)) return -1; /* empty */

	queue->front = (queue->front + 1) % N;

	if (NULL != x) {
		*x = queue->data[queue->front];
	}

	return 0;
}
