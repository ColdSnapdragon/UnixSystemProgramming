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
	sigset_t st,oldst;
	sigemptyset(&st);
	sigaddset(&st,SIGINT);
	sigaddset(&st,SIGQUIT);
	if(sigprocmask(SIG_BLOCK,&st,&oldst))
		perr("sigprocmask fail");
	
	while(1)
	{
		if(sigpending(&st)) 
			perr("sigpending fail");
		for(int i=1;i<32;++i)
			printf("%d",sigismember(&st,i));
		printf("\n");
		sleep(1);
	}

	sigprocmask(SIG_SETMASK,&oldst,&st); //完成操作后，复原屏蔽集
	return 0;
}
