#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>

void prr(const char* str)
{
	perror(str);
	exit(1);
}

int main(int argc,char* argv[])
{
	//if(mkfifo("ff",0000))
	//	prr("make fifo fail");
	
	int fd = open("ff",O_RDONLY);

	if(fd==-1) prr("open ff fail");
	
	char msg[256];
	while(1)
	{
		if(read(fd,msg,256)==-1)
			prr("read fail");
		printf(msg);
		sleep(1);
	}

	return 0;
}
