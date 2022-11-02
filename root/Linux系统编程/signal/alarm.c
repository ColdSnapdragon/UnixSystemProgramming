#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<string.h>

void perr(const char* str)
{
	perror(str);
	exit(1);
}

int main(int argc,char* argv[])
{
	alarm(1);
	int i;
	for(i=0;;++i)printf("%d\n",i);
	return 0;
}
