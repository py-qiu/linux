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
 * 20150511	unicornx	format improvement
 */
#include <stdio.h>
#include <stdlib.h>

#include "linkqueue.h"

linkqueue_t *CreateEmptyLinkqueue()
{
	linkqueue_t *queue;

	queue = (linkqueue_t *)malloc(sizeof(linkqueue_t));
	if (NULL == queue) return NULL;

	queue->rear = queue->front = NULL;

	return queue;
}

void DestroyLinkqueue(linkqueue_t *queue)
{
	if (queue) {
		ClearLinkqueue(queue);
		free(queue);
	}
}

void ClearLinkqueue(linkqueue_t *queue)
{
	linknode4q_t *node_remove;

	/* start from the queue head */
	node_remove = queue->front;
	while (NULL != node_remove) {
		/* move front to the next */
		queue->front = queue->front->next;

		/* free the original queue head node */
		free (node_remove);

		/* move to new queue head node */
		node_remove = queue->front;
	}

	/* rear to NULL */
	queue->rear = NULL;

	return;
}

int EmptyLinkqueue(linkqueue_t *queue)
{
	if (!queue) return -1;
	return (queue->front == NULL ? 1 : 0);
}

int EnQueue(linkqueue_t *queue, data_t x)
{
	linknode4q_t *node_new;

	if (!queue) return -1;

	node_new = (linknode4q_t *)malloc(sizeof(linknode4q_t));
	if (!node_new) return -1;
	node_new->data = x;
	node_new->next = NULL;

	if (NULL == queue->front) { 
		/* 
		 * if the queue is empty
		 * make front and rear both point to the new node
		 */
		queue->front = queue->rear = node_new;
	} else {
		/* 
		 * if the queue is not empty
		 * just change the rear to point to the new node due to
		 * the new node is appended at the tail
		 * for the front, no update, still point to
		 * the first node
		 */
		queue->rear->next = node_new;
		queue->rear = node_new;
	}

	return 0;
}

int DeQueue(linkqueue_t *queue, data_t *x)
{
	linknode4q_t *node_remove;
		
	if (!queue) return -1;

	if (NULL == queue->front) return -1; /* empty */

	/* backup first node */
	node_remove = queue->front;

	/* redirect front to the next element */
	queue->front = node_remove->next;

	/* if the remain queue is empty, update the rear */
	if (NULL == queue->front) queue->rear = NULL;

	/* output the data if caller wanted */
	if (x) {
		*x = node_remove->data;
	}
	
	/* now we can free the first element safely */
	free(node_remove);

	return 0;
}
