#include<stdio.h>
int move(char getone,char putone)
{
	printf("%c->%c\n",getone,putone);
} 

int hanio(int n,char one,char two,char three)
{
	if(n==1) move(one,three);
	else
	{
		hanio(n-1,one,three,two);
		move(one,three);
		hanio(n-1,two,one,three); 
	}
}

int main()
{
	int m;
	printf("Input the number of disks:");
	scanf("%d",&m);
	printf("The steps to moving %3d disks:\n",m);
	hanio(m,'A','B','C');
	return 0;
}
