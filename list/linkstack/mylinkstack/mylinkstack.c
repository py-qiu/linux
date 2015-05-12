#include<stdio.h>
#include<stdlib.h>
#include"linkstack.h"
#include<assert.h>

linkstack_t *CreateEmptyLinkstack()
{
	linkstack_t *p;
	p = (linkstack_t *)malloc(sizeof(linkstack_t));
	
	if (p)
	{
		p->next = NULL;
	}
	
	return p;
}

void ClearLinkstack(linkstack_t *stack)
{
	assert(stack);
	//after assert, stack exists
	
	linkstack_t *node;
	node = stack->next;
	
	while (node)
	{
		stack->next = node->next;
		free(node);
		node = stack->next;
	}
	
}


void DestroyLinkstack(linkstack_t *stack)
{
	assert(stack);
	//after assert, stack exists
	
	ClearLinkstack(stack);
	
	free (stack);
}


int EmptyLinkstack(linkstack_t *stack)
{
	if (!stack)
		return -1; //stack error
	
	return (stack->next == NULL ? 1 : 0);
}


int PushStack(linkstack_t *stack, data_t x)
{
	assert(stack);
	//after assert, stack exists
	
	linkstack_t *p;
	p = (linkstack_t *)malloc(sizeof(linkstack_t));
	
	if (!p)
		return -1; //memory used up
		
	p->data = x;
	p->next = stack->next;
	stack->next = p;
	
	return 0;
}


int PopStack(linkstack_t *stack, data_t *x)
{
	if (!stack)
		return -1; //error, stack invalid
		
	if (!x)
		return -1; //error, x invalid
		
	if (NULL == stack->next)
		return -1; //error, stack empty
		
	linkstack_t *p;
	p = stack->next;
	
	*x = p->data;
	stack->next = p->next;
	free(p);
	
	return 0;
}


int GetTop(linkstack_t *stack, data_t *x)
{
	if (!stack)
		return -1; //error, stack invalid
		
	if (!x)
		return -1; //error, x invalid
		
	if (NULL == stack->next)
		return -1; //error, stack empty
		
	*x = stack->next->data;
	
	return 0;
}
