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
#include<semaphore.h>
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

#define NUM 5

int que[NUM];

sem_t blank_num, data_num;

void *producer(void *args)
{
	int k=0;
	while(1)
	{
		sem_wait(&blank_num);
		int t = rand()%10;
		que[k] = t;
		printf("++++%d have been produced.\n", t);
		sem_post(&data_num);
		k = (k+1)%NUM;
		sleep(rand()%3);
	}
}

void *consumer(void *args)
{
	int k=0;
	while(1)
	{
		sem_wait(&data_num);
		printf("%d have been used.\n", que[k]);
		sem_post(&blank_num);
		k = (k+1)%NUM;
		sleep(rand()%3);
	}
}

int main(int argc,char* argv[])
{
	sem_init(&blank_num,0,NUM);
	sem_init(&data_num,0,0);
	
	pthread_t ptid,ctid;

	pthread_create(&ptid,NULL,producer,NULL);
	pthread_create(&ctid,NULL,consumer,NULL);

	pthread_join(ptid,NULL);
	pthread_join(ctid,NULL);

	sem_destroy(&blank_num);
	sem_destroy(&data_num);

	return 0;
}
