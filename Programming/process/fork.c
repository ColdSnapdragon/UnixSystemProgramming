#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc,char* argv[])
{
	puts("1");
	puts("2");
	puts("3");
	puts("4");

	pid_t pid = fork();
	if(pid == -1){
		perror("fork fail");
		exit(1);
	}
	else if(pid == 0){
		printf("%d's father is %d\n",getpid(),getppid());
	}
	else{
		printf("%d's new child is %d, its parent is %d\n",getpid(),pid,getppid());
		sleep(1);
	}

	puts("5");
	return 0;
}
