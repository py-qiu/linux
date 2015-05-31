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

#define MAXLEN_USRNAME 15

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

//服务器部分
#define RPL_Register		0x8001
#define RPL_Login			0x8002
//没有RPL_Logout 
#define RPL_Query			0x8004	
#define RPL_History			0x8005

#define FAILED (uint16_t)-1
#define SUCCESS (uint16_t)0

#define EREGISTER (uint16_t)1
#define EQUERYHIS (uint16_t)2
#define EQHISEND (uint16_t)3
#define EOPEN_DATABASE (uint16_t)5

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

int server_init();
int server_accept();
int server_running();

int client_init();
int send_to(int dest_fd, xprotocol_t *packet);
int recv_from (int src_fd, xprotocol_t *packet);


void func_register();
int func_login();
int func_query();
void func_history();
