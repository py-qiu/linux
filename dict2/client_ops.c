/*************************************************************************
  > File Name: client_ops.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Tue 02 Jun 2015 01:12:32 PM CST
 ************************************************************************/

#include "include.h"

/*
 * func_register()
 * register module
 */
void func_register()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Client > Register...\n");
	memset (&reg_send, 0x00, sizeof(reg_send));

	/*set command type to register*/
	reg_send.hdr.cmd_type = REQ_Register;

	/*get username*/
	getchar();
	printf ("Input your username > ");
	if (NULL == fgets (reg_send.hdr.usrname, MAXLEN_USRNAME+1, stdin))
	{
		perror ("Client > Get username error");
		return;
	}
	reg_send.hdr.usrname[strlen(reg_send.hdr.usrname)-1] = 0x00;

	/*get password*/
	printf ("Input your password > ");
	if (NULL == fgets(reg_send.data.req_register.passwd, MAXLEN_PASSWD+1, stdin))
	{
		perror ("Client > Get password error");
		return;
	}
	reg_send.data.req_register.passwd[strlen(reg_send.data.req_register.passwd)-1] = 0x00;

	/*send register information to server*/
	if (send_to(sock_client, &reg_send) < 0)
	{
		printf ("Client > Send register information error\n");
		return;
	}

	/*******************************************************/

	/*wait for back information*/
	if (recv_from(sock_client, &reg_recv) < 0)
	{
		printf ("Client > Receive register information err\n");
		return;
	}

	printf ("Client > Receive register information success\n");

	/*check the return code from server*/
	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:
			{
				printf ("Client > Register success\n");
				break;
			}
		case USER_ALREADY_EXIST:
			{
				printf ("Client > User already exists\n");
				break;
			}
		case EREG_INSERT_USER:
			{
				printf ("Client > Insert user failed\n");
				break;
			}
		case EREG_CREAT_USERS:
			{
				printf ("Client > Create table 'users' failed\n");
				break;
			}
		case EREG_CREAT_HISTORY:
			{
				printf ("Client > Create table 'history' failed\n");
				break;
			}
		default:
			{
				printf ("Client > bad response code : '%d'\n", reg_recv.hdr.ret_code);
				break;
			}
	}

	return ;
}



/* login function
 * success : 1
 * failed  : 0
 * error   :-1  
 */
int func_login()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Client > Login...\n");
	memset (&reg_send, 0x00, sizeof(reg_send));

	/*set command type to login*/
	reg_send.hdr.cmd_type = REQ_Login;

	/*get username*/
	getchar();
	printf ("Input your username > ");
	if (NULL == fgets (reg_send.hdr.usrname, MAXLEN_USRNAME+1, stdin))
	{
		perror ("Get username error");
		return -1;
	}
	reg_send.hdr.usrname[strlen(reg_send.hdr.usrname)-1] = 0x00;

	/*get password*/
	printf ("Input your password > ");
	if (NULL == fgets(reg_send.data.req_register.passwd, MAXLEN_PASSWD+1, stdin))
	{
		perror ("Get password error");
		return -1;
	}
	reg_send.data.req_register.passwd[strlen(reg_send.data.req_register.passwd)-1] = 0x00;

	/*send login information to server*/
	if (send_to(sock_client, &reg_send) < 0)
	{
		printf ("Client > Send login information error\n");
		return -1;
	}


	/*wait for back information*/
	if (recv_from(sock_client, &reg_recv) < 0)
	{
		printf ("Client > Receive login information error\n");
		return -1;
	}

	printf ("Client > Receive login information success\n");

	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:
			{
				printf ("Client > Login success\n");
				return 1;
			}
		case ELOGIN_USERS_EXIST:
			{
				printf ("Login failed : table 'USERS' does not exist\n");
				return 0;
			}
		case ELOGIN_USERNAME_EXIST:
			{
				printf ("Login failed : username '%s' does not exist\n", reg_send.hdr.usrname);
				return 0;
			}
		case ELOGIN_PASSWD:
			{
				printf ("'%s' Login failed : password wrong\n", reg_send.hdr.usrname);
				return 0;
			}
		case ELOGIN_ALREADY_LOGIN:
			{
				printf ("'%s' already login\n", reg_send.hdr.usrname);/*not used now*/
				return 1;
			}
		default :
			{
				printf ("bad response code : '%d'\n", reg_recv.hdr.ret_code);
				return 0;
			}
	}
}


/*
 * func_logout, 
 * success : 0
 * error   :-1
 */
int func_logout()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Client > Logout ...\n");
	memset (&reg_send, 0x00, sizeof(reg_send));

	/*set command type to logout*/
	reg_send.hdr.cmd_type = REQ_Logout;

	/*get username*/
	getchar();
	printf ("Input your username > ");
	if (NULL == fgets (reg_send.hdr.usrname, MAXLEN_USRNAME+1, stdin))
	{
		perror ("Get username error");
		return -1;
	}
	reg_send.hdr.usrname[strlen(reg_send.hdr.usrname)-1] = 0x00;

	/*send logout information to server*/
	if (send_to(sock_client, &reg_send) < 0)
	{
		printf ("Client > Send logout information error\n");
		return -1;
	}

	/*receive logout information from server*/
	if (recv_from(sock_client, &reg_recv) < 0)
	{
		printf ("Client > Receive logout information error\n");
		return -1;
	}

	printf ("Client > Receive logout information success\n");

	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:
			{
				printf ("Client > Logout success\n");
				break;
			}
		case ELOGOUT:
			{
				printf ("Client > Logout failed\n");
				return -1;
			}
		case ELOGOUT_ALREADY:
			{
				printf ("Client > Already logout\n");
				return -1;
			}
		default:
			{
				printf ("Client > Bad response code\n");
				return -1;
			}
	}
	return 0;
}



/*
 * func_query()
 * query the word
 * nornally, this function should not quit, 
 * unless user choose <00> to quit, or error occured
 * return value useless now
 */
int func_query()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Client > Query...\n");

	while(1)
	{
		memset (&reg_send, 0x00, sizeof(reg_send));

		/*set command type to register*/
		printf ("\n\nClient > Please input the 'word' you want to search or <00> to back\n\n");

		/*get the search word*/
		scanf("%s", reg_send.data.req_query.word);

		/*after one search, not quit, continue search next*/
		printf("Client > you input the word '%s'\n", reg_send.data.req_query.word);

		/*cheak whether '00' logout*/
		if (0 == strncmp(reg_send.data.req_query.word, "00", 2))
		{
			reg_send.hdr.cmd_type = REQ_Logout;
			while (send_to(sock_client, &reg_send) < 0);
			printf ("Client > user back\n");
			return 0;
		}
		reg_send.hdr.cmd_type = REQ_Query;

		/*send  query information to server*/
		if (send_to(sock_client, &reg_send) < 0)
		{
			printf ("Client > Send query information error\n");
			continue;
		}

		/*wait for back information*/
		if (recv_from(sock_client, &reg_recv) < 0)
		{
			printf ("Client > Receive query information error\n");
			continue;
		}

		printf ("Client > Receive query information success\n");

		switch (reg_recv.hdr.ret_code)
		{
			case SUCCESS:/*query word success, output the result*/
				{
					printf ("Client > search result :\n\t%s ", reg_recv.data.rpl_query.text);
					break;
				}
			case EQUERY_FOUND:
				{
					printf ("Client > Not found\n");
					break;
				}
			default:
				{
					printf ("Client > Bad response code\n");
					break;
				}
		}
	}
}



/*
 * func_history
 * list the query history of a certain username
 * no return value
 */
void func_history()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Client > History...\n");
	memset (&reg_send, 0x00, sizeof(reg_send));

	/*set command type to register*/
	reg_send.hdr.cmd_type = REQ_History;

	/*get username*/
	getchar();
	printf ("Input your username > ");
	if (NULL == fgets (reg_send.hdr.usrname, MAXLEN_USRNAME+1, stdin))
	{
		perror ("Get username error");
		return;
	}
	reg_send.hdr.usrname[strlen(reg_send.hdr.usrname)-1] = 0x00;


	/*send history information to server*/
	if (send_to(sock_client, &reg_send) < 0)
	{
		printf ("Send history information error\n");
		return;
	}

	/*wait for back information, because there may have many history informations,
	 * so use while to recv back information*/
	while (recv_from(sock_client, &reg_recv) == 0)/*receive back information success*/
	{
		if (RPL_HISTORY_END == reg_recv.hdr.ret_code)/*if history result reach end*/
		{
			printf ("Reach end of history");
			break;
		}
		else/*search results do not reach end, output it*/
		{
			printf ("%s\n", reg_recv.data.rpl_query.text);
			continue;
		}
	}
	return;
}


/*
 * func_quit()
 * no return value
 */
void func_quit()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;
	memset (&reg_send, 0x00, sizeof(reg_send));

	/*set command type to REQ_Quit*/
	reg_send.hdr.cmd_type = REQ_Quit;

	/*send history information to server*/
	if (send_to(sock_client, &reg_send) < 0)
	{
		printf ("Send quit information error\n");
		return;
	}


	/*receive logout information from server*/
	if (recv_from(sock_client, &reg_recv) < 0)
	{
		printf ("Client > Receive logout information error\n");
		return ;
	}
	printf ("Client > Receive logout information success\n");

	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:/*query word success, output the result*/
			{
				printf ("Client > Quit success\n");
				break;
			}
		case FAILED:
			{
				printf ("Client > Quit failed\n");
				return;
			}
		default:
			break;
	}
	while(close(sock_client) < 0)
	{
		perror("Client > close");
		sleep(1);
	}

	printf ("Client > client shutdown now\n ");
	return;
}
