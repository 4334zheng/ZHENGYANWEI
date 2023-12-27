#include<stdio.h>
#include<conio.h>
#include<string.h>
#define N 20

int Getnumberstr(char s[]);
int Addnumberstr(char a[],char b[],char c[]);
int lefttrim(char str[]);
int beep();
int tag=0;

//�������������ַ�֮�� 
char Addchar(char ch1,char ch2)
{
	char ch;
	//�������ַ�����Ӧ���������λ���
	ch=(ch1-'0'+ch2-'0')+tag;
	if(ch>=10) //�������10
	{
		tag=1; //�н�λ
		//����λ����10�����0*30ת�����������ַ� 
		return(ch-10+'0');
	} 
	else //���С��10 
	{
		tag=0; //û��λ 
		//����������0*30ת�����������ַ� 
		return(ch+'0'); 
	}
} 

//��ȡ�����ַ��� 
int Getnumberstr(char s[])
{
	int i=0;
	char ch;
	while(1)
	{
		ch=getch();//��ȡ������ַ� 
		if(ch=='\r') break;//�س����˳� 
		if(ch=='\b')//�˸�� 
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
	s[i]='\0';//���ַ���������־ 
} 

//�������������ַ���֮�ͣ�����C�� 
int Addnumberstr(char a[],char b[],char c[])
{
	int i,j,k;
	memset(c,' ',N+2);//��cȫ�����
	i=strlen(a)-1;
	j=strlen(b)-1;
	k=N;
	//����������������ҵ����˳�����
	while(i>=0&&j>=0)
		c[k--]=Addchar(a[i--],b[j--]);
	while(i>=0) //������û�м���
		c[k--]=Addchar(a[i--],'0');
	while(j>=0) //����û�м���
		c[k--]=Addchar(b[j--],'0');
	if(tag==1) //����н�λ��������ں��������λ
		c[k]='1';
	c[N+1]='\0'; //���ַ���������־
	lefttrim(c); //ȥ���ַ���c��ߵĿո� 
} 

// ȥ���ַ�����ߵĿո� 
int lefttrim(char str[])
{
	int i;
	//���ҵ�һ���ǿո��ַ���λ��
	for(i=0;str[i]==' ';i++)
	strcpy(str,str+i); 
}

//���� 
int beep()
{
	printf("\07");
} 

//������
int main()
{
	char a[N+1]={0},b[N+1]={0},c[N+2];
	printf("a=");
	while(strlen(a)==0) //���뱻����a 
		Getnumberstr(a);
	printf("\nb=");
	while(strlen(b)==0) //���뱻����b 
		Getnumberstr(b);
	Addnumberstr(a,b,c); //�������c 
	printf("\na+b=%s\n",c);
	return 0; 
} 
