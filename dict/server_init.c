/*************************************************************************
  > File Name: server_init.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Fri 29 May 2015 09:34:31 AM CST
 ************************************************************************/

#include "include.h"
#define SERVER_ADDR "192.168.1.54"
#define MAXLEN_SQL 256
#define MAX(a, b) (a)>(b)?(a):(b)


int whether_exist_callback(void *arg, int num, char **column_val, char **column_name);
int whether_table_exist(sqlite3 *db, const char *table_name);
int create_table(sqlite3 *db, char *tablename);
int whether_username_exist(sqlite3 *db, char *username);
int insert_username(char *username, char *passwd);
int database_open();
int file_open();
void sendback(int connfd, xprotocol_t client_back);
int log_status(sqlite3 *db, char *username);
int log_status_callback(void *arg, int num, char **column_val, char **column_name);
int check_passwd(sqlite3 *db, char *username, char *passwd);
int check_passwd_callback(void *arg, int num, char **column_val, char **column_name);
void do_query(FILE *fstream, char *str);
int do_logout(char *username);
int log_out_callback(void *arg, int num, char **column_val, char **column_name);
void do_history(int connfd, char *username);
int do_history_callback(void *arg, int num, char **column_val, char **column_name);

int listenfd;
int connfd;
sqlite3 *db = NULL;
FILE *fstream;
char uname[MAXLEN_USRNAME];

/*
 *initialize the server, set local address information
 */
int server_init()
{
	struct sockaddr_in server_addr;


	printf ("*****************************************\n\n");
	/*step1, create socket to listen*/
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror ("server > create socket failed !!");
		printf ("*****************************************\n\n");
		exit (-1);
	}
	printf ("server > create socket success\n\n");
	printf ("*****************************************\n\n");

	/*step2, bind the socket to local connection*/
	memset (&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_addr.s_addr		= inet_addr(SERVER_ADDR);
	server_addr.sin_port	=htons(8888);
	printf ("server > bind IP address and Port...\n");
	printf ("         socket: %d\n", listenfd);
	printf ("         IP_address: %s\n", SERVER_ADDR);
	printf ("         port: %d\n", 8888);

	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror ("server > bind IP address and Prot failed");
		printf ("*****************************************\n\n");
		exit(-1);
	}
	printf ("server > bind success\n\n");
	printf ("*****************************************\n\n");


	/*step3, put the socket to listen mode*/
	listen (listenfd, 5);
	printf ("server > listen the socket %d\n\n", listenfd);

	printf ("server > initialize server success \n\n");
	printf ("*****************************************\n\n");


	/*open database*/
	if (database_open() < 0)/*open database failed*/
	{
		printf ("server > open database error\n\n");
		printf ("*****************************************\n\n");
		//client_back.hdr.ret_code = EOPEN_DATABASE;
		return -1;
	}
	else/*open database success*/
	{
		printf ("server > open database success\n\n");
		printf ("*****************************************\n\n");
	}


	/*open file 'dict.txt'*/
	if (file_open() < 0)
	{
		printf ("server > open file 'dict.txt' error\n\n");
		printf ("*****************************************\n\n");
		return -1;
	}
	else
	{
		printf ("server > open file 'dict.txt' success\n\n");
		printf ("*****************************************\n\n");
	}

	return 0;
}




/*
 *run the server, and monitor socket
 */
int server_accept()
{
	struct sockaddr_in client_addr;
	socklen_t cliaddr_len;

	cliaddr_len = sizeof(client_addr);

	/*accept connection*/
	printf ("server > accept connection begin ...\n\n");
	if ((connfd = accept (listenfd, (struct sockaddr *)&client_addr, &cliaddr_len)) < 0)
	{
		perror ("server > accept connection error");
		printf ("*****************************************\n\n");
		exit (-1);
	}

	printf ("server > accept connection from %s   port %d\n\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	printf ("*****************************************\n\n");

	printf ("server > start service...\n\n");

	return 0;
}




/*
 * server loop for one connection a time
 * client error :-1
 * client exit  : 0
 */
int server_running()
{
	/*receive message from client*/
	xprotocol_t client_msg;
	xprotocol_t client_back;
	int logout_status = 0;

	while (0 == recv_from(connfd, &client_msg))/*while receive message from client success*/
	{
		printf ("server > receive message from client success\n\n");
		printf ("*****************************************\n\n");
		client_back = client_msg;

		switch (client_msg.hdr.cmd_type)
		{
			case REQ_Register:
				{
					printf ("server > client is registering\n\n");

					if (1 == whether_table_exist(db, "users"))/*table users exists*/
					{
						printf ("    server > table 'users' exist\n\n");

						if (1 == whether_username_exist(db, client_msg.hdr.usrname))/*username already exist*/
						{
							printf ("    server > Username '%s' already exist\n\n", client_msg.hdr.usrname);
							printf ("*****************************************\n\n");
							client_back.hdr.ret_code = USER_ALREADY_EXIST;
							sendback(connfd, client_back);
						}
						else/*username does not exist*/
						{
							printf ("    server > Username '%s' does not exist\n\n", client_msg.hdr.usrname);
							if (insert_username(client_msg.hdr.usrname, client_msg.data.req_register.passwd) == 0)
							{
								printf ("    server > Insert username and passwd success\n\n");
								printf ("*****************************************\n\n");
								client_back.hdr.ret_code = SUCCESS;
								sendback(connfd, client_back);
							}
							else
							{
								printf ("    server > Insert username and passwd failed\n\n");
								printf ("*****************************************\n\n");
								client_back.hdr.ret_code = EREG_INSERT_USER;
								sendback(connfd, client_back);
							}
						}
					}
					else/*table users does not exist*/
					{
						printf ("    server > table 'user' does not exist\n\n");

						if (create_table(db, "users") < 0)/*create table users failed*/
						{
							printf ("  server > create table 'users' failed\n\n");
							printf ("*****************************************\n\n");
							client_back.hdr.ret_code = EREG_CREAT_USERS;
							sendback(connfd, client_back);
						}
						else/*create table 'users' success*/
						{
							printf ("  server > create table 'users' success\n\n");

							if (create_table(db, "history") < 0)/*create table history failed*/
							{
								printf ("  server > create table 'history' failed\n\n");
								printf ("*****************************************\n\n");
								client_back.hdr.ret_code = EREG_CREAT_HISTORY;
								sendback(connfd, client_back);
							}
							else/*create table history success*/
							{
								printf ("  server > create table 'history' success\n\n");
								printf ("server > Inserting username '%s' and passwd to table to users\n", client_msg.hdr.usrname);

								if (insert_username(client_msg.hdr.usrname, client_msg.data.req_register.passwd) == 0)/*insert username success*/
								{
									printf ("  server > Insert username and passwd success\n\n");
									printf ("*****************************************\n\n");
									client_back.hdr.ret_code = SUCCESS;
									sendback(connfd, client_back);
								}
								else/*insert username failed*/
								{
									printf ("  server > Insert username and passwd failed\n\n");
									printf ("*****************************************\n\n");
									client_back.hdr.ret_code = EREG_INSERT_USER;
									sendback(connfd, client_back);
								}
							}
						}
					}

					break;
				}
			case REQ_Login:
				{
					strcpy(uname, client_msg.hdr.usrname);
					printf ("****************************************\n");
					printf ("server > client login ...\n\n");

					if (1 == whether_table_exist(db, "users"))/*table 'users exist'*/
					{
						if (1 == whether_username_exist(db, client_msg.hdr.usrname))/*username exist in table users*/
						{
							if (1 == log_status(db, client_msg.hdr.usrname))/*username already login*/
							{
								printf ("    server > '%s' already login\n\n", client_msg.hdr.usrname);
								client_back.hdr.ret_code = ELOGIN_ALREADY_LOGIN;
								sendback(connfd, client_back);
							}
							else/*username not yet login, check passwd*/
							{
								char sql[MAXLEN_SQL];
								printf ("      server > '%s' not yet login\n\n", client_msg.hdr.usrname);/*check password*/

								if (1 == check_passwd(db, client_msg.hdr.usrname, client_msg.data.req_register.passwd))/*password right, change state from 'N' to 'Y'*/
								{
									printf ("      server > password right\n\n");

									snprintf (sql, MAXLEN_SQL, "update users set state='Y' where username='%s'", client_msg.hdr.usrname);
									sqlite3_exec(db, sql, NULL, NULL, NULL);

									printf ("    server > '%s' login success\n\n", client_msg.hdr.usrname);
									client_back.hdr.ret_code = SUCCESS;
									sendback(connfd, client_back);
								}
								else
								{
									printf ("      server > password wrong\n\n");
									client_back.hdr.ret_code = ELOGIN_PASSWD;
									sendback(connfd, client_back);
								}


							}
						}
						else/*username does not exist in table 'users'*/
						{
							printf ("    server > login failed : '%s' does not exist in table 'users'\n\n", client_msg.hdr.usrname);

							client_back.hdr.ret_code = ELOGIN_USERNAME_EXIST;
							sendback(connfd, client_back);
						}

					}
					else/*table 'users' does not exist, login failed*/
					{
						printf ("    server > login failed : table 'users' does not exist\n\n");

						client_back.hdr.ret_code = ELOGIN_USERS_EXIST;
						sendback(connfd, client_back);
					}

					break;
				}
			case REQ_Query:
				{
					printf ("****************************************\n");
					printf ("server > client query...\n\n");
					printf ("server > The query word is '%s'\n", client_msg.data.req_query.word);
					printf ("<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n");
					do_query(fstream, client_msg.data.req_query.word);
					break;
				}
			case REQ_Logout:
				{
					printf ("****************************************\n");
					printf ("server > client logout...\n");
					printf ("<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n");

					if (1 ==(logout_status=do_logout(client_msg.hdr.usrname)))/*logout success*/
					{
						printf ("    server > Logout success\n\n");
						client_back.hdr.ret_code = SUCCESS;
						sendback(connfd, client_back);
						break;
					}
					else if (0 == logout_status)/*logout already*/
					{
						printf ("    server > Already logout\n\n");
						client_back.hdr.ret_code = ELOGOUT_ALREADY;
						sendback(connfd, client_back);
						break;
					}
					else
					{
						printf ("    server > Logout error\n\n");
						client_back.hdr.ret_code = ELOGOUT;
						sendback(connfd, client_back);
						break;
					}
				}
			case REQ_History:
				{
					printf ("****************************************\n");
					printf ("server > client is searching history\n\n");
					printf ("<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n");
					do_history(connfd, client_msg.hdr.usrname);
					break;
				}
			default:
				{
					printf ("server > Bad requst code\n\n");
					printf ("Client quit...\n");
					sleep(4);
					return 0;
				}
		}
		memset(&client_msg, 0x00, sizeof(client_msg));
		memset(&client_back, 0x00, sizeof(client_back));
		rewind(fstream);
	}

	/*receive message from client error*/
	printf ("server > receive message from client error\n");
	return -1;
}


/*
 * send information back to client
 * no return value
 */
void sendback(int connfd, xprotocol_t client_back)
{
	if (send_to(connfd, &client_back) < 0)
	{
		printf ("server > Send back information error\n");
		return;
	}
	else
	{
		printf ("server > Send back information success\n");
		return;
	}
}


/*
 * check login status
 * if user already log in, their status will be 'Y', not 'N'
 * already login: 1
 * not yet login: 0
 * error        :-1
 */
int log_status(sqlite3 *db, char *username)
{
	printf ("server > check '%s' login status\n", username);

	char sql[MAXLEN_SQL];
	int status = 0;

	if (snprintf (sql, MAXLEN_SQL, "select * from users where username='%s'", username) < 0)
	{
		printf ("snprintf sql error\n");
		return -1;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, log_status_callback, &status, NULL))
	{
		printf("    server > check '%s' login status failed\n", username);
		return -1;
	}
	printf ("    server > check '%s' login status success\n", username);

	return status;
}


/*
 * callback function 
 * used by log_status()
 * not return value
 */
int log_status_callback(void *arg, int num, char **column_val, char **column_name)
{
	char sql[MAXLEN_SQL];

	printf ("  server > login status callback was called once\n");

	if (strncmp("N", column_val[2], 1) != 0)	/*status is not 'N', login already*/
	{
		*((int *)arg) = 1;
	}
	return 0;
}

/*
 * check passwd of user
 * password right:0
 * passwd wrong  :-1
 */
struct argu
{
	int status;
	char passwd[MAXLEN_PASSWD];
};


/*
 * check password right or wrong
 * right : 1
 * wrong : 0
 */
int check_passwd(sqlite3 *db, char *username, char *passwd)
{
	printf ("server > check '%s' password\n", username);

	char sql[MAXLEN_SQL];
	struct argu argument;

	argument.status = 0;
	strcpy(argument.passwd, passwd);

	if (snprintf (sql, MAXLEN_SQL, "select passwd from users where username='%s'", username) < 0)
	{
		printf ("snprintf sql error\n");
		return -1;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, check_passwd_callback, &argument, NULL))
	{
		printf("    server > check passwd failed\n\n");
		return -1;
	}
	printf ("    server > check passwd success\n\n");

	return argument.status;
}


/*
 * callback function 
 * used by check_passwd()
 * not return value
 */
int check_passwd_callback(void *arg, int num, char **column_val, char **column_name)
{
	printf ("  server > check passwd callback was called once\n");

	if (strncmp((*(struct argu *)arg).passwd, column_val[0], MAX((strlen((*(struct argu *)arg).passwd)), (strlen(column_val[0])))) == 0)/*passwd right*/
	{
		((struct argu *)arg)->status = 1;
	}

	return 0;
}

/*
 *
 */



/*
 *callback function, 
 *used by whether_table_exist(), and whether_username_exist()
 *no return value
 */
int whether_exist_callback(void *arg, int num, char **column_val, char **column_name)
{
	printf ("  server > whether_exist_callback was called once\n");
	*((int *)arg) = 1;
	return 0;
}

/*
 *check whether or not talbe exist
 *exist     : 1
 *not exist : 0
 *call whether_exist_callback
 */
int whether_table_exist(sqlite3 *db, const char *table_name)
{
	printf ("server > check whether table '%s' exist\n", table_name);

	char sql[MAXLEN_SQL];
	int exist = 0;

	if (snprintf(sql, MAXLEN_SQL, "select name from sqlite_master where type='table' and name='%s'", table_name) < 0)
	{
		printf ("snprintf sql error\n");
		return 0;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, whether_exist_callback, &exist, NULL))
	{
		printf("  server > check whether table exist in datebase failed\n");
		return 0;
	}
	printf ("  server > check whether table exist in datebase success\n");

	return exist;
}


/*
 *create a new table
 *success : 0
 *failed  : -1
 *no call
 */
int create_table(sqlite3 *db, char *tablename)
{
	printf ("server > create new table '%s'\n", tablename);

	char sql[MAXLEN_SQL];

	if ("users" == tablename)
	{
		if (snprintf(sql, MAXLEN_SQL, "create table '%s'(username text, passwd text, state text)", tablename) < 0)
		{
			printf ("snprintf SQL error\n");
			return -1;
		}
	}
	else
	{
		if (snprintf(sql, MAXLEN_SQL, "create table '%s'(username text, word text, time text)", tablename) < 0)
		{
			printf ("snprintf SQL error\n");
			return -1;
		}

	}


	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
	{
		return -1;
	}

	return 0;
}



/*
 *check whether or not username exist in user table
 *exist     :1
 *not exist :0
 *error     :-1
 *call whether_table_exist(), 
 */
int whether_username_exist(sqlite3 *db, char *username)
{
	printf ("server > check whether user '%s' exist\n", username);

	int exist = 0;

	char sql[MAXLEN_SQL];

	if (snprintf (sql, MAXLEN_SQL, "select * from users where username='%s'", username) < 0)
	{
		printf ("snprintf SQL error\n");
		return -1;
	}
	else
	{
		if (SQLITE_OK != sqlite3_exec(db, sql, whether_exist_callback, &exist, NULL))
		{
			printf ("    server > check whether user '%s' exist in table failed\n\n", username);
			return exist;
		}
		else
		{
			printf ("    server > check whether user '%s' exist in table success\n\n", username);
			return exist;
		}
	}
	return exist;
}



/*
 *insert username to users table
 *success :0
 *failed  :-1
 *call whether_table_exist(), create_table()
 */
int insert_username(char *username, char *passwd)
{
	char sql[MAXLEN_SQL];

	if (snprintf(sql, MAXLEN_SQL, "insert into users values('%s', '%s', '%s')", username, passwd, "N") < 0)
	{
		printf ("snprintf SQL error\n");
		return -1;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
	{
		return -1;
	}

	return 0;
}

/*
 *initialize database
 *success : 0
 *error   : -1
 */
int database_open()
{
	int result;
	result = sqlite3_open("database.db", &db);

	if (result != SQLITE_OK)
	{
		if (NULL != db)
		{
			printf ("server > open database failed : %s\n", sqlite3_errmsg(db));
			if (sqlite3_close(db) != SQLITE_OK)
			{
				printf ("server > close database error\n");
			}
			return -1; 
		}
		else
		{
			printf ("server > failed to allocate memory for database\n");
			if (sqlite3_close(db) != SQLITE_OK)
			{
				printf ("server > close database error\n");
			}
			return -1; 
		}
	}

	return 0;
}


/*
 * open file 'dict.txt', RDONLY
 * success : 0
 * error   : -1
 */
int file_open()
{
	fstream = fopen("./dict.txt", "r");
	if (fstream == NULL)/*open file error*/
	{
		return -1;
	}
	return 0;
}


/*
 * query a word
 * no return value
 */
void do_query(FILE *fstream, char *str)
{
	char buff[MAXLEN_TEXT];
	char *ret_buf; 
	char buf_word[MAXLEN_WORD];
	int i = 0;
	xprotocol_t client_back;
	while (1)
	{
		i=0;
		memset(&buff, 0x00, sizeof(buff));
		printf ("+++++++++++++++++++++++++++++++++++++++++\n");
		printf ("  server > read from stream\n");

		if (NULL != (ret_buf=fgets(buff, MAXLEN_TEXT, fstream)))/*while can read one line data*/
		{
			printf ("    server > the read data is : %s", buff);

			while (buff[i] != ' ')/*store search word*/
			{
				buf_word[i] = buff[i];
				i++;
			}
			buf_word[i]='\0';
			printf ("target is : %s\n", str);
			printf ("found is  : %s\n", buf_word);

			if (0 == strncmp(buff, str, MAX(strlen(str), strlen(buf_word))))/*we get a match*/
			{
				printf ("      server > get a positive match\n\n");
				client_back.hdr.ret_code = SUCCESS;
				strcpy(client_back.data.rpl_query.text, buff);
				sendback(connfd, client_back);

				printf ("  server > Insert record into table 'history'\n");

				if (0 == insert_record(db, str))/*Insert the success search result into table 'history' success*/
				{
					printf ("    server > Insert record into table 'history' success\n\n");
					return;
				}
				else/*insert search result into table 'history' failed*/
				{
					printf ("    server > Insert record into table 'history' failed\n\n");
					return;	
				}
			}
			else/*we do not have a match*/
			{
				printf ("      server > do not have a match\n\n");
				continue;
			}
		}
		else /*can not read data, EOF or error*/
		{
			printf ("    server > EOF or error\n");
			perror ("error");
			printf ("No search result\n");

			client_back.hdr.ret_code = EQUERY_FOUND;
			sendback(connfd, client_back);
			return;
		}
	}

	return;
}

/*
 * insert search record into table 'history'
 * success : 0
 * failed  :-1
 */

int insert_record(sqlite3 *db, char *word)
{
	char sql[MAXLEN_SQL];
	time_t *tm;

	if (snprintf(sql, MAXLEN_SQL, "insert into history values('%s', '%s', '%s')", uname, word, asctime(localtime(tm))) < 0)
	{
		printf ("snprintf SQL error\n");
		return -1;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
	{
		return -1;
	}
	return 0;
}


/*
 * function do_logout
 * success : 1
 * already : 0
 * error   :-1
 */
int do_logout(char *username)
{
	printf ("server > '%s' logout \n", username);

	char sql[MAXLEN_SQL];
	int status = 0;

	if (snprintf (sql, MAXLEN_SQL, "select * from users where username='%s'", username) < 0)
	{
		printf ("snprintf sql error\n");
		return -1;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, log_out_callback, &status, NULL))
	{
		printf("  server > check '%s' logout status failed\n", username);
		return -1;
	}
	printf ("  server > check '%s' logout status success\n", username);

	return status;
}

/*
 * log_out_callback
 * return value useless
 */
int log_out_callback(void *arg, int num, char **column_val, char **column_name)
{
	char sql[MAXLEN_SQL];
	printf ("  server > login out callback was called once\n");

	if (0 == strncmp(column_val[2], "Y", 1))//not yet logout
	{
		snprintf (sql, MAXLEN_SQL, "update users set state='N' where username='%s'", column_val[0]);
		SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL);
		*((int *)arg) = 1;
	}
	//else user already logout

	return 0;
}


/*
 * function do_history
 * check user search history
 * no return value
 */
void do_history(int connfd, char *username)
{
	printf ("server > '%s' history\n", username);

	char sql[MAXLEN_SQL];
	xprotocol_t client_back;
	memset(&client_back, 0x00, sizeof(client_back));

	if (snprintf (sql, MAXLEN_SQL, "select * from history where username='%s'", username) < 0)
	{
		printf ("snprintf sql error\n");
		return ;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, do_history_callback, &connfd, NULL))
	{
		printf("  server > check '%s' search history failed\n", username);
		return ;
	}
	printf ("  server > check '%s' search history success\n", username);

	client_back.hdr.ret_code = RPL_HISTORY_END;
	sendback(connfd, client_back);
}

/*
 * do_history_callback
 * callback function, used by do history
 */
int do_history_callback(void *arg, int num, char **column_val, char **column_name)
{
	xprotocol_t client_back;
	memset(&client_back, 0x00, sizeof(client_back));

	printf ("  server > do_history callback was called once, get a match\n\n");
	client_back.hdr.ret_code = SUCCESS;
	strcpy(client_back.data.rpl_query.text, column_val[0]);
	strcat(client_back.data.rpl_query.text, "	");
	strcat(client_back.data.rpl_query.text, column_val[1]);
	strcat(client_back.data.rpl_query.text, "	");
	strcat(client_back.data.rpl_query.text, column_val[2]);
	sendback(*(int *)arg, client_back);
	return 0;
}
