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
 	}//����������cnt++ 
	for (int i=1;i<=n;i++) 
	{
		c[r]=i;
		p=1;//������� 
		for(int j=1;j<r;j++) 
		{
   			if (c[j]==i||abs(j-r)==abs(c[j]-i)) //ͬһ�л�Խ�λ�� 
			{
   			 	p=0;
    			break;
   			}
		}
		if (!p)
   			continue;
  		else
   			queen(r+1);//��r���жϽ����������r+1�� 
 	}
}
int main() 
{
 	while (1) 
	{
 		scanf("%d",&n);
  		if (n==0)  return 0;
  		cnt=0;
  		queen(1);//�ӵ�һ�п�ʼ 
  		printf("%d\n",cnt);
 	}
 	return 0;
}
