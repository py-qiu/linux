/*************************************************************************
  > File Name: pipe_select.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Tue 26 May 2015 08:04:47 PM CST
  > 多路复用I/O模型的使用，监视三个打开的文件描述符，fd[0]为stdin, fd[1]为FIFO1, fd[2]为FIFO2
  > 将读到的数据输出
  > 如果标准输入的首字母为q或Q，则退出
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<time.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO1 "in1"
#define FIFO2 "in2"

#define MAX_BUFFER_SIZE 1024
#define IN_FILES 3
#define TIME_DELAY 60
#define MAX(a, b) ((a>b)?(a):(b))

int main()
{
	int fds[IN_FILES];
	char buf[MAX_BUFFER_SIZE];
	int i, res, real_read, maxfd;
	struct timeval tv;
	fd_set inset, tmp_inset;//多路复用IO

	fds[0] = 0;//stdin

	/*
	 *创建FIFO1， in1
	 */
	if (access(FIFO1, F_OK) == -1)
	{
		if (mkfifo(FIFO1, 0666) < 0)
		{
			perror("fail to create fifo1");
			exit(-1);
		}
	}

	/*
	 *创建FIFO2， in2
	 */
	if (access(FIFO2, F_OK) == -1)
	{
		if (mkfifo(FIFO2, 0666) < 0)
		{
			perror("fail to create fifo2");
			exit(-1);
		}
	}

	/*
	 *打开管道FIFO1，FIFO2
	 */
	if ((fds[1] = open(FIFO1, O_RDONLY|O_NONBLOCK)) < 0)
	{
		perror("fail to open fifo1");
		exit(-1);
	}

	if ((fds[2] = open(FIFO2, O_RDONLY|O_NONBLOCK)) < 0)
	{
		perror("fail to open fifo2");
		exit(-1);
	}

	/*
	 *多路复用IO
	 */
	maxfd = MAX(MAX(fds[0], fds[1]), fds[2]);
	FD_ZERO(&inset);

	for (i=0; i<IN_FILES; i++)
	{
		FD_SET(fds[i], &inset); //将三个打开的文件描述符添加到检测集中
	}

	//设置超时时间
	tv.tv_sec = TIME_DELAY;
	tv.tv_usec = 0;


	while (FD_ISSET(fds[0], &inset) || FD_ISSET(fds[1], &inset) || FD_ISSET(fds[2], &inset))
	{
		tmp_inset = inset;//备份原检测集

		res = select(maxfd + 1, &tmp_inset, NULL, NULL, &tv);//提交select开始监视

		switch (res)
		{
			case -1://select错误
				{
					perror("fail to select");
					close(fds[1]);
					close(fds[2]);
					exit(-1);
					break;
				}
			case 0://超时
				{
					printf("time out\n");
					close(fds[1]);
					close(fds[2]);
					exit(-1);
					break;
				}
			default://至少有一个文件描述符命中
				{
					for (i=0; i<IN_FILES; i++)
					{
						if (FD_ISSET(fds[i], &tmp_inset))
						{
							memset(buf, 0, MAX_BUFFER_SIZE);
							real_read = read(fds[i], buf, MAX_BUFFER_SIZE);
							if (real_read < 0)
							{
								if (errno != EAGAIN)
								{
									close(fds[1]);
									close(fds[2]);
									return 1;
								}
							}
							else if(!real_read)
							{
								close(fds[i]);
								FD_CLR(fds[i], &inset);
							}
							else
							{
								if (i == 0)//如果是标准输入
								{
									if ((buf[0] == 'q') || (buf[0] == 'Q'))
									{
										close(fds[1]);
										close(fds[2]);
										return 1;
									}
									buf[real_read] = '\0';
									printf("%s", buf);
								}//如果是管道
								else
								{
									buf[real_read] = '\0';
									printf("%s", buf);
								}
							}
						}
					}
					break;
				}
		}
	}
	close(fds[1]);
	close(fds[2]);
	return 0;
}
