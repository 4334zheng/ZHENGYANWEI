#include<stdio.h>
int main()
{   
	int a[8],b[8],c[8];
    int i,j,cnt,k=0;
 	for(i=0;i<8;i++)
	{
        scanf("%d",&a[i]);//输入第一组数 
 	}
 	for(i=0;i<8;i++)
	{
  		scanf("%d",&b[i]);
	}//输入第二组数 
	for(i=0;i<8;i++)
  		for(j=0,cnt=1;j<8;j++)
		{
   			if(b[i]==a[j]&&cnt)c[k]=b[i],k++;//如果有相同的赋值给c这个数组
  		}
 		if(k>=1)
 		{
 			printf("%d\n",c[0]);//第一个数一定不重复，直接输出 	
		 }
	for(i=1;i<k;i++)
	{
  		for(j=0,cnt=1;j<i;j++)
		{
   			if(c[i]==c[j])cnt=0;//c存放a,b这两个数组中相同的数，c中有相同的数，不重复输出 
  		}
		if(cnt)printf("%d\n",c[j]);
 	} 
   	return 0;
}
