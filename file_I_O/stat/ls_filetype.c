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
 * demo learn how to use stat()/lstat() to get file type
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * There are two methods to test the file type
 */
#define TEST_TYPE 2

int main(int argc, char *argv[])
{
	struct stat sb;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		return EXIT_FAILURE;
	}

	printf("File type: ");

#if TEST_TYPE == 1
	/* following macros are POSIX compatible */
	if (S_ISBLK(sb.st_mode)) 
		printf("block device\n");
	else if (S_ISCHR(sb.st_mode))
		printf("character device\n");
	else if (S_ISDIR(sb.st_mode))
		printf("directory\n");
	else if (S_ISFIFO(sb.st_mode))
		printf("FIFO/pipe\n");
	else if (S_ISLNK(sb.st_mode))
		printf("symlink\n");
	else if (S_ISREG(sb.st_mode))
		printf("regular file\n");
	else if (S_ISSOCK(sb.st_mode))
		printf("socket\n");
	else
		printf("unknown?\n");

#elif TEST_TYPE == 2

	switch (sb.st_mode & S_IFMT) {
	case S_IFBLK:	printf("block device\n");	break;
	case S_IFCHR:	printf("character device\n");	break;
	case S_IFDIR:	printf("directory\n");		break;
	case S_IFIFO:	printf("FIFO/pipe\n");		break;
	case S_IFLNK:	printf("symlink\n");		break;
	case S_IFREG:	printf("regular file\n");	break;
	case S_IFSOCK:	printf("socket\n");		break;
	default:	printf("unknown?\n");		break;
	}

#endif /* TEST_TYPE */
	
	return EXIT_SUCCESS;
}