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

void fperr(const char *str, int en)
{
	if(en)
	{

		fprintf(stderr,"%s: %s\n",str,strerror(en));
		exit(1);
	}
}

void *tfn(void *arg)
{
	int num = (int)arg;
	char *s = (char*)malloc(20*sizeof(char));
	sprintf(s,"%d-th pthread have over.",num);
	return (void*)s;
}

int main(int argc,char* argv[])
{
	pthread_t tid[5];
	for(int i=1;i<=3;++i)
	{
		int ret = pthread_create(tid+i,NULL,tfn,(void*)i);
		fperr("pthread create fail",ret);
	}
	for(int i=1;i<=3;++i)
	{
		char *rtv;
		int ret = pthread_join(tid[i],(void**)&rtv);
		fperr("pthread free fail",ret);
		puts(rtv);
		free(rtv);
	}
	return 0;
}
