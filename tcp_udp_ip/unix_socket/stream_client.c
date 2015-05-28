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
 * sample to demo code for client side about socket of UNIX 
 * protocol family in stream mode.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAXBUF 50

typedef struct sockaddr SA;

int main(int argc, char *argv[])
{
	int			connfd;
	char			buf[MAXBUF] = "Hello from client";
	struct sockaddr_un	srv_addr;
	char			*ipc_path;
	int 			retval = 0;

	if (argc < 2) {
		printf ("usage: %s <ipc_path>\n", argv[0]);
		return 1;
	}
	ipc_path = argv[1];

	if ((connfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket() error");
		return 1;
	}
	
	memset(&srv_addr, 0x00, sizeof(srv_addr));
	srv_addr.sun_family = AF_UNIX;
	strcpy(srv_addr.sun_path, ipc_path);
	if (-1 == connect(connfd, 
			(struct sockaddr *)(&srv_addr), 
			sizeof(srv_addr))) {
		perror("connect() error");
		retval = 1;
		goto _exit_entry;
	}
	
	if (write(connfd, buf, strlen(buf)) < 0) {
		perror("write() error");
		retval = 1;
		goto _exit_entry;
	}
	printf("send message to server: %s\n", buf);
	
_exit_entry:
	close(connfd);
	
	return retval;
}
