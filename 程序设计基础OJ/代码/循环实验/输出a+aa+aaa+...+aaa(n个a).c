#include<Stdio.h>
int main()
{
	int a,n,i;
	scanf("%d\n%d",&a,&n);
	int b=a;
	if(n==0) printf("0\n");
	else 
	{
		int sum=a;
		for(i=1;i<n;i++)
		{
			a=a*10+b;
			sum+=a;
		}
		printf("%d\n",sum);
	}
	return 0;
}
