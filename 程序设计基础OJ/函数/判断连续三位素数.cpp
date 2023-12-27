#include<stdio.h>
#include<math.h>

int judge(int x)
{
	int j;
	int cnt;
	for(j=2;j<=sqrt(x);j++)
	{
		if(x%j==0)
		{
			cnt=0;
			break;
		}
		else continue;
	}
	if(j>sqrt(x))
	{
		cnt=1;
	}
	return cnt;
}

int main()
{
	int n;
	scanf("%d",&n);
	int i,a,b;
	int tag=1;
	if(n==1) printf("No triple\n");
	else{
		for(i=3;(i+4)<=n;i+=2)
		{
			a=i+2;
			b=i+4;
			if(judge(i)&&judge(a)&&judge(b))
			{
				printf("%d %d %d\n",i,a,b);
				tag=0;
			} 
		} 
		if((i+4)>n&&tag)
		{
			printf("No triple\n");
		}
	}
	return 0;
} 
