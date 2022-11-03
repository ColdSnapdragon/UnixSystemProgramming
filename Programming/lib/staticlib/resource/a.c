#include<stdio.h>
#include"mymath.h"

int main()
{
	div(2,1);
	int x=2,y=3;
	printf("%d+%d=%d\n",x,y,add(x,y));
	printf("%d-%d=%d\n",x,y,sub(x,y));
	printf("%d/%d=%lf\n",x,y,div(x,y));
	return 0;
}
