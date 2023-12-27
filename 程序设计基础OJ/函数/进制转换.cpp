#include<stdio.h>
#include<string.h>
#include<math.h>

long change(char s[])
{
	int i,j,a;
	int sum=0;
	for(i=strlen(s)-1,j=0;i>=0;i--)
	{
		if(s[i]>='0'&&s[i]<='9') a=s[i]-48;
		if(s[i]>='A'&&s[i]<='Z') a=s[i]-55;
		sum+=a*pow(16,j++);
	}
	printf("%d\n",sum);
	return(sum);
}

int main()
{
	int t,T;
	char s[1000];
	scanf("%d\n",&T);
	for(t=0;t<T;t++)
	{
		scanf("%s",s);
		change(s);
	}
	return 0;
}
