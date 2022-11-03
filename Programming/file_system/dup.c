#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[])
{
	int fd = open(argv[1], O_WRONLY | O_APPEND);
	
	int res = dup2(fd, STDOUT_FILENO);

	if(res==-1)
	{
		perror("dup2 fail");
		exit(1);
	}

	printf("change the output successfully\n");

	return 0;
}
