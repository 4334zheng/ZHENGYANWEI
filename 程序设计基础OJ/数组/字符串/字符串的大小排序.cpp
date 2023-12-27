#include<stdio.h>
#include<string.h>
int main()
{
	char str1[100],str2[100],str3[100];
	scanf("%s %s %s",str1,str2,str3);
	if(strcmp(str1,str2)!=-1&&strcmp(str2,str3)!=-1) printf("%s\n%s\n%s",str3,str2,str1);
   	else if(strcmp(str1,str3)!=-1&&strcmp(str3,str2)!=-1) printf("%s\n%s\n%s",str2,str3,str1);
	else if(strcmp(str2,str1)!=-1&&strcmp(str1,str3)!=-1) printf("%s\n%s\n%s",str3,str1,str2);
	else if(strcmp(str2,str3)!=-1&&strcmp(str3,str1)!=-1) printf("%s\n%s\n%s",str1,str3,str2);
	else if(strcmp(str3,str2)!=-1&&strcmp(str2,str1)!=-1) printf("%s\n%s\n%s",str1,str2,str3);
	else if(strcmp(str3,str1)!=-1&&strcmp(str1,str2)!=-1) printf("%s\n%s\n%s",str2,str1,str3);	
	return 0;
} 
	//为避免重复输出，可以使用else if语句；或者使用标志变量flag；或者每个语句都用return 0或exit（0）结束程序；
	//标志变量使用方法：flag 初始化为0，一旦if满足就赋值为1，在if的条件里加上flag==0这一个条件 
