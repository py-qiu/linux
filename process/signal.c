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
  * This is sample demos how to disposition the handler for SIGINT.
  *
  * Note that differnt system calls or lib functions may have
  * different and their own behaviours when interrupted by
  * a signal, read manpage of each API carefully for more details.
  */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

void sig_handler(int signo);

int main(int argc, char *argv[])
{
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		perror("signal error");
		return -1;
	}

	if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
		perror("signal error");
		return -1;
	}
	
	while(1);

	return 0;
}

void sig_handler(int signo)
{
	if (signo == SIGINT)
		printf("I received a SIGINT!\n");

	if (signo == SIGQUIT)
		printf("I received a SIGQUIT!\n");

}

