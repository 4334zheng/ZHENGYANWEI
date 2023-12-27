#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		char str1[10],str2[10];
		scanf("%s",str1);
		scanf("%s",str2);
		int i,j,a1,a2;
		int cnt=0;
		int sum1=0,sum2=0,sum;
		for(i=strlen(str1)-1,j=0;i>=0;i--)
		{
			if(str1[i]>='0'&&str1[i]<='9') a1=str1[i]-48;
			else if(str1[i]>='A'&&str1[i]<='F') a1=str1[i]-55;
			else {
				cnt=1;
				break;
			}
			sum1=sum1+a1*pow(16,j++);
		}
		if(cnt==0)
		{
			for(i=strlen(str2)-1,j=0;i>=0;i--)
			{
	 			if(str2[i]>='0'&&str2[i]<='9') a2=str2[i]-48;
				else if(str2[i]>='A'&&str2[i]<='F') a2=str2[i]-55;
				else {
					cnt=1;
					break;
				}
				sum2=sum2+a2*pow(16,j++);
			}
		}
		if(cnt) printf("-1\n");
		else {
			sum=sum1+sum2;
			printf("%d\n",sum);
		}
	}
	return 0;
}
