#include<stdio.h>
#include<math.h>

int main()
{
	int t;
	scanf("%d\n",&t);
	while(t--)
	{
		char c;
		int num[26]={0};
		int i,j;
		while((c=getchar())!='\n')
		{ 
			if(c>='a'&&c<='z')
			{
				num[c-'a']++;
			} 
		} 
		int t=0,l=0;
		int maxn,minn;
		for(i=1;i<26;i++)
		{
			if(num[i]>num[t])
			{
				t=i;
			}
			if(num[i]!=0&&num[i]<num[l]||num[l]==0)
			{
				l=i;
			}	
		}
		maxn=num[t];
		minn=num[l];
		int k;
		k=maxn-minn;
 		if(k==0||k==1)
 		{
 			printf("No Answer\n0\n");
		}
		else{
			for(i=2;i<=sqrt(k);i++)
			{
				if(k%i==0) 
				{
					printf("No Answer\n0\n");
					break;
				}
			}
			if(i>sqrt(k))
			{
				printf("Lucky Word\n%d\n",k);
			}
		}
	}
	return 0;
}
