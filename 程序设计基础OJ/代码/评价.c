#include<stdio.h>
int main()
{
	char ch;
	scanf("%c",&ch);
	switch(ch)
	{
		case'A':printf("一个学期的努力给你带来了应有的收获\n");break;
		case'B':printf("你与成功还缺少了一点契机\n");break;
		case'C':printf("保底已到，力争上游\n");break;
		case'D':printf("失败与你只是一步之遥，莫一失足成千古恨\n");break;
		case'F':printf("一次失败代表不了什么，请从头再来\n");break; 
	}
	return 0;
}
