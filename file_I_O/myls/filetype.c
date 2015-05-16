#include"include.h"

void filetype(char *file)
{
	struct stat info;
	lstat(file, &info);
	
	switch (info.st_mode & S_IFMT)
	{		
		case S_IFSOCK:printf("s");break;
		
		case S_IFLNK:printf("l");break;
		
		case S_IFREG:printf("-");break;
		
		case S_IFBLK:printf("b");break;
		
		case S_IFDIR:printf("d");break;
		
		case S_IFCHR:printf("c");break;
		
		case S_IFIFO:printf("f");break;
		
		default:printf("unknown");break;
	}
		return ;
}
