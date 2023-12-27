#include<stdio.h>
int main()
{
	int t;
	scanf("%d",&t);
	int i=0;
	int n;
	int cum;
	for(i=0;i<t;i++)
	{
		scanf("%d",&n);
		for(cum=0;n!=1;){
			if(n%2==0) {n=n/2;cum+=1;}
	    	else {n=3*n+1;cum+=1;}
		}
		printf("%d",cum);
		if(i!=t-1) printf(" ");
	}
	return 0;
}
