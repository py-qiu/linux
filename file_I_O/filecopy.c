/* purpose:
 * - learn how to use file IO functions to open/close file
 *   and read/write data from/to the file
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAXSIZE 256	/* max read size one time from the source file */

int main(int argc, char *argv[])
{
	int	fd1, fd2;	/* fd1 for source file and fd2 for target file */
	char	buf[MAXSIZE];	/* read buffer */
	int	i;
	
	if (argc < 3)	{ /* check command format */
		printf("Usage: %s <sourcefile> <targetfile>\n", argv[0]);
		return 1;
	}
	
	/* open source file as read-only */
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		printf("open %s error\n", argv[1]);
		return 1;
	}
	
	/* open target file in append mode */
	//if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0) {
	if((fd2 = open(argv[2], O_WRONLY | O_CREAT, 0644)) < 0) {
		printf("open %s error\n", argv[1]);
		close(fd1); /* don't forget me! */
		return 1;
	}
	
	while (1) {
		i = read(fd1, buf, MAXSIZE);
		if (i < 0) {
			perror("read error");
			break;
		}
		else if (i == 0) {
			/* end of file */
			break;
		}
		else {
			/* the return value of write may be less than i
			 * here we just ignore this possibility
			 */
			if (write(fd2, buf, i) < 0) {
				perror("write error");
				break;
			}
		}
	}
	
	close(fd1);
	close(fd2);
	
	return 0;
}
