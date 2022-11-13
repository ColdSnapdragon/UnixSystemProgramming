#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int cnt;

int main(int argc,char* argv[])
{
	for(int i=1;i<=5;++i)
	{
		if(fork()==0)
		{
			++cnt;
			printf("I'm %dth child\n",i);
			return 0;
		}
	}
	sleep(1);
	printf("%d\n",cnt);
	return 0;
}
