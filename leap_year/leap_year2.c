/*************************************************************************
    > File Name: leap_year2.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Mon 27 Apr 2015 07:27:24 PM CST
	asdw
 ************************************************************************/

#include<stdio.h>
int main()
{
	int i = 2000;
	int n = 0;
	while(i < 2501)
	{
		if(i % 4 != 0)
		{
			printf("%d is not a leap year\n", i);
		}
		else
		{
			if(i % 100 != 0)
			{
				printf("%d is a leap year\n", i);
				n++;
			}
			else 
			{
				if(i % 400 == 0)
				{
					printf("%d is a leap year\n", i);
					n++;
				}
			}
		}//endif
		i++;
	}	//
	printf("number of total leap is %d\n", n);

	return 0;
}
