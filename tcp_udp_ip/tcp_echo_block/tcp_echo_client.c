/*************************************************************************
  > File Name: tcp_client.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Mon 25 May 2015 11:25:44 AM CST
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
	int sockfd, nr;
	struct sockaddr_in servaddr;
	char bufr[MAXLINE];
	char bufw[MAXLINE];
	char buf[MAXLINE];
	char *p;

	p=buf;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to skcket");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.4.63");
	servaddr.sin_port = htons(8888);

	if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to connect");
		close(sockfd);
		exit(-1);
	}

	while (1)
	{
		p = fgets(bufw, MAXLINE, stdin);
		printf("%s", p);
		
		if (strncmp(p, "quit", 4) == 0)
		{
			printf("client quit\n");
			close(sockfd);
			exit(0);
		}

		write (sockfd, bufw, MAXLINE);

		if ((nr = read(sockfd, bufr, MAXLINE)) == 0)
		{
			break;
		}

		printf("recv from server : %s", bufr);
	}
	return 0;

}
