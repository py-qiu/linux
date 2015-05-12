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
 * 20150511	unicornx	rename param data to x 
 *				for pop and get
 */
#ifndef _LINK_STACK_H_
#define _LINK_STACK_H_

#include "datatype.h"

/*
 * for the case the stack is implemented in linked-list.
 * the empty stack will at least contain ONE node to
 * represent the stack object, we call it header node.
 * when PUSH, the new element will be inserted at the
 * top of the stack,  after the header node, as the 2nd node.
 * it's a cheaper solution, reversely POP will delete the node 
 * from the top. Overall, the stack type is still "full-stack".
 */
typedef struct node_t{
	
	data_t		data;
	struct node_t	*next;
	
} linkstack_t;

/* 
 * create a stack and init it as empty 
 * Input:	void
 * Output:	void
 * Return:	new list, NULL when failed 
 */
linkstack_t *CreateEmptyLinkstack();

/* 
 * destroy a stack 
 * Input:
 *	stack: the stack to be destroied. 
 * Output:	void
 * Return:	void
 */
void DestroyLinkstack(linkstack_t *stack);

/*
 * clear the stack, reset it as empty
 * Input:
 *	stack:	the list to be cleared. 
 * Output:	void
 * Return:	void
 */
void ClearLinkstack(linkstack_t *stack);

/* 
 * judge if the stack is empty
 * Input:
 *	stack: the stack to be tested. 
 * Output:	void
 * Return:
 *	1:	stack is empty
 *	0:	not
 *	-1:	error
 */
int EmptyLinkstack(linkstack_t *stack);

/* 
 * Push
 * Input:
 *	stack:	the list to be operated.
 *	x:	the data to be pushed
 * Output:	void
 * Return:
 *	0:	success
 *	!0:	error, e.g. the memory is used up. generally for 
 *		linklist implementation, the stack hardly be full
 *		except the memory is used up.
 */
int PushStack(linkstack_t *stack, data_t x);

/* 
 * Pop
 * Input : 
 *	stack: the list to be operated.
 * Output:
 *	x:	caller should allocate the data and provide 
 *		the address. PopStack will copy the data
 *		to that address as output. If the caller don't want
 *		the data, just provide NULL.
 * Return:	
 *	0:	success, pop one
 *	-1:	failed, or the stack is already empty 
 */
int PopStack(linkstack_t *stack, data_t *x);

/*
 * get the data on the top of the stack
 * Input : 
 *	stack: the list to be operated.
 * Output:
 *	x:	caller should allocate the data and provide 
 *		the address. GetTop will copy the data
 *		to that address as output. If the caller don't want
 *		the data, just provide NULL.
 * Return:	
 *	0:	success, get the top one
 *	-1:	failed, or the stack is already empty 
 */
int GetTop(linkstack_t *stack, data_t *x);

#endif /* _LINK_STACK_H_ */
