#include<stdio.h>
#include"sqstack.h"
#include<stdlib.h>
#define MAX_DEPTH 10

int main()
{
	int i = 0;
	int flag = 0;
	int *x = (int *)malloc(sizeof(int));
	
	//CreateEmptySqstack
	printf("creat empty stack\n");
	sqstack_t *stack;
	stack = CreateEmptySqstack(MAX_DEPTH);
	
	//EmptySqstack
	printf("test if stack is empty?\n");
	flag = EmptySqstack(stack);
	
	if (flag)//start of if
	{
		printf ("stack empty\n");
	}
	else if (0 == flag)
	{
		printf ("stack not empty\n");
	}
	else
	{
		printf("stack error\n");
	}//end of if
	
	//PushStack
	printf("push stack\n");
	for (i=0; i<MAX_DEPTH; i++)
	{
		if (0 != PushStack(stack, i))
			{break;}	
		
		//GetTop
		printf("push %d in %d position\n", i, i);
		GetTop(stack, x);
				
	//	printf("%d\n", *x);
	}
	
	//after push
	printf("after push, test if stack is full?\n");
	flag = FullSqstack(stack);
	if (1 == flag)//start of if
	{
		printf ("stack full\n");
	}
	else if (0 == flag)
	{
		printf ("stack not full\n");
	}
	else
	{
		printf("stack error\n");
	}//end of if
	

	//PopStack
	printf("pop stack 1 time\n");
	PopStack(stack, x);
	printf("%d\n", *x);

	printf("after one pop, test if stack is full?\n");
	flag = FullSqstack(stack);
	if (flag)//start of if
	{
		printf ("stack full\n");
	}
	else if (0 == flag)
	{
		printf ("stack not full\n");
	}
	else
	{
		printf("stack error\n");
	}//end of if
	
	//ClearSqstack
	printf("clear stack\n");
	ClearSqstack(stack);

	printf("after clear,test if stack is empty?\n");
	flag = EmptySqstack(stack);
	
	if (flag)//start of if
	{
		printf ("stack empty\n");
	}
	else if (0 == flag)
	{
		printf ("stack not empty\n");
	}
	else
	{
		printf("stack error\n");
	}//end of if
	
	printf("destroy stack\n");
	DestroySqstack(stack);
	
	return 0;
}
