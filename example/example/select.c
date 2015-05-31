/*************************************************************************
    > File Name: select.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Tue 26 May 2015 11:38:16 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define N 64

typedef struct sockaddr SA;

int main()
{
	int i, listenfd, connfd, maxfd;
	char buf[N];
	fd_set rdfs;

	struct sockaddr_in myaddr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8888);
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(listenfd, (SA *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		close(listenfd);
		exit(-1);
	}

	listen(listenfd, 5);

	maxfd = listenfd;

	while (1)
	{
		FD_ZERO(&rdfs);
		FD_SET(0, &rdfs);
		FD_SET(listenfd, &rdfs);

		if (select(maxfd+1, &rdfs, NULL, NULL, NULL) < 0)
		{
			perror("fail to select");
			close(listenfd);
			exit(-1);
		}

		for (i=0; i<=maxfd; i++)
		{
			if (FD_ISSET(i, &rdfs))
			{
				if (i == STDIN_FILENO)
				{
					fgets(buf, N, stdin);
					printf("%s\n", buf);
				}
				else if(i == listenfd)
				{
					connfd = accept(listenfd, NULL, NULL);
					printf("New connection %d is comming\n", connfd);
					//close(connfd);
				}
			}
		}
	}

	return 0;
}
