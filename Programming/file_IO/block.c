#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[])
{
	int flag = fcntl(STDIN_FILENO, F_GETFL);
	if(flag==-1)
	{
		perror("error");
		exit(1);
	}
	flag |= O_NONBLOCK;
	int res = fcntl(STDIN_FILENO, F_SETFL, flag);
	if(res==-1)
	{
		perror("error");
		exit(1);
	}
	int times=5,rz;
	char buf[1030];
	while(times--)
	{
		rz = read(STDIN_FILENO, buf, 1024);
		if(rz>0)
			break;
		else if(rz==-1)
		{
			if(errno == EAGAIN)
				printf("try again\n");
			else
			{
				perror("read error\n");
				exit(1);
			}
		}
		sleep(2);
	}
	if(times<0)
		perror("time out\n");
	else{
		int wz = write(STDOUT_FILENO, buf, rz);
		if(wz == -1)
		{
			perror("write error\n");
			exit(1);
		}
	}
	return 0;
}
