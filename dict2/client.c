/*************************************************************************
  > File Name: client.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Fri 29 May 2015 11:07:01 AM CST
 ************************************************************************/

#include "include.h"

int main()
{
	int input = 0;

	if ((sock_client = client_init()) > 0)
	{
		printf ("client > client initialize success\n");
	}

	/*step1, select one function to execute*/
step1:
	printf ("\n");
	printf ("********************************************************\n");
	printf ("*** 1:Register  2:Login  3:History  4:Logout  5:Quit ***\n");
	printf ("********************************************************\n");

	scanf ("%d", &input);

	switch (input)
	{
		case 1:
			func_register();
			goto step1;
		case 2:
			if (1 != func_login())/*login failed*/
			{
				goto step1;
			}
			/*after login success, start query function*/
			func_query();
			goto step1;
		case 3:
			func_history();
			goto step1;
		case 4:
			func_logout();
			goto step1;
		case 5:
			func_quit();
			break;
		default:
			break;
	}

	return 0;
}

