#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<string.h>

void perr(const char* str)
{
	perror(str);
	exit(1);
}

struct dat{
	int id;
	char name[256];
};

int main(int argc,char* argv[])
{
	int fd = open("text", O_RDONLY|O_CREAT, 0644);
	if(fd == -1)
		perr("open fail");
	
	struct dat *pt;
	//if(ftruncate(fd,1024)) //fd必须可写
	//	perr("ftruncate fail");
	size_t len = lseek(fd, 0, SEEK_END);
	pt = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	close(fd);
	if(pt==MAP_FAILED)
		perr("mmap fail");

	int pid = fork();
	if(pid==-1)
		perr("fork fail");
	else if(pid > 0)
	{
		for(int i=1; ;++i)
		{
			pt->id=i;
			sprintf(pt->name,"hello mmap(%d)",rand());
			sleep(1);
		}
	}
	else if(pid==0)
	{
		while(1)
		{
			printf("%d: %s\n",pt->id,pt->name);
			sleep(1);
		}
	}

	if(munmap(pt,len))
		perr("munmap fail");
	return 0;
}
