#include<stdio.h>
#include<string.h> 
int main()
{
	char s1[]="hello world!";
	char s2[]={'h','e','l','l','o',' ','w','o','r','l','d','!'};
	printf("%s %d\n",s1,sizeof(s1));
	printf("%s %d\n",s2,sizeof(s2));
	//sizeof:数组长度 
	printf("%s\n",s2);//输出s2 
	printf("%d\n",strlen(s1));//输出字符串长度 不包括结束符'\0' 
	printf("%d\n",strlen(s2));
	return 0;
 } 
