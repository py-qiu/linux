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
	int sockfd, nbytes;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to skcket");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.54");
	servaddr.sin_port = htons(8888);

	if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to connect");
		close(sockfd);
		exit(-1);
	}

	if ((nbytes = recv(sockfd, buf, MAXLINE, 0)) < 0)
	{
		perror("fail to recv");
		exit(-1);
	}

	printf("recv from server : %s\n", buf);

	return 0;

}
