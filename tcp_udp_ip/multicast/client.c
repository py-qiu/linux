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
 * sample to demo server side code about multicast
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
#define IPADDR_GROUP	"226.0.0.1"
#define PORT_GROUP	8888

typedef struct sockaddr SA;

int main(void)
{
	int sockfd;
	struct sockaddr_in dest_addr; /* destination socket address */
	char buf_snd[MAXLINE] = "Hello, everyone in my group!";
	
	/* 
	 * step1: create socket
	 * note the socket is creaed as type of SOCK_DGRAM
	 * By now, it should be obvious that multicast traffic is 
	 * handled at the transport layer with UDP, as TCP 
	 * provides point-to-point connections, not feasibles 
	 * for multicast traffic.
	 * See http://www.tldp.org/HOWTO/Multicast-HOWTO-2.html#ss2.3 
	 */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket failed");
		return 1;
	}
	
	/* step2: send w/o bind */
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT_GROUP);
	dest_addr.sin_addr.s_addr = inet_addr(IPADDR_GROUP); 
	if (-1 == sendto(
		sockfd, 
		buf_snd, 
		sizeof(buf_snd), 
		0, 
		(SA *)&dest_addr, 
		sizeof(dest_addr)
		)) {
		perror("sendto failed");
		exit(1);
	}
	printf("sendto(multicast) successed!\n");

	return 0;
}
