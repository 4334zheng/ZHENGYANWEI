#include<stdio.h>
int main()
{   
	int a[8],b[8],c[8];
    int i,j,cnt,k=0;
 	for(i=0;i<8;i++)
	{
        scanf("%d",&a[i]);//�����һ���� 
 	}
 	for(i=0;i<8;i++)
	{
  		scanf("%d",&b[i]);
	}//����ڶ����� 
	for(i=0;i<8;i++)
  		for(j=0,cnt=1;j<8;j++)
		{
   			if(b[i]==a[j]&&cnt)c[k]=b[i],k++;//�������ͬ�ĸ�ֵ��c�������
  		}
 		if(k>=1)
 		{
 			printf("%d\n",c[0]);//��һ����һ�����ظ���ֱ����� 	
		 }
	for(i=1;i<k;i++)
	{
  		for(j=0,cnt=1;j<i;j++)
		{
   			if(c[i]==c[j])cnt=0;//c���a,b��������������ͬ������c������ͬ���������ظ���� 
  		}
		if(cnt)printf("%d\n",c[j]);
 	} 
   	return 0;
}
