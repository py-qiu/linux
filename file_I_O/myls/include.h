#include<sys/types.h>

#include<sys/stat.h>

#include<unistd.h>

#include<stdio.h>
#include<pwd.h>
#include<time.h>

#include<grp.h>

void  filetype(char *file);
void fileowner(char *file);
void fileperm(char *file);
