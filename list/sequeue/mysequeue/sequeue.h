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
#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_

#include "datatype.h"

#define FIFO_LEN 9 		/* Max length of the FIFO */
#define N (FIFO_LEN + 1)	/* length of the array = FIFO_LEN + 1 */
/* 
 * the queue is implemented as a cycle array.
 * that's why the length of the array = FIFO_LEN + 1,
 * there is an extra element reserved in the array to
 * mark out the "cycle-head" of the FIFO. "reserved"
 * means we will NOT store data at that position.
 * the position of "cycle-head" may be changed during
 * operation on the queue and it is pointed by the 
 * "front", read source code for more details
 */
typedef struct {
	data_t	data[N];
	int	front;	/* front always points to the "cycle-head" */
	int	rear;	/* rear point to the rear postion element of the queue */

} sequeue_t;

/* 
 * create a queue and init it as empty 
 * Input:	void
 * Output:	void
 * Return:	new queue, NULL when failed 
 */
sequeue_t *CreateEmptySequeue();

/* 
 * destroy a queue 
 * Input:
 *	queue: the queue to be destroied. 
 * Output:	void
 * Return:	void
 */
void DestroySequeue(sequeue_t *queue);

/* 
 * judge if the queue is empty
 * Input:
 *	queue: the queue to be tested. 
 * Output:	void
 * Return:
 *	1:	empty
 *	0:	not 
 *	-1:	error, e.g. the queue is NULL
 */
int EmptySequeue(sequeue_t *queue);

/* 
 * judge if the queue is full 
 * Input:
 *	queue: the queue to be tested. 
 * Output:	void
 * Return:
 *	1:	full
 *	0:	not 
 *	-1:	error
 */
int FullSequeue(sequeue_t *queue);

/*
 * clear the queue, reset it as empty
 * Input:
 *	queue:	the queue to be cleared. 
 * Output:	void
 * Return:	void
 */
void ClearSequeue(sequeue_t *queue);

/* 
 * In Queue, add the element to the rear
 * Input:
 *	queue:	the queue to be operated.
 *	x:	the data to be entered
 * Output:	void
 * Return:
 *	0:	success
 *	!0:	error, e.g. the queue is already full.
 */
int EnQueue(sequeue_t *queue, data_t x);

/* 
 * Out Queue: remove the element from the front
 * Input:
 *	queue:	the queue to be operated.
 *	x:	caller should allocate the space for "x" and provide 
 *		the address. DeQueue will copy the data
 *		to that address as output. If the caller don't want
 *		the data, just provide NULL.
 * Output:	void
 * Return:
 *	0:	success
 *	-1:	error, e.g. the queue is empty
 */
int DeQueue(sequeue_t *queue, data_t *x);

#endif /* _SEQ_QUEUE_H_ */

