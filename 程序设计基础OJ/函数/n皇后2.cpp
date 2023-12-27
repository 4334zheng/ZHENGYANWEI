#include<stdio.h>
#include<math.h>

int cnt,c[11],n;
int p;
int queen(int r)
{ 
	if (r>n) 
	{
		cnt++;
		return 0;
 	}//满足条件，cnt++ 
	for (int i=1;i<=n;i++) 
	{
		c[r]=i;
		p=1;//假设成立 
		for(int j=1;j<r;j++) 
		{
   			if (c[j]==i||abs(j-r)==abs(c[j]-i)) //同一列或对角位置 
			{
   			 	p=0;
    			break;
   			}
		}
		if (!p)
   			continue;
  		else
   			queen(r+1);//第r行判断结束，进入第r+1行 
 	}
}
int main() 
{
 	while (1) 
	{
 		scanf("%d",&n);
  		if (n==0)  return 0;
  		cnt=0;
  		queen(1);//从第一行开始 
  		printf("%d\n",cnt);
 	}
 	return 0;
}
