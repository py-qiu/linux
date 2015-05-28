/*************************************************************************
    > File Name: tcp_server.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Mon 25 May 2015 11:03:17 AM CST
	> create server, and send a message to connected client
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAXLINE 50


int main()
{
	int listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in myaddr, cliaddr;
	char buf[MAXLINE] = "Welcome to TCP Server";

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = inet_addr("192.168.1.54");
	myaddr.sin_port = htons(8888);

	if (bind(listenfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		close(listenfd);
		exit(-1);
	}

	listen(listenfd, 5);
	

	for (;;)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		printf("connection from %s, port %d\n", 
				inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		send(connfd, buf, sizeof(buf), 0);
		close(connfd);
	}

	return 0;
}

