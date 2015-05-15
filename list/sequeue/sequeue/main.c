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

void iterate_queue(sequeue_t * queue)
{
	int i;
	
	data_t a[N];
	
	if (!queue) return;

	for (i = 0; i < N; i++) {
		a[i] = '_';
	}

	i = queue->front;
	a[i] = 'x';
	
	while (i != queue->rear) {
		i++;
		i = i % N;
		a[i]= queue->data[i];
	}
	
	printf("queue = (f(%d),r(%d)) {", queue->front, queue->rear);
	
	for (i = 0; i < N; i++) {
		printf("%c ", a[i]);
	}
	printf("\b}\n");
}

int main()
{
	int i;
	data_t data;
	sequeue_t *queue;

	queue = CreateEmptySequeue();

	printf("First round!-----------------------------------------------\n");
	for (i = 0; i < 20; i++) {
		if ( !FullSequeue(queue) ) {
			printf("Enter %c: ", '1' + i);
			EnQueue(queue, '1' + i);
			iterate_queue(queue);
		} else {
			printf("queue is full\n");
			break;
		}
	}

	while ( !EmptySequeue(queue) ){
		DeQueue(queue, &data);
		printf("Out   %c: ", data);
		iterate_queue(queue);
	}

	printf("Second round!----------------------------------------------\n");
	
	for (i = 0; i < 20; i++) {
		if ( !FullSequeue(queue) ) {
			printf("Enter %c: ", '1' + i);
			EnQueue(queue, '1' + i);
			iterate_queue(queue);
		} else {
			printf("queue is full\n");
			break;
		}
	}

	while ( !EmptySequeue(queue) ){
		DeQueue(queue, &data);
		printf("Out   %c: ", data);
		iterate_queue(queue);
	}
	
	DestroySequeue(queue);

	return 0;
}

