#include<stdio.h>
int fix(int a,int b)
{
	int i,j,sum1=0,sum2=0;
	int cnt;
	int str1[100],str2[100];
	j=0;
	for(i=1;i<a;i++)
	{
		if(a%i==0)  
		{
			str1[j]=i;
			j++;
		}
		else continue;
	} 
	for(i=0;i<j;i++)
	{
		sum1+=str1[i];
	}
	
	j=0;
	for(i=1;i<b;i++)
	{
		if(b%i==0)  
		{
			str2[j]=i;
			j++;
		}
		else continue;
	} 
	for(i=0;i<j;i++)
	{
		sum2+=str2[i];
	}
	if(a!=b&&(sum1==b||sum2==a)) cnt=1;
	else cnt=0;
	return cnt;
} 
int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		if(fix(a,b)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
