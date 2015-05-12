#include<stdlib.h>
#include<stdio.h>
#include"sqstack.h"
#include<assert.h>

sqstack_t *CreateEmptySqstack(int max_depth)
{
	sqstack_t *p;
	
	p = (sqstack_t *)malloc(sizeof(sqstack_t));
	
	if (p)
	{
		p->data = (data_t *)malloc(sizeof(data_t) * max_depth);
		
		if (!p->data)
		{
			free (p);
			return NULL;
		}
		else
		{
			p->top = -1;
			p->max_depth = max_depth;
		}
	}
	
	return p;
}


void ClearSqstack(sqstack_t *stack)
{
	assert(stack);
	//after assert, stack exists
	
	stack->top = -1;
}


void DestroySqstack(sqstack_t *stack)
{
	assert(stack);
	//after assert, stack exists
	
	free (stack->data);
	free (stack);
}


int EmptySqstack(sqstack_t *stack)
{
	if (!stack)
		return -1; //error
	
	return (stack->top == -1 ? 1 : 0);
}


int FullSqstack(sqstack_t *stack)
{
	if (!stack)
		return -1; //error
		
	return (stack->top == stack->max_depth-1 ? 1 :0);		
}


int PushStack(sqstack_t *stack, data_t x)
{
	assert(stack);
	//after assert, stack exists
	
	if (FullSqstack(stack))
	{
		printf("stack full\n");
		return -1;
	}
	
	stack->data[++stack->top] = x;
	
	return 0;
}


int PopStack(sqstack_t *stack, data_t *x)
{
	assert(stack);
	//after assert, stack exists
	assert(x);
	//after assert, x is not NULL
	
	if (EmptySqstack(stack))
	{
		printf("stack empty\n");
		return -1;
	}
	
	*x = stack->data[stack->top--];
	
	return 0;
}


int GetTop(sqstack_t *stack, data_t *x)
{
	assert(stack);
	//after assert, stack exists
	assert(x);
	//after assert, x is not NULL
	
	if (EmptySqstack(stack))
	{
		printf("stack empty\n");
		return -1;
	}
	
	*x = stack->data[stack->top];
	
	return 0;
}
