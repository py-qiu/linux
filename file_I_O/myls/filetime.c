#include"include.h"

void filetime(char *file)
{
	struct stat info;
	
	lstat(file, &info);
	
	int month = 0;
	int date = 0;
	int hour = 0;
	int minute = 0;
		
	struct tm *time;
	
	time = localtime(&info.st_mtime);
	
	month = time->tm_mon;
	date = time->tm_mday;
	hour = time->tm_hour;
	minute = time->tm_min;

	printf("  %d", month);
	printf("  %d", date);
	printf("  %d ", hour);
	printf(": %d", minute);

	return;	
}
