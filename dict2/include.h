/*************************************************************************
    > File Name: include.h
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Fri 29 May 2015 08:56:25 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<inttypes.h> /*for uint16_t*/
#include<sys/types.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sqlite3.h>
#include<time.h>
#include<error.h>

#define MAXLEN_SQL 256
#define MAXLEN_USRNAME 15

#define MAX(a, b) (a)>(b)?(a):(b)

typedef struct xp_hdr /*协议报头部，存放一些公共的长度固定的字段域*/
{
	char      usrname[MAXLEN_USRNAME + 1]; /*用户名*/
	uint16_t  cmd_type;                /*命令类型，存放请求类型和应答类型*/
	uint16_t  ret_code;				   /*返回码，仅用于服务器端发给客户机的应答*/
}xp_hdr_t;


#define MAXLEN_PASSWD 15	 /*REQ Register & REQ Login*/
typedef struct xp_req_register
{
	char passwd[MAXLEN_PASSWD + 1];
}xp_req_register_t, xp_req_login_t;


#define MAXLEN_WORD 31		/*REQ Query*/
typedef struct xp_req_query
{
	char word[MAXLEN_WORD + 1];
}xp_req_query_t;


#define MAXLEN_TEXT 300		/*RPL Query*/
typedef struct xp_rpl_query
{
	char text[MAXLEN_TEXT];
}xp_rpl_query_t;


#define MAXLEN_TIME 19		/*RPL History*/
typedef struct xp_rpl_history
{
	char word[MAXLEN_WORD + 1];
	char time[MAXLEN_TIME + 1];
}xp_rpl_history_t;


typedef union xp_data		/*协议报数据载荷部分，存放客户端的request或服务器端的reply*/
{
	xp_req_register_t req_register;
	xp_req_login_t    req_login;
	xp_req_query_t    req_query;

	xp_rpl_query_t	  rpl_query;
	xp_rpl_history_t  rpl_history;
}xp_data_t;


typedef struct xprotocol		/*协议报文格式*/
{
	xp_hdr_t   hdr;  /*协议报头部，存放一些公共的长度固定的字段域*/
	xp_data_t  data; /*协议报数据载荷部分，存放客户端的request或服务器端的reply*/
}xprotocol_t;



/*协议报头部，命令类型定义*/
//客户端部分
#define REQ_Register		0x0001
#define REQ_Login			0x0002 
#define REQ_Logout			0x0003
#define REQ_Query			0x0004
#define REQ_History			0x0005
#define REQ_Quit			0x0006

#define FAILED (uint16_t)-1
#define SUCCESS (uint16_t)0

/*register error*/
#define USER_ALREADY_EXIST (uint16_t)10
#define EREG_INSERT_USER (uint16_t)11
#define EREG_CREAT_USERS (uint16_t)12
#define EREG_CREAT_HISTORY (uint16_t)13


/*login error*/
#define ELOGIN_USERS_EXIST (uint16_t)20
#define ELOGIN_USERNAME_EXIST (uint16_t)21
#define ELOGIN_ALREADY_LOGIN (uint16_t)22
#define ELOGIN_PASSWD (uint16_t)23


/*query error*/
#define EQUERY_FOUND (uint16_t)30

/*louout error*/
#define ELOGOUT (uint16_t)40
#define ELOGOUT_ALREADY (uint16_t)41

/*history*/
#define RPL_HISTORY_END (uint16_t)50




/**********public.c**********/
int send_to(int dest_fd, xprotocol_t *packet);
int recv_from (int src_fd, xprotocol_t *packet);
/*****public.c*****/




/**********server_init.c**********/
int server_init();
int server_accept();
int server_running();
int database_open();
int file_open();
/*****server_init.c*****/


/**********server_ops.c**********/
void reg_func();
void login_func();
int logout_func(char *username);
void query_func(FILE *fstream, char *str);
int insert_record(sqlite3 *db, char *word);
void history_func(int connfd, char *username);
int do_history_callback(void *arg, int num, char **column_val, char **column_name);

void quit_func();

int whether_table_exist(sqlite3 *db, const char *table_name);
int whether_username_exist(sqlite3 *db, const char *username);
int whether_exist_callback(void *arg, int num, char **column_val, char **column_name);

int create_table(sqlite3 *db, char *tablename);
int insert_username(char *username, char *passwd);

int log_status(sqlite3 *db, char *username);
int log_status_callback(void *arg, int num, char **column_val, char **column_name);

int check_passwd(sqlite3 *db, char *username, char *passwd);
int check_passwd_callback(void *arg, int num, char **column_val, char **column_name);

/*****server_ops.c*****/




/**********client_init.c**********/
int client_init();
/*****client_init.c*****/


/**********client_ops.c**********/
void func_register();
int func_login();
int func_logout();
int func_query();
void func_history();
void func_quit();
/*****client_ops.c*****/



#ifndef _MYINCLUDE_
#define _MYINCLUDE_
FILE *fstream;  /*opened stream, opened by file_open()*/

char uname[MAXLEN_USRNAME];/*username, global*/
int sock_client;/*sockfd of client*/
int listenfd_server;/*listenfd of server, created by socket()*/
int connfd_server;  /*connfd of server, created by accept()*/

xprotocol_t client_msg;// client_msg在服务器中代表从客户端收到的信息
xprotocol_t client_back;// client_back在服务器中代表服务器要发回客户端的信息
#endif
