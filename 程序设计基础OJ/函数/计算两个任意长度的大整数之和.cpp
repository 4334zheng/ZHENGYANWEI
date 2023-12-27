#include<stdio.h>
#include<conio.h>
#include<string.h>
#define N 20

int Getnumberstr(char s[]);
int Addnumberstr(char a[],char b[],char c[]);
int lefttrim(char str[]);
int beep();
int tag=0;

//计算两个数字字符之和 
char Addchar(char ch1,char ch2)
{
	char ch;
	//两数字字符所对应的数字与进位相加
	ch=(ch1-'0'+ch2-'0')+tag;
	if(ch>=10) //结果大于10
	{
		tag=1; //有进位
		//将个位数减10后加上0*30转换成其数字字符 
		return(ch-10+'0');
	} 
	else //结果小于10 
	{
		tag=0; //没进位 
		//将和数加上0*30转换成其数字字符 
		return(ch+'0'); 
	}
} 

//读取数字字符串 
int Getnumberstr(char s[])
{
	int i=0;
	char ch;
	while(1)
	{
		ch=getch();//读取输入的字符 
		if(ch=='\r') break;//回车符退出 
		if(ch=='\b')//退格符 
		{
			if(i>0)
			{
				printf("%c %c",ch,ch);
				i--;
			}
			else beep();
			continue;
		}
		if(ch<'0'||ch>'9')
		{
			beep();
			continue;
		}
		if(i<N){
			printf("%c",ch);
			s[i++]=ch;
		}
		else beep();
	}//while
	s[i]='\0';//置字符串结束标志 
} 

//计算两个数字字符串之和，放在C中 
int Addnumberstr(char a[],char b[],char c[])
{
	int i,j,k;
	memset(c,' ',N+2);//将c全部清空
	i=strlen(a)-1;
	j=strlen(b)-1;
	k=N;
	//将被加数与加数从右到左的顺序相加
	while(i>=0&&j>=0)
		c[k--]=Addchar(a[i--],b[j--]);
	while(i>=0) //被加数没有加完
		c[k--]=Addchar(a[i--],'0');
	while(j>=0) //加数没有加完
		c[k--]=Addchar(b[j--],'0');
	if(tag==1) //最后有进位，将其放在和数的最高位
		c[k]='1';
	c[N+1]='\0'; //置字符串结束标志
	lefttrim(c); //去掉字符串c左边的空格 
} 

// 去掉字符串左边的空格 
int lefttrim(char str[])
{
	int i;
	//查找第一个非空格字符的位置
	for(i=0;str[i]==' ';i++)
	strcpy(str,str+i); 
}

//响铃 
int beep()
{
	printf("\07");
} 

//主函数
int main()
{
	char a[N+1]={0},b[N+1]={0},c[N+2];
	printf("a=");
	while(strlen(a)==0) //输入被加数a 
		Getnumberstr(a);
	printf("\nb=");
	while(strlen(b)==0) //输入被加数b 
		Getnumberstr(b);
	Addnumberstr(a,b,c); //计算和数c 
	printf("\na+b=%s\n",c);
	return 0; 
} 
