/*************************************************************************
    > File Name: leap_year.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Mon 27 Apr 2015 07:16:38 PM CST
	ASD
 ************************************************************************/

#include<stdio.h>
int main()
{
	int i = 2000;
	int n = 0;
	while (i < 2501)
	{
		if (i % 4 != 0)
		{
			i++;
			continue;
		}
		//
		if( i % 100 != 0)//能被4整除，但不能被100整除，是闰年
		{
			i++;
			n++;
			continue;
		}
		//
		if (i % 400 == 0)//能被4整除，能被100整除，又能被400整除，是闰年
		{
			n++;
			i++;
			continue;
		}
		i++;
		//
	}
	//
	printf("%d\n", n);

	return 0;
}
