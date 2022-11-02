#include<unistd.h>//包含open()
#include<fcntl.h>//包含O_REONLY
#include<stdio.h>
#include<errno.h>//包含errno
#include<string.h>//包含strerror，显示errno代表的详细错误信息

int main(int argc,char *argv[])
{
	int fd = open("./cc", O_RDONLY | O_CREAT, 0222);
	
	printf("fd = %d errno = %d(%s)\n", fd, errno, strerror(errno));
	
	close(fd);
	
	return 0;
}
