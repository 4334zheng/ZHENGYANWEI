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
	//Ϊ�����ظ����������ʹ��else if��䣻����ʹ�ñ�־����flag������ÿ����䶼��return 0��exit��0����������
	//��־����ʹ�÷�����flag ��ʼ��Ϊ0��һ��if����͸�ֵΪ1����if�����������flag==0��һ������ 
