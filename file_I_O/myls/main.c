#include"include.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("please input filepath\n");
		return 0;
	}
	
	struct stat info;
	stat(argv[1], &info);
	
	filetype(argv[1]);//print filetype
	
	fileperm(argv[1]);//print permission
	
	printf("  %d  ", info.st_nlink);//print number of link
	
	fileowner(argv[1]);//print file owner

	printf("%ld", info.st_size);//print total size in bytes
	
	filetime(argv[1]);//print mtime
	
	printf("  %s\n", argv[1]);
	
	return 0;
}
