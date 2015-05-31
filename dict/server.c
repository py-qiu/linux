/*************************************************************************
    > File Name: server.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Fri 29 May 2015 10:30:31 AM CST
 ************************************************************************/

#include "include.h"

int main()
{
	while (server_init() < 0)
	{
		printf ("server > initialize server failed\n");
		sleep(5);
	}
accept:
	while (server_accept() < 0)
	{
		printf ("server > run server service failed\n");
		sleep(5);
	}
	
	while (1)
	{
		if (server_running() < 0)
		{
			printf ("server > server running error\n");
			sleep(3);
		}
		else
		{
			printf ("server > client exit\n");
			sleep(2);
			break;
		}
	}
	goto accept;
	return 0;
}
