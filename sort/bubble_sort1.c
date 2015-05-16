/*************************************************************************
  > File Name: bubble_sort1.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Tue 28 Apr 2015 12:50:16 PM CST
 ************************************************************************/

#include<stdio.h>
#define N 10

int main()
{
	int a[N] = {0};
	int i = 0;
	int j = 0;

	for (i=0; i<N; i++)
	{
		scanf("%d", &a[i]);
	}
	//
	for (i=0; i<N-1; i++)
	{
		for (j=0; j<N-1-i; j++)
		{
			if (a[j] > a[j+1])
			{
				a[j] ^= a[j+1];
				a[j+1] ^= a[j];
				a[j] ^= a[j+1];
			}//
		}//
	}//

	for (i=0; i<N; i++)
	{
		printf("%3d", a[i]);
	}

	return 0;
}
