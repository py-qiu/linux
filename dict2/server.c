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
		printf ("server > run server_init() failed\n");
		sleep(5);
	}
accept:
	while (server_accept() < 0)
	{
		printf ("server > run server_accept() failed\n");
		sleep(5);
	}

	/********************************************************************************************/
	/********************************************************************************************/


	while (0 == recv_from(connfd_server, &client_msg))/*while receive message from client success*/
	{
		printf ("server > receive message from client success\n\n");
		printf ("*********************************************\n\n");
		client_back = client_msg;

		/*switch cmd_type according to client request code*/
		switch (client_msg.hdr.cmd_type)
		{
			case REQ_Register:
				{
					reg_func();
					break;
				}
			case REQ_Login:
				{
					login_func();
					break;
				}
			case REQ_Query:
				{
					query_func(fstream, client_msg.data.req_query.word);
					break;
				}
			case REQ_Logout:
				{
					logout_func(client_msg.hdr.usrname);
					break;
				}
			case REQ_History:
				{
					history_func(connfd_server, client_msg.hdr.usrname);
					break;
				}
			case REQ_Quit:
				{
					quit_func();
					sleep(4);
					goto accept;
				}
			default:
				break;
		}
		memset(&client_msg, 0x00, sizeof(client_msg));
		memset(&client_back, 0x00, sizeof(client_back));
		rewind(fstream);
	}

	/*receive message from client error*/
	printf ("server > receive message from client error\n");
	goto accept;
	return 0;
}
