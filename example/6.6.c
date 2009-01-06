/*************************************************************************
  > File Name: 6.5.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Tue 26 May 2015 02:19:40 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>

#define MAXLINE 50
typedef struct sockaddr SA;

void reaper(int signo)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}


int main()
{
	int listenfd, connfd;
	int  nbyte;
	struct sockaddr_in myaddr;
	char buf[MAXLINE];

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&myaddr, sizeof(myaddr));

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8888);
	myaddr.sin_addr.s_addr = inet_addr("192.168.4.67");

	if (bind(listenfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	listen(listenfd, 5);

	signal(SIGCHLD, reaper);

	while (1)
	{
		connfd = accept(listenfd, NULL, NULL);
		printf("connection from %d\n", connfd);
		switch (fork())
		{
			case -1:
				close(connfd);
				break;
			case 0:
				close(listenfd);

				while ((nbyte = recv(connfd, buf, sizeof(buf), 0)) > 0)
				{
					printf("child, connection from %d\n", connfd);
					send(connfd, buf, nbyte, 0);
				}
				close(connfd);
				exit(0);
			default:
				close(connfd);
				break;
		}
	}

	return 0;
}

