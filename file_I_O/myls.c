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
 * Requirements: to implement same behaviour as
 * we input "ls -l filepath".
 * Through this exercise to learn how to use stat()/lstat() to 
 * get file info.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAXLEN_SYMBLINK 64 /* max length of symbolic link string to be displayed */

int main(int argc ,char *argv[])
{
	struct stat	buf;
	char		out[MAXLEN_SYMBLINK+1]; /* 1 is reserved to end the string with 0x00 */
	struct tm 	*t;
	ssize_t		n;
	
	if (argc < 2) {
		fprintf(stderr,"Usage: %s <pathname>\n", argv[0]);
		return 0;
	}

	/*
	 * Note: this sample uses lstat but not stat to 
	 * implement the same as "ls -l".
	 * man 2 stat: "The lstat function is similar to stat, 
	 * but when the named file is a symbolic link, lstat 
	 * returns information about the symbolic link, not 
	 * the file referenced by the symbolic link."
	 */
	if (lstat(argv[1], &buf) < 0) {
		perror("lstat error");
		return -1;
	}

	/* file type */
	switch (buf.st_mode & S_IFMT) {
	case S_IFREG:
	default:
		printf("-");
		break;
	case S_IFDIR:
		printf("d");
		break;
	case S_IFCHR:
		printf("c");
		break;
	case S_IFBLK:
		printf("b");
		break;
	case S_IFIFO:
		printf("p");
		break;
	case S_IFLNK:
		printf("l");
		break;
	case S_IFSOCK:
		printf("s");
		break;
	}

	/* file permissions - USER */
	if(S_IRUSR & buf.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWUSR & buf.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXUSR & buf.st_mode)
		printf("x");
	else
		printf("-");

	/* file permissions - GROUP */
	if(S_IRGRP & buf.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWGRP & buf.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXGRP & buf.st_mode)
		printf("x");
	else
		printf("-");

	/* file permissions - OTHERS */
	if(S_IROTH & buf.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWOTH & buf.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXOTH & buf.st_mode)
		printf("x");
	else
		printf("-");

	/* number of links */
	printf(" %d",buf.st_nlink);

	/* user ID/name of owner */
	struct passwd *pw;
	pw = getpwuid(buf.st_uid);
	printf(" %s", pw->pw_name);

	/* group ID/name of owner */
	struct group *gr;
	gr = getgrgid(buf.st_gid);
	printf(" %s", gr->gr_name);

	/* size in bytes, for regular files */
	printf(" %12ld", buf.st_size);

	/* time of last modificaiton */
	t = localtime(&buf.st_mtime);
	printf(" %04d-%02d-%02d %02d:%02d",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min);

	/* file name */
	printf(" %s ", argv[1]);

	/* is it a link */
	if (S_ISLNK(buf.st_mode)) {
		printf(" -> ");
		if (-1 == (n = readlink(argv[1], out, MAXLEN_SYMBLINK))) {
			perror("readlink error");
		} else {
			out[n] = 0x00;
			printf("%s", out);
		}
	}
	
	printf("\n");
	
	return 0;
}
