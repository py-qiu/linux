/*************************************************************************
    > File Name: public.c
    > Author: qiu
    > Mail: py_qiu@163.com 
    > Created Time: Fri 29 May 2015 11:52:24 AM CST
 ************************************************************************/

#include "include.h"

/*
 * send information
 * success : 0
 * failed  :-1
 */
int send_to(int dest_fd, xprotocol_t *packet)
{
	packet->hdr.cmd_type = htons (packet->hdr.cmd_type);
	packet->hdr.ret_code = htons (packet->hdr.ret_code);

	if (write (dest_fd, packet, sizeof(xprotocol_t)) < 0)
	{
		perror ("    > send message error");
		exit (-1);
	}
	
	printf ("    > send message success\n");
	return 0;
}


/*
 * recv information 
 * success ： 0
 * failed ： -1
 */
int recv_from (int src_fd, xprotocol_t *packet)
{
	if (read(src_fd, packet, sizeof(xprotocol_t)) < 0)
	{
		perror ("read error");
		exit (-1);
	}

	packet->hdr.cmd_type = ntohs(packet->hdr.cmd_type);
	packet->hdr.ret_code = ntohs(packet->hdr.ret_code);

	return 0;
}
