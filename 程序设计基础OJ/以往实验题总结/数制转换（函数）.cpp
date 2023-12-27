#include<stdio.h>
#include<math.h>
#include<string.h>

long change(char s[]) 
{
	int i,j=0;
	int len,a;
	int sum=0;
	len = strlen(s);
	for(i=len-1;i>=0;i--)
	{ 
		if(s[i]>='0'&&s[i]<='9') a=s[i]-48;
		if(s[i]>='A'&&s[i]<='Z') a=s[i]-55;
		sum+=a*pow(16,j++);
	} 
	return sum;
}

int main()
{
	int t,T;
	char str[1000];
	scanf("%d\n",&T);
	for(t=1;t<=T;t++)
	{
		scanf("%s",str);
		printf("%d\n",change(str));
	}
	return 0;
}
