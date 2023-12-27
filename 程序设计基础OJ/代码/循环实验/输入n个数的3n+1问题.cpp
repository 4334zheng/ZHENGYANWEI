#include<stdio.h>
int main()
{
	int t;
	scanf("%d",&t);
	int i=0;
	int n;
	int cum;
	while(i<t)
	{
		scanf("%d",&n);
		cum=0;
		while(n!=1){
			if(n%2==0) {n=n/2;cum+=1;}
		    else {n=3*n+1;cum+=1;}
		}
		printf("%d",cum);
    	i++;
		if(i<t) printf(" "); 
	}
	return 0;
}
