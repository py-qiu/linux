/*************************************************************************
    > File Name: myquick_sort.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Wed 13 May 2015 08:07:42 PM CST
 ************************************************************************/

#include<stdio.h>
#define N 8

/*
 *partition(),分区函数，执行一次的结果是，以第一个数为基点，
						先找小于基点的数的位置，小于基点的数挪到左边，
						 再找大于基点的数的位置，大于基点的数挪到右边，
						 直到最后i==j,把基点挪到最后空的i位置上,
						 返回基点位置，为下一次分区做准备
 */

int partition(int s[], int low, int high)
{
	int i = 0;
	int j = 0;
	int pivot = 0;

	i = low;
	j = high;
	pivot = s[low];

	while (i<j) //当i<j时，还有可比区间，否则已分区好
	{
		/*
		 *从右向左筛选
		 */
		while ((i<j) && (s[j]>=pivot))
		{
			j--;/*一直找，直到s[j]<pivot;可以s[j]换到s[i]
				 *或者直到i == j,右边的数全部比左边的数小
				 */
		}

		if (i<j)
		{
			s[i] = s[j];
		}

		while ((i<j) && (s[i]<=pivot))
		{
			i++;   /*向右一只找，直到s[i]>pivot,可以交换到右边
					*或者i==j,左边的数全比右边的小
					*/
		}

		if (i<j)
		{
			s[j] = s[i];
		}
	}
	s[i] = pivot;

	return i;
}

/*
 *递归快速排序，依次递归先对左半部分排序，返回时递归返回再对右半部分排序，直到退出时，排序已完成
 */

void sort_quick_r(int s[], int low, int high)
{
	int pivot = 0;
	pivot =  partition(s, low, high);
	
	if ((pivot-1) > low)
	{
		sort_quick_r(s, low, pivot-1);
	}

	if ((pivot+1) < high)
	{
		sort_quick_r(s, pivot+1, high);
	}

	return ;
}

int main()
{
	int s[N] = {50, 36, 66, 76, 36, 12, 25, 95};

	int i = 0;	

	for (i=0; i<N; i++)
	{
		printf("%d\n", s[i]);
	}

	sort_quick_r(s, 0, 7);

	for (i=0; i<N; i++)
	{
		printf("%d\n", s[i]);
	}

	return 0;
}
