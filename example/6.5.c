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
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAXLINE 50
typedef struct sockaddr SA;

int main()
{
	int listenfd, connfd, maxfd;
	int i, nbyte;
	struct sockaddr_in myaddr;
	char buf[MAXLINE];
	fd_set global_rdfs, current_rdfs;

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

	FD_ZERO(&global_rdfs);
	FD_SET(listenfd, &global_rdfs);

	maxfd = listenfd;

	while (1)
	{
		current_rdfs = global_rdfs;
		if (select(maxfd+1, &current_rdfs, NULL, NULL, 0) < 0)
		{
			perror("fail to select");
			exit(-1);
		}
		else
		{
			for (i=0; i<=maxfd; i++)
			{
				if (FD_ISSET(i, &current_rdfs))
				{
					if (i == listenfd)
					{
						connfd = accept(listenfd, NULL, NULL);
						FD_SET(connfd, &global_rdfs);
						maxfd = maxfd > connfd ? maxfd : connfd;
					}
					else
					{
						if ((nbyte = recv(i, buf, sizeof(buf), 0)) <= 0)
						{
							close(i);
							FD_CLR(i, &global_rdfs);
						}
						else
						{
							send(i, buf, nbyte, 0);
							
						}
					}
				}
			}
		}
	}

	return 0;
}
