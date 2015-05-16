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
 * demo how to use stat()/lstat() to get owner of the file
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	struct stat sb;
	struct passwd *pw;
	struct group *gr;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	if (stat(argv[1], &sb) == -1) {
		perror("stat error");
		return EXIT_FAILURE;
	}

	/* user ID/name of owner:
	 * The getpwuid() function returns a pointer to a structure 
	 * containing the broken-out fields of the record in the 
	 * password database (e.g., the local password file /etc/passwd, 
	 * NIS, and LDAP) that matches the user ID uid.
	 */
	pw = getpwuid(sb.st_uid);
	if (pw) {
		printf("The user name of owner is: %s\n", pw->pw_name);
	} else {
		printf("The user name of owner is: not found.\n");
	}

	/* group ID/name of owner:
	 * The getgrgid() function returns a pointer to a structure
	 * containing the broken-out fields of the record in the 
	 * group database (e.g., the local group file /etc/group, 
	 * NIS, and LDAP) that matches the group ID gid.
	 */
	gr = getgrgid(sb.st_gid);
	if (gr) {
		printf("The group name of owner is: %s\n", gr->gr_name);
	} else {
		printf("The group name of owner is: not found.\n");
	}
	
	return EXIT_SUCCESS;
}