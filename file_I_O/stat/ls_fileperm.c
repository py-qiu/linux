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
 * demo how to use stat()/lstat() to get permission mode of the file
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

	printf("File permission: ");

	/* file permissions - USER */
	if(S_IRUSR & sb.st_mode)
		printf("r");
	else	
		printf("-");
	if(S_IWUSR & sb.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXUSR & sb.st_mode)
		printf("x");
	else
		printf("-");

	/* file permissions - GROUP */
	if(S_IRGRP & sb.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWGRP & sb.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXGRP & sb.st_mode)
		printf("x");
	else
		printf("-");

	/* file permissions - OTHERS */
	if(S_IROTH & sb.st_mode)
		printf("r");
	else
		printf("-");
	if(S_IWOTH & sb.st_mode)
		printf("w");
	else
		printf("-");
	if(S_IXOTH & sb.st_mode)
		printf("x");
	else
		printf("-");
		
	printf("\n");
	
	return EXIT_SUCCESS;
}