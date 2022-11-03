#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

char buf[1100];

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("argument too few!\n");
		return 0;
	}
	const char *sour=argv[1], *tar=argv[2];
	int d1=open(sour,O_RDONLY);
	if(d1==-1)
	{
		printf("fail:%s\n",strerror(errno));
		return 0;
	}
	int d2=open(tar,O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if(d2==-1)
	{
		printf("fail:%s\n",strerror(errno));
		return 0;
	}
	int rz,wz,rt=0,wt=0;
	while(rz=read(d1,buf,1024))
	{
		if(rz==-1)
		{
			printf("fail:%s\n",strerror(errno));
			break;
		}
		wz=write(d2,buf,strlen(buf)); //或者传入rz
		if(wz==-1)
		{
			printf("fail:%s\n",strerror(errno));
			break;
		}
		rt+=rz,wt+=wz;
	}
	close(d2);
	printf("%d bytes copied and %d bytes pasted\n",rt,wt);
	return 0;		
}
