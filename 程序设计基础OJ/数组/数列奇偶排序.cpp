#include<stdio.h>
int main()
{
	int i,j,cnt1,cnt2,t,k;
	scanf("%d",&k);
	while(k--)
	{
		scanf("%d",&i);
		int a[i];
		for(j=0;j<i;j++)
		{
			scanf("%d",&a[j]);
		}
		cnt1=-1;
		cnt2=i;
		while(1)
		{
			while(a[++cnt1]%2==0);
			while(a[--cnt2]%2==1);
			if(cnt1>cnt2) break;
			t=a[cnt1];
			a[cnt1]=a[cnt2];
			a[cnt2]=t;
		}
		
		printf("%d ",i);
		for(j=0;j<i;j++)
		{
			printf("%d",a[j]);
			if(j!=i-1) printf(" ");
		}
		printf("\n");
	}
	return 0;
}
