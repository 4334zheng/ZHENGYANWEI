#include<stdio.h>
#include<math.h>

int isprime(int x)
{
	int i;
	int cnt;
	if(x==1) cnt=0;
	else
	{
		for(i=2;i<=sqrt(x);i++)
		{
			if(x%i==0)
			{
				cnt=0;
				break;
			}
		}
		if(i>sqrt(x)) cnt=1;
	}
	return cnt;
}

int main()
{
	int m,n;
	scanf("%d %d",&m,&n);
	int i;
	int sum=0;
	for(i=m;i<=n;i++)
	{
		if(isprime(i)) sum += i; 
	}
	printf("%d\n",sum);
	return 0;
}
