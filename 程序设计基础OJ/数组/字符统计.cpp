#include<stdio.h>
int main()
{
	int number[26]={0},i;
	char ch;
	while((ch=getchar())!='\n')
		{ 
		if(ch>='A'&&ch<='Z') number[ch-'A']++;
		} 
		//Ϊʲô��ch-'A'? 
		//��ʾ26����ĸ��0��ʼ��25��ÿһ�����ֵĴ�����ch-'A'��ʾĳ����ĸ��A�ľ��루��0~25�� 
		for(i=0;i<26;i++)
		{
			if(i%5==0) printf("\n");
			printf("%c(%d)",'A'+i,number[i]);
		}
		printf("\n");
	
	return 0;
}
