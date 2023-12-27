#include<stdio.h>

int max(int m,int n)
{
	int t;
	while(n != 0)
	{
		t = m % n;
		m = n;
		n = t;
	}
	return m;
}

int min(int m,int n)
{
	int i;
	int k;
	for(i=m;;i++)
	{
		if((i%m==0)&&(i%n==0)) 
		
		{
			k=i;
			break;
		}
	}
	return k;
}

int main()
{
	int x,y;
	scanf("%d %d",&x,&y);
	printf("%d %d\n",max(x,y),min(x,y));
	return 0;
} 
