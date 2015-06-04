/*************************************************************************
  > File Name: server_init.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Fri 29 May 2015 09:34:31 AM CST
 ************************************************************************/

#include "include.h"

#define SERVER_ADDR "192.168.1.54"
sqlite3 *db;


/*
 * initialize the server, set local address information
 * open dict.txt, open database
 * success : 0
 * error   :-1
 */
int server_init()
{
	struct sockaddr_in server_addr;

	printf ("*****************************************\n");
	/*step1, create socket to listen*/
	if ((listenfd_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror ("server > create listen socket failed !!\n");
		printf ("*****************************************\n");
		exit (-1);
	}
	printf ("server > create listen socket success !!\n");
	printf ("*****************************************\n\n");

	/*step2, bind the socket to local connection*/
	memset (&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_addr.s_addr		= inet_addr(SERVER_ADDR);
	server_addr.sin_port	=htons(8888);
	printf ("server > bind IP address and Port...\n");
	printf ("         socket: %d\n", listenfd_server);
	printf ("         IP_address: %s\n", SERVER_ADDR);
	printf ("         port: %d\n\n", 8888);

	if (bind(listenfd_server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror ("server > bind IP address and Prot failed\n");
		printf ("*****************************************\n\n");
		close(listenfd_server);
		exit(-1);
	}
	printf ("server > bind success\n");
	printf ("*****************************************\n\n");


	/*step3, put the socket to listen mode*/
	listen (listenfd_server, 5);
	printf ("server > listen the socket %d\n\n", listenfd_server);

	printf ("server > initialize server success \n\n");
	printf ("*****************************************\n\n");


	/*open database*/
	if (database_open() < 0)/*open database failed*/
	{
		printf ("server > open database error\n\n");
		printf ("*****************************************\n\n");
		close(listenfd_server);
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
		close(listenfd_server);
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
 * run the server, and monitor socket listenfd_server
 * accept connection to connfd_server
 * success : 0
 * error   :-1
 */
int server_accept()
{
	struct sockaddr_in client_addr;
	socklen_t cliaddr_len;

	cliaddr_len = sizeof(client_addr);

	/*accept connection*/
	printf ("server > accept connection begin ...\n\n");
	if ((connfd_server = accept (listenfd_server, (struct sockaddr *)&client_addr, &cliaddr_len)) < 0)
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
			return -1; 
		}
		else
		{
			printf ("server > failed to allocate memory for database\n");
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

