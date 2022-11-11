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
	int pid,fd[2];
	if(pipe(fd))
		prr("create pipe fail");
	int i;
	for(i=0;i<2;++i)
	{
		pid = fork();
		if(pid == 0)
			break;
		if(pid < 0)
			prr("fork fail");
	}
	if(i==0)//第一个子进程
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
		prr("exec error");
	}
	else if(i==1)//第二个子进程
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		prr("exec error");
	}
	else
	{//此时两个子进程已被创建
		//close(fd[1]);
		write(fd[1],"hello",5);
		wait(NULL);
		wait(NULL);
	}
	return 0;
}
