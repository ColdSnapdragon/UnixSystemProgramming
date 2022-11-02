#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<sys/time.h>
#include<signal.h>
#include<string.h>

void perr(const char* str)
{
	perror(str);
	exit(1);
}

int main(int argc,char* argv[])
{
	int pid = fork();
	if(pid < 0) perr("fork error");
	if(pid > 0) exit(0);
	
	if(setsid()==-1) perr("setsid fail");
	
	umask(0022);

	if(chdir("/root")) perr("chdir fail");

	close(STDIN_FILENO);
	int fd = open("/dev/null",O_RDWR);
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);

	while(1);
	return 0;
}
