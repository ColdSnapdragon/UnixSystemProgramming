#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char* argv[])
{
	int fd[2];
	if(pipe(fd))
	{
		perror("create pipe error");
		exit(1);
	}
	int pid = fork();
	if(pid > 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",argv[1],NULL);
		//close(fd[1]); //exec后面的代码不会起效
		//sleep(2);
	}
	else if(pid == 0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		close(fd[0]);
	}
	else
	{
		perror("fork fail");
		exit(1);
	}
	return 0;
}
