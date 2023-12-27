#include<stdio.h>
int main()
{
	int number[26]={0},i;
	char ch;
	while((ch=getchar())!='\n')
		{ 
		if(ch>='A'&&ch<='Z') number[ch-'A']++;
		} 
		//为什么是ch-'A'? 
		//表示26个字母从0开始到25，每一个出现的次数，ch-'A'表示某个字母到A的距离（即0~25） 
		for(i=0;i<26;i++)
		{
			if(i%5==0) printf("\n");
			printf("%c(%d)",'A'+i,number[i]);
		}
		printf("\n");
	
	return 0;
}
