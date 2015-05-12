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

#include "linkstack.h"

int max_depth;

int Push_Pop(linkstack_t *stack, data_t x);

/*
 * iterate through the stack, from the top to the base 
 * and print out info of each element
 */
void iterate_stack(linkstack_t *stack)
{
	linkstack_t *node; /* pointer to the node to be iterated */
	
	if (!stack) return;

	printf("stack = top{");

	node = stack->next;
	while (NULL != node) {
		printf("%d,", node->data);
		node = node->next;
	}
	
	if (1 == EmptyLinkstack(stack))
		printf("}base\n");
	else
		printf("\b}base\n");
}

int main(int argc, char *argv[])
{
	linkstack_t *stack;

	if (argc < 2) {
		printf("Usage: %s <len>\n", argv[0]);
		return -1;
	}

	max_depth = atoi(argv[1]);
	
	stack = CreateEmptyLinkstack();

	if (!stack) {
		printf("CreateEmptyLinkstack error\n");
		return -1;
	}

	Push_Pop(stack, 1);

	DestroyLinkstack(stack);
	
	return 0;
}

int Push_Pop(linkstack_t *stack, data_t x)
{
	data_t data_pop;
	static int	depth = 0;	

	if (depth == max_depth) {
		printf("----- reach the max depth of the stack!\n");
		return 0;
	} else {
		depth++;
		
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

