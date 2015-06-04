/*************************************************************************
    > File Name: client_init.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Fri 29 May 2015 10:36:38 AM CST
 ************************************************************************/

#include "include.h"

#define  SERVER_ADDR "192.168.1.54"

/*
 * initialize client
 * success : sockfd
 * failed  : -1
 */
int client_init()
{
	int sockfd;
	struct sockaddr_in server_addr;

	/*step1, create socket to connetc*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror ("client > create socket failed !!");
		close(sockfd);
		exit (-1);
	}
	printf ("client > create socket success\n\n");

	/*step2, connect to server*/
	memset (&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_addr.s_addr		= inet_addr(SERVER_ADDR);
	server_addr.sin_port		= htons(8888);

	if (connect (sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror ("client > connect to server failed");
		close (sockfd);
		exit(-1);
	}

	printf ("client > connect to server %s port %d success\n\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

	return sockfd;
}
