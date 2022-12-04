#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[])
{
	int fd = open("out", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	int res = fork();
	if(res==-1) exit(1);
	if(res == 0)
	{
		execlp("ps","ps","axu","NULL");
		perror("execlp fail");
		exit(1);
	}
	sleep(1);
	close(fd);
	return 0;
}
