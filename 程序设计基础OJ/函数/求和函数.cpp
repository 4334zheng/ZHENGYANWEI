#include<stdio.h>

/*int sum(int begin,int end)
{
    int i;
    int sum=0;
    for(i = begin; i <= end; i++)
    {
        sum+=i;
    }
    return(sum);
}*/

int sum(int begin,int end)
{
	int i;
	int sum=0;
	for(i=begin; i<=end; i++)
	{
		sum += i;
	}
	printf("%d",sum);
}
 

int main()
{
    int x,y;
    scanf("%d %d",&x, &y);
 	sum(x,y);
    return 0;
}
