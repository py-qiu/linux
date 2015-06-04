/*************************************************************************
  > File Name: server_ops.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Thu 04 Jun 2015 10:34:46 AM CST
 ************************************************************************/

#include"include.h"
extern sqlite3 *db;
/*
 * name:reg_func
 * describation: check whether table 'users' exist,
 *				 if table 'users' exist, then check whether 'username' already exist,
 *					if 'username' already exist, then return code 'USER_ALREADY_EXIST', else insert 'username' into table 'users'
 *	if table 'users' does not exist, then create table 'users', and create table 'history', and insert 'username' into table 'users'
 *
 * return value:no
 */
void reg_func()
{
	printf ("****************************************\n\n");
	printf ("server > client registering ...\n\n");
	xprotocol_t client_back;

	if (1 == whether_table_exist(db, "users"))/*table 'users' exists*/
	{
		printf ("    server > table 'users' exist\n\n");

		if (1 == whether_username_exist(db, client_msg.hdr.usrname))/*username already exist*/
		{
			printf ("    server > Username '%s' already exist\n\n", client_msg.hdr.usrname);
			printf ("*****************************************\n\n");
			client_back.hdr.ret_code = USER_ALREADY_EXIST;
			send_to(connfd_server, &client_back);
			return;
		}
		else/*username does not exist*/
		{
			printf ("    server > Username '%s' does not exist\n\n", client_msg.hdr.usrname);
			if (insert_username(client_msg.hdr.usrname, client_msg.data.req_register.passwd) == 0)/*insert username success*/
			{
				printf ("    server > Insert username and passwd success\n\n");
				printf ("*****************************************\n\n");
				client_back.hdr.ret_code = SUCCESS;
				send_to(connfd_server, &client_back);
				return;
			}
			else /*insert username failed*/
			{
				printf ("    server > Insert username and passwd failed\n\n");
				printf ("*****************************************\n\n");
				client_back.hdr.ret_code = EREG_INSERT_USER;
				send_to(connfd_server, &client_back);
				return;
			}
		}
	}
	else/*table 'users' does not exist, then create*/
	{
		printf ("    server > table 'user' does not exist\n\n");
		if (create_table(db, "users") < 0)/*create table 'users' failed*/
		{
			printf ("  server > create table 'users' failed\n\n");
			printf ("*****************************************\n\n");
			client_back.hdr.ret_code = EREG_CREAT_USERS;
			send_to(connfd_server, &client_back);
			return;
		}
		else/*create table 'users' success, then create table 'history'*/
		{
			printf ("  server > create table 'users' success\n\n");
			if (create_table(db, "history") < 0)/*create table 'history' failed*/
			{
				printf ("  server > create table 'history' failed\n\n");
				printf ("*****************************************\n\n");
				client_back.hdr.ret_code = EREG_CREAT_HISTORY;
				send_to(connfd_server, &client_back);
				return;
			}
			else/*create table history success*/
			{
				printf ("  server > create table 'history' success\n\n");
				printf ("server > Inserting username '%s' and passwd to table to users\n", client_msg.hdr.usrname);

				if (insert_username(client_msg.hdr.usrname, client_msg.data.req_register.passwd) == 0)/*insert username success*/
				{
					printf ("  server > Insert username and passwd to table 'users' success\n\n");
					printf ("*****************************************\n\n");
					client_back.hdr.ret_code = SUCCESS;
					send_to(connfd_server, &client_back);
					return;
				}
				else/*insert username failed*/
				{
					printf ("  server > Insert username and passwd to table 'users' failed\n\n");
					printf ("*****************************************\n\n");
					client_back.hdr.ret_code = EREG_INSERT_USER;
					send_to(connfd_server, &client_back);
					return;
				}
			}
		}//end of if create table 'users'
	}//end of if whether table 'users' exist
}//end if function



/*
 * name : login_func
 * describe : first check whether table 'users' exist, if not, then set return code 'ELOGIN_USERS_EXIST',
 *				if table 'users' exist, then check whether 'username' exist, if not, set return code 'ELOGIN_USERNAME_EXIST',
 *					if both table and username exist, then check 'username' log state, if state shows already logged then set return code 'ELOGIN_ALREADY_LOGIN',
 *						if result shows 'username' not logged, then verify password, and change log state into login
 * return value :
 */
void login_func()
{
	xprotocol_t client_back;
	strcpy(uname, client_msg.hdr.usrname);
	printf ("****************************************\n\n");
	printf ("server > client login ...\n\n");

	if (1 == whether_table_exist(db, "users"))/*table 'users exist'*/
	{
		if (1 == whether_username_exist(db, client_msg.hdr.usrname))/*username exist in table users*/
		{
			if (1 == log_status(db, client_msg.hdr.usrname))/*username already login*/
			{
				printf ("    server > '%s' already login\n\n", client_msg.hdr.usrname);
				client_back.hdr.ret_code = ELOGIN_ALREADY_LOGIN;
				send_to(connfd_server, &client_back);
				return;
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
					send_to(connfd_server, &client_back);
					return;
				}
				else/*password wrong*/
				{
					printf ("      server > password wrong\n\n");
					client_back.hdr.ret_code = ELOGIN_PASSWD;
					send_to(connfd_server, &client_back);
					return;
				}
			}
		}
		else/*username does not exist in table 'users'*/
		{
			printf ("    server > login failed : '%s' does not exist in table 'users'\n\n", client_msg.hdr.usrname);

			client_back.hdr.ret_code = ELOGIN_USERNAME_EXIST;
			send_to(connfd_server, &client_back);
			return;
		}

	}
	else/*table 'users' does not exist, login failed*/
	{
		printf ("    server > login failed : table 'users' does not exist\n\n");

		client_back.hdr.ret_code = ELOGIN_USERS_EXIST;
		send_to(connfd_server, &client_back);
		return;
	}//end of if, whether_table_exist
}//end of func


/*
 * name : query_func
 * describe : query function can only be used after login function
 *				read line by line from 'fstream', and get the word before space,
 *				then compare the word with input, if it is a match, send the line back to client,
 *					and insert the word to table 'history', and then return,
 *				otherwise, read next line until get a match or last line
 *
 * return value : no 
 *
 */
void query_func(FILE *fstream, char *str)
{
	printf ("****************************************\n");
	printf ("server > client query...\n\n");
	printf ("server > The query word is '%s'\n", client_msg.data.req_query.word);
	printf ("<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n");

	char buff[MAXLEN_TEXT];
	char *ret_buf; 
	char buf_word[MAXLEN_WORD];
	int i = 0;
	xprotocol_t client_back;

	printf ("  server > read from stream\n");
	while (1)
	{
		i=0;
		memset(&buff, 0x00, sizeof(buff));
		printf ("++++++++++++++++++++++++++++++++++++++++++++++\n");

		if (NULL != (ret_buf=fgets(buff, MAXLEN_TEXT, fstream)))/*while can read one line data*/
		{
			printf ("    server > the read data is : %s", buff);

			while (buff[i] != ' ')/*get first word*/
			{
				buf_word[i] = buff[i];
				i++;
			}
			buf_word[i]='\0';

			printf ("target is : %s\n", str);
			printf ("found is  : %s\n", buf_word);

			/*compare user input word, and found word*/
			if (0 == strncmp(buff, str, MAX(strlen(str), strlen(buf_word))))/*it's a match*/
			{
				printf ("      server > get a positive match\n\n");
				client_back.hdr.ret_code = SUCCESS;
				strcpy(client_back.data.rpl_query.text, buff);
				send_to(connfd_server, &client_back);

				printf ("  server > Insert record into table 'history'\n");
				if (0 == insert_record(db, str))/*Insert search word into table 'history' success*/
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
			send_to(connfd_server, &client_back);
			return;
		}
	}
}



/*
 * insert search record into table 'history'
 * success : 0
 * failed  :-1
 */

int insert_record(sqlite3 *db, char *word)
{
	char sql[MAXLEN_SQL];
	time_t tm;
	time(&tm);

	if (snprintf(sql, MAXLEN_SQL, "insert into history values('%s', '%s', '%s')", uname, word, ctime(&tm)) < 0)
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
 * history_func
 * search in table 'history', check user search history
 * no return value
 */
void history_func(int connfd, char *username)
{
	printf ("****************************************\n");
	printf ("server > client is searching history\n\n");
	printf ("<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n");
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
	send_to(connfd_server, &client_back);
}

/*
 * do_history_callback
 * callback function, used by do history, if this function is called, it means a match search result is found
 */
int do_history_callback(void *arg, int num, char **column_val, char **column_name)
{
	xprotocol_t client_back;
	memset(&client_back, 0x00, sizeof(client_back));

	printf ("  server > do_history callback was called once, get a match\n\n");
	client_back.hdr.ret_code = SUCCESS; /*set return code 'SUCCESS'*/

	/*send back all information in table 'history' to client*/
	strcpy(client_back.data.rpl_query.text, column_val[0]);
	strcat(client_back.data.rpl_query.text, "	");
	strcat(client_back.data.rpl_query.text, column_val[1]);
	strcat(client_back.data.rpl_query.text, "	");
	strcat(client_back.data.rpl_query.text, column_val[2]);
	//send_to(*(int *)arg, client_back);
	send_to(connfd_server, &client_back);
	return 0;
}



/*
 * quit_func
 * client quit, force all users logout, change all state into 'N'
 * no return value useful
 */
void quit_func()
{
	xprotocol_t client_back;
	memset(&client_back, 0x00, sizeof(client_back));
	printf ("server > Client quit...\n\n");
	char sql[MAXLEN_SQL];

	if (snprintf (sql, MAXLEN_SQL, "update users set state='N'") < 0)
	{
		printf ("snprintf sql error\n");
		return ;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
	{
		printf("  server > client quit failed\n");
		client_back.hdr.ret_code = FAILED; /*set return code 'SUCCESS'*/
		send_to(connfd_server, &client_back);
		return ;
	}
	printf ("    server > client quit success\n");
	client_back.hdr.ret_code = SUCCESS; /*set return code 'SUCCESS'*/
	send_to(connfd_server, &client_back);
	return;
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
 *check whether or not username exist in user table
 *exist     :1
 *not exist :0
 *error     :-1
 *call whether_table_exist(), 
 */
int whether_username_exist(sqlite3 *db, const char *username)
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
 *callback function, 
 *used by whether_table_exist(), and whether_username_exist()
 *no return value useful
 */
int whether_exist_callback(void *arg, int num, char **column_val, char **column_name)
{
	printf ("  server > whether_exist_callback was called once\n");
	*((int *)arg) = 1;
	return 0;
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

	if (0 == strcmp("users", tablename))
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

	if (snprintf (sql, MAXLEN_SQL, "select * from users where username='%s'", uname) < 0)
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
	printf ("  server > login status callback was called once\n");

	if (strncmp("N", column_val[2], 1) != 0)	/*status is not 'N', login already*/
	{
		*((int *)arg) = 1;
	}
	return 0;
}


/*
 * check password right or wrong
 * struct argu, used for check_passwd and check_passwd_callback
 * right : 1
 * wrong : 0
 */
struct argu
{
	int status;
	char passwd[MAXLEN_PASSWD];
};

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
 * logout_func
 * failed :-1
 * success: 0
 */
int logout_func(char *username)
{
	char sql[MAXLEN_SQL];

	printf ("****************************************\n");
	printf ("server > user '%s' logout...\n", username);
	printf ("<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n");

	if (0 == log_status(db, username))/*already log out*/
	{
		printf ("      server > Already logout\n\n");
		client_back.hdr.ret_code = ELOGOUT_ALREADY;
		send_to(connfd_server, &client_back);
		return 0;
	}
	else/*username still login*/
	{
		snprintf (sql, MAXLEN_SQL, "update users set state='N' where username='%s'", username);

		if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
		{
			printf("      server > '%s' logout  failed\n", username);
			client_back.hdr.ret_code = ELOGOUT;
			send_to(connfd_server, &client_back);
			return -1;
		}
		printf ("      server > Logout success\n\n");
		client_back.hdr.ret_code = SUCCESS;
		send_to(connfd_server, &client_back);
		return 0;
	}

}


