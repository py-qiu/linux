#include"include.h"

void fileowner(char *file)
{
	struct stat info;

	lstat(file, &info);
	
	struct passwd *owner = getpwuid(info.st_uid);
	
	struct group *grp = getgrgid(info.st_gid);
	
	printf("%s  ", owner->pw_name);
	printf("%s  ", grp->gr_name);
	
	return;	
}
