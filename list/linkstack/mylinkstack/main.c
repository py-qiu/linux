#include<stdio.h>
#include<stdlib.h>
#include"datatype.h"
#include"linkstack.h"
#include<assert.h>
#define N 10

void iterate_stack(linkstack_t *stack)
{
	assert(stack);
	//after assert, stack exists
	
	linkstack_t *p;
	p = stack->next;
	printf("iterate stack:\n");
	while (p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}

int main()
{
	linkstack_t *stack = NULL;
	int flag = 0;
	int i = 0;
	data_t data = 0;
	
	printf("creat empty stack\n");
	stack = CreateEmptyLinkstack();
	if (NULL == stack)
	{
		printf("Create stack failed\n");
		return -1;	
	}
	
	flag = EmptyLinkstack(stack);
	if (flag)
		printf("stack empty\n");
	else if (0 == flag)
		printf("stack not empty\n");
	else
		printf ("error\n");
		
	for (i=0; i<N; i++)
	{
		if (0 != PushStack(stack, i*i+1))
			printf("push stack error\n");
	}
	
	iterate_stack(stack);
	
	printf("pop stack\n");
	PopStack(stack, &data);
	printf("pop result : %d\n", data);
	
	flag = EmptyLinkstack(stack);
	if (flag)
		printf("stack empty\n");
	else if (0 == flag)
		printf("stack not empty\n");
	else
		printf ("error\n");
		
	printf("clear stack\n");
	ClearLinkstack(stack);
	
	flag = EmptyLinkstack(stack);
	if (flag)
		printf("stack empty\n");
	else if (0 == flag)
		printf("stack not empty\n");
	else
		printf ("error\n");
		
	printf("destroy stack\n");
	DestroyLinkstack(stack);
	
	return 0;
}
