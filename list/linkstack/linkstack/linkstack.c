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
#include <stdio.h>
#include <stdlib.h>

#include "linkstack.h"

linkstack_t *CreateEmptyLinkstack()
{
	linkstack_t *s;

	s = (linkstack_t *)malloc(sizeof(linkstack_t));
	if (s) {
		s->next = NULL;
	}

	return s;
}

void DestroyLinkstack(linkstack_t *stack)
{
	if (stack) {
		/* clear the stack linked list */
		ClearLinkstack(stack);
		
		/* free the stack header node */
		free(stack);
	}
}

int EmptyLinkstack(linkstack_t *stack)
{
	if (stack) {
		return ((NULL == stack->next) ? 1 : 0);
	} else {
		return -1;
	}
}

void ClearLinkstack(linkstack_t *stack)
{
	linkstack_t *node; /* pointer to the node to be removed */

	if (!stack) return;

	while ( NULL != stack->next ) {
		/* disconnect the one to be removed */
		node = stack->next;
		stack->next = node->next;

		free(node);
	}

	return;
}

/* 
 * Push will insert the data from the 2nd 
 * position of the linked list.
 * it's a cheaper solution bcos it is quick.
 */
int PushStack(linkstack_t *stack, data_t x)
{
	linkstack_t *node; /* node to be inserted */

	if (!stack) return -1;

	node = (linkstack_t *)malloc(sizeof(linkstack_t));
	if (NULL == node) {
		return -1;
	}
	node->data = x;

	node->next = stack->next;
	stack->next = node;

	return 0;
}

int PopStack(linkstack_t *stack, data_t *x)
{
	linkstack_t *node; /* pointer to the node to be removed */
	
	if (!stack) return -1;

	if (!(stack->next)) return -1; /* stack is empty */

	/* pop from the head of the list */
	node = stack->next;
	stack->next = node->next;

	if (x) {
		*x = node->data;
	}

	/* now we can free the node safely */
	free(node);
	
	return 0;
}

int GetTop(linkstack_t *stack, data_t *x)
{
	if (!stack) return -1;

	if (!(stack->next)) return -1; /* stack is empty */
	
	if (x) {
		*x = stack->next->data;
	}
	return 0;
}
