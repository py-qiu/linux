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

#include "sqstack.h"

sqstack_t *CreateEmptySqstack(int max_depth)
{
	sqstack_t *stack;

	stack = (sqstack_t *)malloc(sizeof(sqstack_t));
	if (stack) {
		stack->data = (data_t *)malloc(sizeof(data_t) * max_depth);
		if (!stack->data) {
			free(stack);
			return NULL;
		}
		stack->max_depth = max_depth;
		stack->top = -1; /* full stack */
	}

	return stack;
}

void DestroySqstack(sqstack_t *stack)
{
	if (stack) {
		if (stack->data) free(stack->data);

		free(stack);
	}
}

int EmptySqstack(sqstack_t *stack)
{
	if (!stack) return -1;
	
	return (-1 == stack->top ? 1 : 0);
}

int FullSqstack(sqstack_t *stack)
{
	if (!stack) return -1;
	
	return (stack->max_depth - 1 == stack->top ? 1 : 0);
}

void ClearSqstack(sqstack_t *stack)
{
	stack->top = -1;

	return;
}

int PushStack(sqstack_t *stack, data_t x)
{
	if (FullSqstack(stack)) return -1;
	
	stack->top++;
	stack->data[stack->top] = x;

	return 0;
}

int PopStack(sqstack_t *stack, data_t *x)
{
	if (EmptySqstack(stack)) return -1;

	if (x)
		*x = stack->data[stack->top];

	stack->top--;
	
	return 0;
}

int GetTop(sqstack_t *stack, data_t *x)
{
	if (EmptySqstack(stack)) return -1;

	if (x)
		*x = stack->data[stack->top];

	return 0;
}
