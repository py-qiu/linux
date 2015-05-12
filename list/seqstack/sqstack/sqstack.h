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
#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_

#include "datatype.h"

typedef struct
{
	data_t	*data;	/* storage of the stack, 
			 * in array, dynamic allocated 
			 */
	int	top;	/* current top of the stack, the value of 
			 * top is the index of the data array.
			 * note the type of stack we create here
			 * is "full-stack", which means the top always
			 * points to the location in which the last 
			 * item was stored. A push will first 
			 * increment the stack pointer, then store
			 * the value. Another stack type is called
			 * "empty-stack": of which the top points to 
			 * the location in which the next item will be 
			 * stored. A push will first store the value, 
			 * and then increment the stack pointer. 
			 */
	int	max_depth; /* max depth of stack, initialized when the 
			    * stack is created, used to limit top
			    * not exceed the max depth 
			    */
} sqstack_t;

/* 
 * create a stack and init it as empty 
 * Input:
 *	max_depth: max depth of the stack 
 * Output:	void
 * Return:	new list, NULL when failed 
 */
sqstack_t *CreateEmptySqstack(int max_depth);

/* 
 * destroy a stack 
 * Input:
 *	stack: the stack to be destroied. 
 * Output:	void
 * Return:	void
 * Note:	after destroy, the stack can not be used any more
 */
void DestroySqstack(sqstack_t *stack);

/*
 * clear the stack, reset it as empty
 * Input:
 *	stack:	the list to be cleared. 
 * Output:	void
 * Return:	void
 */
void ClearSqstack(sqstack_t *stack);

/* 
 * judge if the stack is empty
 * Input:
 *	stack: the stack to be tested. 
 * Output:	void
 * Return:
 *	1:	empty
 *	0:	not 
 *	-1:	error
 */
int EmptySqstack(sqstack_t *stack);

/* 
 * judge if the stack is full 
 * Input:
 *	stack: the stack to be tested. 
 * Output:	void
 * Return:
 *	1:	full
 *	0:	not 
 *	-1:	error
 */
int FullSqstack(sqstack_t *stack);

/* 
 * Push
 * Input:
 *	stack:	the list to be operated.
 *	x:	the data to be pushed
 * Output:	void
 * Return:
 *	0:	success
 *	!0:	error or the stack is already full.
 */
int PushStack(sqstack_t *stack, data_t x);

/* 
 * Pop
 * Input : 
 *	stack: the list to be operated.
 * Output:
 *	x:	caller should allocate the space of 'x'.
 *		PopStack will copy the data of pop element
 *		to x as output. If the caller don't want
 *		the data, just provide NULL.
 * Return:	
 *	0:	success, pop one
 *	-1:	error, e.g. the stack is already empty 
 */
int PopStack(sqstack_t *stack, data_t *x);

/*
 * get the data on the top of the stack
 * Input : 
 *	stack: the list to be operated.
 * Output:
 *	x:	caller should allocate the space of x and provide 
 *		the address of x as input. GetTop will copy the data
 *		to x as output. If the caller don't want
 *		the data, just provide NULL.
 * Return:	
 *	0:	success, get the top one
 *	-1:	error, e.g. the stack is already empty 
 */
int GetTop(sqstack_t *stack, data_t *x);

#endif /* _SEQ_STACK_H_ */
