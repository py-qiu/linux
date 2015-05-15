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

#include "linkqueue.h"

void iterate_queue(linkqueue_t * queue)
{
	linknode4q_t *node;

	/* browse from the front to the rear */
	printf("queue = front{");

	node = queue->front;
	while (NULL != node) {
		printf("%2d,", node->data);
		node = node->next;
	}
	
	if (1 == EmptyLinkqueue(queue)) {
		printf("}rear\n");
	} 
	else {
		printf("\b}rear\n");
	}

	return;
}

int main()
{
	int i;
	data_t data;
	linkqueue_t *queue;

	queue = CreateEmptyLinkqueue();

	for (i = 1; i < 10; i++) {
		printf("Enter %2d: ", i);
		EnQueue(queue, i);
		iterate_queue(queue);
	}

	while ( !EmptyLinkqueue(queue) ){
		DeQueue(queue, &data);
		printf("Out   %2d: ", data);
		iterate_queue(queue);
	}

	/* run again */
	for (i = 1; i < 10; i++) {
		printf("Enter %2d: ", i);
		EnQueue(queue, i);
		iterate_queue(queue);
	}

	while ( !EmptyLinkqueue(queue) ){
		DeQueue(queue, &data);
		printf("Out   %2d: ", data);
		iterate_queue(queue);
	}
	
	DestroyLinkqueue(queue);

	return 0;
}

