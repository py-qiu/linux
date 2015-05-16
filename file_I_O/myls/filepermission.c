#include"include.h"

void fileperm(char *file)
{
	struct stat info;
		
	lstat(file, &info);
	
	switch (info.st_mode & S_IRWXU)
	{
		case S_IRWXU:printf("rwx");break;
		case S_IRUSR:printf("r--");break;
		case S_IWUSR:printf("-w-");break;
		case S_IXUSR:printf("--x");break;
		case S_IRUSR|S_IWUSR:printf("rw-");break;
		case S_IRUSR|S_IXUSR:printf("r-x");break;
		case S_IWUSR|S_IXUSR:printf("-wx");break;
	}
	switch (info.st_mode & S_IRWXG)
	{
		case S_IRWXG:printf("rwx");break;
		case S_IRGRP:printf("r--");break;
		case S_IWGRP:printf("-w-");break;
		case S_IXGRP:printf("--x");break;
		case S_IRGRP|S_IWGRP:printf("rw-");break;
		case S_IRGRP|S_IXGRP:printf("r-x");break;
		case S_IWGRP|S_IXGRP:printf("-wx");break;
	}
	switch (info.st_mode & S_IRWXO)
	{
		case S_IRWXO:printf("rwx");break;
		case S_IROTH:printf("r--");break;
		case S_IWOTH:printf("-w-");break;
		case S_IXOTH:printf("--x");break;
		case S_IROTH|S_IWOTH:printf("rw-");break;
		case S_IROTH|S_IXOTH:printf("r-x");break;
		case S_IWOTH|S_IXOTH:printf("-wx");break;
	}
	return;
}
