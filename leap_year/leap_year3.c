/*************************************************************************
    > File Name: leap_year3.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Mon 27 Apr 2015 07:36:13 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
	int i = 2000;
	int n = 0;
	while (i < 2501)
	{
		if (i % 4 == 0 && ((i % 100 != 0) || (i % 400 == 0)))
		{
			n++;
		}
		i++;
	}
	printf("number of total leap year is %d\n", n);
	return 0;
}
