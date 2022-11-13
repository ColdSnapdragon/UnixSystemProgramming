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

struct dat{
	struct dat *nxt;
	int val;
};
struct dat *head = NULL;

pthread_mutex_t mt;
pthread_cond_t cond;

void* consumer(void* arg)
{
	while(1)
	{
		int ret;
		ret = pthread_mutex_lock(&mt);
		fperr("mutex lock fail",ret);
		while(head == NULL)
		{
			ret = pthread_cond_wait(&cond,&mt);
			fperr("cond wait fail",ret);
		}
		struct dat *pt = head;
		head = pt->nxt;
		printf("----data%d have been received.\n",pt->val);
		free(pt); //别忘
		ret = pthread_mutex_unlock(&mt);
		fperr("mutex unlock fail",ret);
		sleep(rand()%3);
	}
	return NULL;
}

void* producer(void* arg)
{
	while(1)
	{
		int ret;
		struct dat* pt = (struct dat*)malloc(sizeof(struct dat));
		pt->val=rand()%100+1;
		ret = pthread_mutex_lock(&mt);
		fperr("mutex lock fail",ret);
		pt->nxt=head;
		head=pt;
		printf("++++data%d have been produced.\n",pt->val);
		ret = pthread_mutex_unlock(&mt);
		fperr("mutex unlock fail",ret);
		pthread_cond_signal(&cond);
		sleep(rand()%3);
	}
	return NULL;
}

int main(int argc,char* argv[])
{
	srand(time(NULL));
	pthread_mutex_init(&mt,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_t ctid, ptid;
	int ret;
	ret = pthread_create(&ctid,NULL,consumer,NULL);
	fperr("pthread create fail",ret);	
	ret = pthread_create(&ptid,NULL,producer,NULL);
	fperr("pthread create fail",ret);
	pthread_join(ctid,NULL);
	pthread_join(ptid,NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mt);
	return 0;
}
