#include<stdio.h>
#include<cmath>
using namespace std; 

int judge_same(int a[6])
{
   	int i,flag=0;
   	for(i=1;i<6;i++)
   	{
   		if(a[i]==a[i-1]&&flag==0)flag=1;
    	else if(a[i]==a[i-1]&&flag)return 0;
    	else flag=0;
   	}
   	return 1;
} 

int judge_b(int a[6]) 
{
  	int i;
  	for(i=1;i<6;i++)
  	{
   		if(abs(a[i]-a[i-1])>4)return 0;
  	}
  	return 1;
}

int spe(int n) 
{
   	int a[6];
   	for(int i=0;i<6;i++,n/=10)
  	{ 
   	 	a[i]=n%10;
    	if(a[i]>6)return 0;
   	}
   	if(judge_same(a)&&judge_b(a)) return 1;
   	else return 0;

}

int main()
{
 	int T;
 	scanf("%d",&T);
 	while(T--)
 	{
  		int x,y;
  		scanf("%d %d",&x,&y);
  		while(x<=y)
  		{
   			if(spe(x))
   			{
   		 		printf("%.6d\n",x);
   			}
   			x++;
  		}
  		printf("\n");
 	}
 	return 0;
}
