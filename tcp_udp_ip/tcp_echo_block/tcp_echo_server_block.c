/*
 * (C) Copyright 2014
 * http://www.farsight.com.cn/
 * http://nj.hqyj.com/
 * 
 * This program is distributed in the purpose for training only
 * and hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Revision history
 * ------------------------------------------------------
 * 20140928	unicornx	initial archived
 */
/*
 * enhanced example code for experiment #6.1
 * Demo how to implement a simple TCP echo server
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 50
typedef struct sockaddr  SA;

int main(int argc, char **argv)
{        
	int			listenfd; /* listen socket fd */
	int			connfd;	  /* connection socket fd */
	socklen_t		clilen;
	struct sockaddr_in  	myaddr, cliaddr;
	char			buf[MAXLINE+1];
	ssize_t			nbyte;			

	/* step1: create socket to listen
	 * note the listen socket is created as type of SOCK_STREAM to
	 * work in TCP 
	 */
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("S> socket error");
		exit(-1);
	}
	printf("S> socket() listenfd = %d\n", listenfd);
	
	/* step2: bind the socket to local connection point */
	memset(&myaddr, 0x00, sizeof(myaddr));
	myaddr.sin_family	= AF_INET;
	//myaddr.sin_addr.s_addr	= inet_addr("10.0.2.15");
	myaddr.sin_addr.s_addr	= INADDR_ANY;
	myaddr.sin_port		= htons(8888);	/* port number */
	if (bind(listenfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("S> bind error");
		exit(-1);
	}
	printf("S> bind()\n");
	
	/* step3: put the socket to listen/passive mode
	 * set max# of incoming pending connection queue is 5
	 */
	listen(listenfd, 5);
	printf("S> listen()\n");

	/* single process to service one connection a time */
	while(1) 
	{
		clilen = sizeof(cliaddr); // sizeof(struct sockaddr_in)
		/* step4: wait to accept connection request from the target client */
		printf("S> accept() begin...\n");
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		/* when accept returns, the connection with the client
		 * is setup and the accepted connection socket is returned
		 */
		if (connfd < 0) {
			perror("S> accept error");
			continue;
		}
		printf("S> accept() connection fd = %d from %s, port %d\n",
	          	connfd, inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		
		/* step5: echo till the connection is shutdown from client end */
		while(1) {
			printf("S> read() begin ...\n");
			if ( (nbyte = read(connfd, buf, MAXLINE)) < 0) {
				perror("S> read error");
				/* continue next round of read */
				
			} else if (0 == nbyte) {
				printf("S> read() 0 when the peer has performed an orderly shutdown\n");
				break;
				
			} else {
				/* echo */
				buf[nbyte] = 0x00; /* complete a string */
				printf("S> read() done. message: %s\n", buf);
				printf("S> write() message: %s\n", buf);
				if (write(connfd, buf, nbyte) < 0) {
					perror("S> write error");
					/* continue next round of read */
				} else {
					printf("S> write() done\n");
				}
			}
		} /* service session cycle */
		
		/* step6: close the connection session with client 
		 * due to peer has shutdown 
		 */
		close(connfd);
		printf("S> close()\n");
	} /* accept cycle */
	
	return 0;
}

