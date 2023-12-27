#include<stdio.h>
int main()
{
	int I;
	int jiangjin;
	scanf("%d",&I); 
	if(I<=100000) jiangjin=I*10/100;
	if(100000<I&&I<=200000)jiangjin=(I-100000)*7.5/100+10000;
	if(200000<I&&I<=400000)jiangjin=(I-200000)*5/100+17500;
	if(400000<I&&I<=600000)jiangjin=(I-400000)*3/100+27500;
	if(600000<I&&I<=1000000)jiangjin=(I-600000)*1.5/100+33500;
	if(I>1000000)jiangjin=(I-1000000)*1/100+39500;
	printf("%d\n",jiangjin);
	return 0; 
}
