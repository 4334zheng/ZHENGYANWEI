#include<stdio.h>
#include<string.h> 
int main()
{
	char s1[]="hello world!";
	char s2[]={'h','e','l','l','o',' ','w','o','r','l','d','!'};
	printf("%s %d\n",s1,sizeof(s1));
	printf("%s %d\n",s2,sizeof(s2));
	//sizeof:���鳤�� 
	printf("%s\n",s2);//���s2 
	printf("%d\n",strlen(s1));//����ַ������� ������������'\0' 
	printf("%d\n",strlen(s2));
	return 0;
 } 
