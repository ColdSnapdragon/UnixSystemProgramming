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

void fperr(const char *str, int en)
{
	if(en)
	{

		fprintf(stderr,"%s: %s\n",str,strerror(en));
		exit(1);
	}
}

void * tfn(void *arg)
{
	printf("pthread %d have been created.\n",pthread_self());
	return NULL;
}

int main(int argc,char* argv[])
{
	int ret;
	pthread_attr_t attr;
	ret = pthread_attr_init(&attr);
	fperr("pthread attr init fail",ret);
	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	fperr("pthread attr setdetach fail",ret);	
	pthread_t tid;
	ret = pthread_create(&tid,&attr,tfn,NULL);
	fperr("pthread create fail",ret);
	
	sleep(1);
	
	ret = pthread_join(tid,NULL); //尝试回收已分离的线程
	fperr("pthread join fail",ret);
	pthread_attr_destroy(&attr);
	return 0;
}
