/*************************************************************************
    > File Name: select_sort.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 28 Apr 2015 01:28:21 PM CST
 ************************************************************************/

#include<stdio.h>
#define N 10

int main()
{
	int a[N] = {0};
	int i = 0;
	int j = 0;
	int r = 0;
	int t = 0;

	for (i=0; i<N; i++)
	{
		scanf("%d", &a[i]);
	}

	for (i=0; i<N-1; i++)
	{
		r = i;
		for (j=i+1; j<N; j++)
		{
			if (a[j] < a[r])
			{
				r = j;
			}
		}
		//
		if (r != i)
		{
			t = a[r];
			a[r] = a[i];
			a[i] = t;
		}
	}
	//
	for (i=0; i<N; i++)
	{
		printf("%-3d", a[i]);
	}
	printf("\n");

	return 0;
}
