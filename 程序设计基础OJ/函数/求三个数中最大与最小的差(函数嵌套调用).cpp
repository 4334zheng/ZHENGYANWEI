#include<stdio.h>
//ѧϰ��������Сֵ���㷨�� 
int max(int x,int y,int z)
{
	int r;
	r=x>=y?x:y;
	return(r>=z?r:z); 
} 
int min(int x,int y,int z)
{
	int r;
	r=x<y?x:y;
	return(r<z?r:z); 
}
int dif(int x,int y,int z)
{
	return(max(x,y,z)-min(x,y,z));
}
int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	printf("Max-Min=%d\n",dif(a,b,c));
	return 0;
}
