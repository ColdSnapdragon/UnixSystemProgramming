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
	int pid;
	while( (pid=waitpid(-1,NULL,WNOHANG)) > 0)
	{
		printf("zombie process %d have been free.\n",pid);
	}
	return;
}

int main(int argc,char* argv[])
{
	sigset_t st;
	sigemptyset(&st);
	sigaddset(&st,SIGCHLD);
	if(sigprocmask(SIG_BLOCK,&st,NULL))
		perr("sigprocmask fail");
	
	int N=10,pid,i;
	for(i=0;i<N;++i)
		if((pid=fork())==0)
			break;
	
	if(i==N)
	{
		struct sigaction act;
		act.sa_handler=sig_catch;
		act.sa_flags=0;
		sigemptyset(&act.sa_mask);

		sigaction(SIGCHLD,&act,NULL);
		
		if(sigprocmask(SIG_UNBLOCK,&st,NULL))
			perr("sigprocmask fail");

		while(1);
	}
	else
	{
		sleep(1);
		printf("child %d end.\n",getpid());
	}

	return 0;
}
