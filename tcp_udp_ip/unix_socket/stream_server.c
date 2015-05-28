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
 * sample to demo code for server side about socket of UNIX 
 * protocol family in stream mode.
 */
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MAXLINE 50
#define MAXBUF	(MAXLINE + 1)

typedef struct sockaddr SA;

int main(int argc, char *argv[])
{
	int			listenfd, connfd;
	ssize_t			rcvlen;
	char			buf[MAXBUF]; 
	struct sockaddr_un	local_addr;
	char			*ipc_path;
	int			retval = 0;
        
	if (argc < 2) {
		printf ("usage: %s <ipc_path>\n", argv[0]);
		return 1;
	}
	ipc_path = argv[1];
	
	/* 
	 * unlink here to make sure the socket file does NOT exixt,
	 * so we can avoid failure of bind() later
	 * unlink may return error when the file does not exist,
	 * just ignore it.
	 */
	if (-1 == unlink(ipc_path)) {
		if (ENOENT == errno) {
			perror("unlink warning");
		} else {
			perror("unlink error");
			return 1;
		}
	}

	listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listenfd < 0) {
		perror("socket() error");
		return 1;
	}
    
	memset(&local_addr, 0x00, sizeof(local_addr));
	local_addr.sun_family = AF_UNIX;
	strcpy(local_addr.sun_path, ipc_path);
	if (-1 == bind(
			listenfd, 
			(struct sockaddr *)&local_addr, 
			sizeof(local_addr))) {
		perror("bind() error");
		retval = 1;
		goto _exit_entry;
	}
	
	if (-1 == listen(listenfd, 5)) {
		perror("listen() error");
		retval = 1;
		goto _exit_entry;
	}
	
	if ((connfd = accept(listenfd, NULL, NULL)) < 0) {
		perror("accept() error");
		retval = 1;
		goto _exit_entry;
	}
	
	memset(buf, 0x00, MAXBUF);
	if ((rcvlen = read(connfd, buf, MAXBUF)) < 0) {
		perror("read failed");
		retval = 1;
		goto _exit_entry;
	}
	buf[rcvlen] = 0x00; /* end as string */
	printf("recv message from client successfully: %s\n", buf);
	
_exit_entry:
	/* remove the socket file anyway */
	unlink(ipc_path);
	
	close(listenfd);
	close(connfd);
	
	return retval;
}
