/*************************************************************************
    > File Name: myquick_sort.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Wed 13 May 2015 08:48:14 PM CST
 ************************************************************************/

#include<stdio.h>

void sort_quick(int s[], int low, int high)
{
	int i = 0;
	data_t u;
	linkstack_t *stack; //链式存储的栈

	stack = CreateEmptyLinkstack();

	u.low = low;
	u.high = high;
	
	PushStack(stack, u);

	while (0 == EmptyLinkstack(stack))
	{
		PopStack(stack, &u);
		low = u.low;
		high = u.high;

		while(low < high)
		{
			i = partition(s, low, high);
			if((i+1)<high)
			{
				u.low = i+1;
				u.high = high;
				PushStack(stack, u);
			}

			high = i-1;
		}
	}
}
