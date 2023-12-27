#include <stdio.h>
#include <math.h>

int r[11];
int c[11];
int count,n;

int generate(int x)
{
    if(x==n+1)
    {
        int flag=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<x;j++)
            {
                if(abs(i-j)==abs(c[i]-c[j]))
                {
                    flag=0;
                    break;
                }
            }
        }
        if(flag)
        {
            count++;
        }
        return 0;
    }
    for(int x=1; x<=n; x++)
    {
        if(r[x]==0)
        {
            c[x]=x;
            r[x]=1;
            generate(x+1);
            r[x]=0;
        }
    }
}

int main()
{
	while(1)
	{
		scanf("%d",&n);
		if(n==0) return 0;
  	  	for(int m=0;m<=n;m++)
   		{
   	 		r[m]=0;
    	}
    	count=0;
   		generate(1);
    	printf("%d\n",count);
	}
    return 0;
}

