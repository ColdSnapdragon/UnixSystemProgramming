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
	struct itimerval new_t,old_t;
	new_t.it_value.tv_sec=3;
	new_t.it_value.tv_usec=0;
	new_t.it_interval.tv_sec=5;
	new_t.it_interval.tv_usec=0;

	if(setitimer(ITIMER_REAL, &new_t, &old_t))
		perr("setitimer fail");
	
	getchar();

	return 0;
}
