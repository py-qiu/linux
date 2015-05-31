/*************************************************************************
  > File Name: client.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Fri 29 May 2015 11:07:01 AM CST
 ************************************************************************/

#include "include.h"

static	int sockfd;

int main()
{
	int ret_client;
	int input = 0;

	if ((sockfd = client_init()) > 0)
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
			func_query();
			goto step1;
			break;
		case 3:
			func_history();
			goto step1;
			break;
		case 4:
			func_quit();
			goto step1;
			break;
		default:
			break;
	}

	printf ("client exit now\n");
}



/*
 *register module
 *由键盘输入用户名和密码，通过套接字发送到服务器端确认
 *服务器端将确认结果返回，注册成功/用户名已存在/注册失败
 */
void func_register()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Register...\n");
	memset (&reg_send, 0x00, sizeof(reg_send));

	/*set command type to register*/
	reg_send.hdr.cmd_type = REQ_Register;

	/*get username*/
	getchar();
	printf ("Input your username > ");
	if (NULL == fgets (reg_send.hdr.usrname, MAXLEN_USRNAME+1, stdin))
	{
		perror ("Get username error");
		return;
	}
	reg_send.hdr.usrname[strlen(reg_send.hdr.usrname)-1] = 0x00;

	/*get password*/
	printf ("Input your password > \n");
	if (NULL == fgets(reg_send.data.req_register.passwd, MAXLEN_PASSWD+1, stdin))
	{
		perror ("Get password error");
		return;
	}
	reg_send.data.req_register.passwd[strlen(reg_send.data.req_register.passwd)-1] = 0x00;

	/*send register information to server*/
	if (send_to(sockfd, &reg_send) < 0)
	{
		printf ("Send register information error\n");
		return;
	}



	/*wait for back information*/
	if (recv_from(sockfd, &reg_recv) < 0)
	{
		printf ("Receive register information err\n");
		return;
	}

	printf ("Receive register information success\n");

	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:
			{
				printf ("Register success\n");
				break;
			}
		case USER_ALREADY_EXIST:
			{
				printf ("User already exists\n");
				break;
			}
		case EREG_INSERT_USER:
			{
				printf ("Insert user failed\n");
				break;
			}
		case EREG_CREAT_USERS:
			{
				printf ("Create table users failed\n");
				break;
			}
		case EREG_CREAT_HISTORY:
			{
				printf ("Create table history failed\n");
				break;
			}
		default:
			{
				printf ("bad response code : '%d'\n", reg_recv.hdr.ret_code);
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

	printf ("Login...\n");
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
	printf ("Input your password > \n");
	if (NULL == fgets(reg_send.data.req_register.passwd, MAXLEN_PASSWD+1, stdin))
	{
		perror ("Get password error");
		return -1;
	}
	reg_send.data.req_register.passwd[strlen(reg_send.data.req_register.passwd)-1] = 0x00;

	/*send login information to server*/
	if (send_to(sockfd, &reg_send) < 0)
	{
		printf ("Send login information error\n");
		return -1;
	}


	/*wait for back information*/
	if (recv_from(sockfd, &reg_recv) < 0)
	{
		printf ("Receive login information error\n");
		return -1;
	}

	printf ("Receive login information success\n");

	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:
			{
				printf ("Login success\n");
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
	return 0;
}


/*
 * function quit, 
 * logout
 */
int func_quit()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Logout ...\n");
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

	/*get password*/
	printf ("Input your password > \n");
	if (NULL == fgets(reg_send.data.req_register.passwd, MAXLEN_PASSWD+1, stdin))
	{
		perror ("Get password error");
		return -1;
	}
	reg_send.data.req_register.passwd[strlen(reg_send.data.req_register.passwd)-1] = 0x00;

	/*send logout information to server*/
	if (send_to(sockfd, &reg_send) < 0)
	{
		printf ("Send logout information error\n");
		return -1;
	}

	/*receive louout information from server*/
	if (recv_from(sockfd, &reg_recv) < 0)
	{
		printf ("Receive logout information error\n");
		return;
	}

	printf ("Receive logout information success\n");

	switch (reg_recv.hdr.ret_code)
	{
		case SUCCESS:
			{
				printf ("Louout success\n");
				break;
			}
		case ELOGOUT:
			{
				printf ("Logout failed\n");
				break;
			}
		case ELOGOUT_ALREADY:
			{
				printf ("Already logout\n");
				break;
			}
		default:
			{
				printf ("Bad response code\n");
				break;
			}
	}
	return;
}


/*
 * query the word
 * nornally, this function should not quit, 
 * unless user choose <00> to quit, or error occured
 * return value useless now
 */
int func_query()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("Query...\n");

	while(1)
	{
		memset (&reg_send, 0x00, sizeof(reg_send));

		/*set command type to register*/
		printf ("\n\nPlease input the 'word' you want to search or <00> to quit\n\n");

		scanf("%s", reg_send.data.req_query.word);

		/*cheak whether quit*/
		if (0 == strncmp(reg_send.data.req_query.word, "00", 2))
		{
			return;
		}

		/*not quit, continue*/
		printf("you input the word '%s'\n", reg_send.data.req_query.word);
		reg_send.hdr.cmd_type = REQ_Query;

		/*send  query information to server*/
		if (send_to(sockfd, &reg_send) < 0)
		{
			printf ("Send query information error\n");
			return;
		}

		/*wait for back information*/
		if (recv_from(sockfd, &reg_recv) < 0)
		{
			printf ("Receive query information error\n");
			return;
		}

		printf ("Receive query information success\n");

		switch (reg_recv.hdr.ret_code)
		{
			case SUCCESS:
				{
					printf ("detail :\n%s ", reg_recv.data.rpl_query.text);
					break;
				}
			case EQUERY_FOUND:
				{
					printf ("Not found\n");
					break;
				}
			default:
				{
					printf ("Bad response code\n");
					break;
				}
		}
	}
}



/*
 * func_history
 * list the query history of a certain user
 * no return value
 */
void func_history()
{
	xprotocol_t reg_send;
	xprotocol_t reg_recv;

	printf ("History...\n");
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

	/*get password*/
	printf ("Input your password > \n");
	if (NULL == fgets(reg_send.data.req_register.passwd, MAXLEN_PASSWD+1, stdin))
	{
		perror ("Get password error");
		return;
	}
	reg_send.data.req_register.passwd[strlen(reg_send.data.req_register.passwd)-1] = 0x00;

	/*send history information to server*/
	if (send_to(sockfd, &reg_send) < 0)
	{
		printf ("Send history information error\n");
		return;
	}


	/*wait for back information*/
	while (recv_from(sockfd, &reg_recv) == 0)/*receive back information success*/
	{
		if (RPL_HISTORY_END == reg_recv.hdr.ret_code)/*reach end*/
		{
			printf ("Reach end of history");
			return;
		}
		else/*do not reach end*/
		{
			printf ("%s\n", reg_recv.data.rpl_query.text);
			continue;
		}
	}
}
