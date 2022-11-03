#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[])
{
	struct stat dat;
	int res = stat(argv[1], &dat);
	if(res)
	{
		perror("stat error!");
		exit(1);
	}
	printf("size:%u\n",dat.st_size);	
	unsigned int mode = dat.st_mode;
	if(S_ISREG(mode))
		printf("Is a regular file\n");
	else if(S_ISDIR(mode))
		printf("Is a directory\n");
	else if(S_ISLNK(mode))
		printf("Is a link\n");
	else
		printf("Other file\n");
	return 0;
}
