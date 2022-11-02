#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

void printtab(int num)
{
	printf("\n");
	for(int i=0;i<num;++i)
		printf("\t");
}

void ls(const char *tar,const char *name,int depth)
{
	struct stat dat;
	if(stat(tar,&dat))
	{
		perror("stat error");
		exit(1);
	}
	if(S_ISDIR(dat.st_mode))
	{
		printtab(depth);
		printf("%s---- ",name);
		DIR *dp = opendir(tar);
		struct dirent* dtp;
		char des[256];
		while((dtp = readdir(dp))!=NULL)
		{
			if(dtp->d_name[0]=='.') continue;
			if(strlen(tar)+strlen(dtp->d_name)+2>256)
			{
				printf("error: path %s/%s is too long.\n",tar,dtp->d_name);
				continue;
			}
			sprintf(des,"%s/%s",tar,dtp->d_name);
			ls(des,dtp->d_name,depth+1);
		}
		printf("\n");
	}
	else
	{
		printtab(depth);
		printf("%s",name);
		return;
	}
}

int main(int argc,char* argv[])
{
	ls(argv[1],argv[1],0);	
	printf("\n");
	return 0;
}
