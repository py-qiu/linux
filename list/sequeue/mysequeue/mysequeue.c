#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"sequeue.h"

sequeue_t *CreateEmptySequeue()
{
	sequeue_t *p;
	p = (sequeue_t *)malloc(sizeof(sequeue_t));
	
	if (p)
	{
		p->front = p->rear = 0;
	}
	
	return p;
}

void DestroySequeue(sequeue_t *queue)
{
	assert(queue);
	//after assert, queue exists
	
	free(queue);
}


void ClearSequeue(sequeue_t *queue)
{
	assert(queue);
	//after assert, queue exists
	
	queue->front = queue->rear = 0;
}


int EmptySequeue(sequeue_t *queue)
{
	if (!queue)
		return -1; //queue is NULL
	
	if (queue->front == queue->rear)
		return 1; //queue empty
	else	
		return 0; //queue not empty
}


int FullSequeue(sequeue_t *queue)
{
	if (!queue)
		return -1; //queue is NULL
	
	if ((queue->rear+1)%N == queue->front)
		return 1; //queue full
	else
		return 0; //queue not full
}


int EnQueue(sequeue_t *queue, data_t x)
{
	assert(queue);
	//after assert, queue exists
	
	if (FullSequeue(queue))
		return -1; //queue is already full
	
	queue->rear = (queue->rear + 1) % N;
	queue->data[queue->rear] = x;
	
	return 0;
}


int DeQueue(sequeue_t *queue, data_t *x)
{
	assert(queue);
	//after assert, queue exists
	
	assert(x);
	//after assert, x is not NULL
	
	if (EmptySequeue(queue))
		return -1; //queue is already empty
		
	queue->front = (queue->front + 1) % N;	
	*x = queue->data[queue->front];
	
	return 0; 
}