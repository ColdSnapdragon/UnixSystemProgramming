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

void * fun(void * arg)
{
	int *num = (int*)arg;
	printf("The %dth pthread's pid:%d ,tid: %lu\n",*num,getpid(),pthread_self());
	return NULL;
}

int main(int argc,char* argv[])
{
	printf("main tid : %lu\n",pthread_self());	
	
	pthread_t tid;

	for(int i=1;i<=5;++i)
	{
		int res = pthread_create(&tid, NULL, fun, (void*)&i);
		if(res != 0){ 
			printf("create pthread fail: %s\n",strerror(res));
			exit(1);
		}
		sleep(1);
	}

	//sleep(1);//延迟进程终止，等待线程主函数执行
	return 0;
}
