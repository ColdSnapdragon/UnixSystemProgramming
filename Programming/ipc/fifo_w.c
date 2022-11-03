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
	int fd = open("ff",O_WRONLY);
	if(fd==-1) prr("open ff fail");
	
	char msg[256];
	for(int i=1; ;++i)
	{
		sprintf(msg,"%d times send data.\n",i);
		if(write(fd,msg,strlen(msg))==-1)
			prr("write fail");
		sleep(1);
	}

	return 0;
}
