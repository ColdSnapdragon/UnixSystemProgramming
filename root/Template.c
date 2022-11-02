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
#include<pthread.h>
#include<string.h>

void perr(const char* str)
{
	perror(str);
	exit(1);
}

int main(int argc,char* argv[])
{
	
	return 0;
}
