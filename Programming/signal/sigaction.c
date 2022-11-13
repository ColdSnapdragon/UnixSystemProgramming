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

void sig_catch(int sg)
{
	printf("catch signal %d\n",sg);
	return;
}

int main(int argc,char* argv[])
{
	struct sigaction act,oldact;
	act.sa_handler=sig_catch;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	if(sigaction(SIGINT,&act,&oldact))
		perr("sigaction fail");
	
	while(1);

	return 0;
}
