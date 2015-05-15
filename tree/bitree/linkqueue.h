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
#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

#include "datatype.h"

typedef struct node4q_t {
	data_t data;
	struct node4q_t *next;
} linknode4q_t, *linklist4q_t;

typedef struct
{
	linklist4q_t front, rear;
} linkqueue_t;

/* 
 * create a queue and init it as empty 
 * Input:	void
 * Output:	void
 * Return:	new queue, NULL when failed 
 */
linkqueue_t *CreateEmptyLinkqueue();

/* 
 * destroy a queue 
 * Input:
 *	queue: the queue to be destroied. 
 * Output:	void
 * Return:	void
 */
void DestroyLinkqueue(linkqueue_t *queue);

/*
 * clear the queue, reset it as empty
 * Input:
 *	queue:	the queue to be cleared. 
 * Output:	void
 * Return:	void
 */
void ClearLinkqueue(linkqueue_t *queue);

/* 
 * judge if the queue is empty
 * Input:
 *	queue: the queue to be tested. 
 * Output:	void
 * Return:
 *	1:	empty
 *	0:	not 
 *	-1:	error
 * Note: doesn't make sense to judge full for linked list storage method
 */
int EmptyLinkqueue(linkqueue_t *queue);

/* 
 * In Queue
 * Input:
 *	queue:	the queue to be operated.
 *	x:	the data to be entered
 * Output:	void
 * Return:
 *	0:	success
 *	!0:	error
 */
int EnQueue(linkqueue_t *queue, data_t x);

/* 
 * Out Queue
 * Input:
 *	queue:	the queue to be operated.
 *	x:	caller should allocate the data and provide 
 *		the address. DeQueue will copy the data
 *		to that address as output. If the caller don't want
 *		the data, just provide NULL.
 * Output:	void
 * Return:
 *	0:	success
 *	-1:	failed, or the queue is already empty
 */
int DeQueue(linkqueue_t *queue, data_t *x);

#endif /* _LINK_QUEUE_H_ */

