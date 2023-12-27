#include<stdio.h>
#include<math.h>

int judge_same(int a[6])
{
	int i,cnt;
	for(i=0;i<4;i++)
	{
		if(a[i]==a[i+1]&&a[i+1]==a[i+2])
		{
			cnt=0;
			break;
		}
		if(i==4) cnt=1;
	} 
	return cnt;
} 

int judge_b(int a[6])
{
	int i,cnt;
	int x;
	for(i=0;i<5;i++)
	{
		x=fabs(a[i]-a[i+1]);
		if(x>=4)
		{
			cnt=0;
			break;
		}
		if(i==5) cnt=1;
	}
	return cnt;
}

int spe(int n) 
{
	int a[6];
	int flag;
	int i,j;
	for(i=0;i<6;n/=10,i++)  
	{
		a[i]=n%10; 
		if(a[i]>6) return 0;
	} 
	if(judge_same(a)&&judge_b(a)) flag=1;
	else flag=0;
	return flag;
}

int main()
{
	int t,T;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		int k;
		for(k=x;k<=y;k++)
		{
			if(spe(k))
			{
				printf("%.6d\n",k);
			}
		}
		printf("\n");
	}
	return 0;
}
