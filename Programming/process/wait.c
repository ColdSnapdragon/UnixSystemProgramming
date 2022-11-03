#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char* argv[])
{
	int pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	if(pid == 0)
	{
		printf("process %d is sleeping...\n",getpid());
		sleep(8);
		return 11;
	}
	int sta;
	wait(&sta);
	if(WIFEXITED(sta))
	{
		printf("child %d 's exit-value is %d\n",pid,WEXITSTATUS(sta));	
	}
	if(WIFSIGNALED(sta))
	{
		printf("child %d 's term-signal is %d\n",pid,WTERMSIG(sta));	
	}
	return 0;
}
