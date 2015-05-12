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
 /*
  * Requirements:
  * 1) typedef int data_t;
  * 2) Create the seqstack, init the depth of the stack
  * 	according to user's input.
  * 3) Push new data element into the stack till it is full;
  * 	intial data value is 1 and value++ the time when pushing.
  * 4) After stack is full, pop the element out from the stack.
  * 5) Print content of the stack when push/pop.
  */
#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

int Push_Pop(sqstack_t *stack, data_t x);

/*
 * iterate through the stack, from the base to the top 
 * and print out info of each element
 */
void iterate_stack(sqstack_t *stack)
{
	int i;
	
	if (!stack) return;

	printf("stack = base{");
	
	if (stack->data) { /* just for protection */
		for (i = -1; i < stack->top;) {
			printf("%d,", stack->data[++i]);
		}	
	}
	
	if (1 == EmptySqstack(stack))
		printf("}top\n");
	else
		printf("\b}top\n");
}

int main(int argc, char *argv[])
{
	sqstack_t *stack;
	int max_depth;

	if (argc < 2) {
		printf("Usage: %s <max_depth>\n", argv[0]);
		return -1;
	}

	max_depth = atoi(argv[1]);
	
	stack = CreateEmptySqstack(max_depth);

	if (!stack) {
		printf("CreateEmptySqstack error\n");
		return -1;
	}

	Push_Pop(stack, 1);

	DestroySqstack(stack);
	
	return 0;
}

int Push_Pop(sqstack_t *stack, data_t x)
{
	data_t data_pop;
	
	if (FullSqstack(stack)) {
		printf("----- reach the max depth of the stack!\n");
		return 0;
	} else {
		printf("Push %d\n", x); 
		PushStack(stack, x++);
		iterate_stack(stack);

		Push_Pop(stack, x);

		PopStack(stack, &data_pop);
		printf("Pop %d\n", data_pop);
		iterate_stack(stack);

		return -1;
	}
}

