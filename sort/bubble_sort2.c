/*************************************************************************
    > File Name: bubble_sort2.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 28 Apr 2015 01:09:41 PM CST
 ************************************************************************/

#include<stdio.h>
#define N 10

int main()
{
	int a[N] = {0};
	int j = 0;
	int flag = N;
	int k = 0;

	for (j=0; j<N; j++)
	{
		scanf("%d", &a[j]);
	}
//flag记录最后一个变化被交换的数`
	while (flag > 0)
	{
		k = flag;
		flag = 0;
		for (j=1; j<k; j++)
		{
			if (a[j-1] > a[j])
			{
				flag = j;
				a[j] ^= a[j-1];
				a[j-1] ^= a[j];
				a[j] ^= a[j-1];
			}
		}//
	}//

	for (j=0; j<N; j++)
	{
		printf("%3d", a[j]);
	}
	printf("\n");

	return 0;
}
