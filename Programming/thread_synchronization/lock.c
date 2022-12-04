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

pthread_mutex_t mt;

void* tfn(void* arg)
{
	while(1)
	{
		
		pthread_mutex_lock(&mt);
		printf("hello ");
		usleep(1000);
		printf("world\n");
		pthread_mutex_unlock(&mt);
		usleep(3000);
	}
}

int main(int argc,char* argv[])
{
	pthread_mutex_init(&mt,NULL);
	pthread_t tid;
	int ret = pthread_create(&tid,NULL,tfn,NULL);
	fperr("pthread create fail",ret);
	while(1)
	{
		pthread_mutex_lock(&mt);
		printf("HELLO ");
		usleep(1000);
		printf("WORLD\n");
		pthread_mutex_unlock(&mt);//访问完贡献资源后立即解锁，减小粒度 
		usleep(3000);
	}
	pthread_mutex_destroy(&mt);	
	return 0;
}
