#include<stdio.h>
#include<string.h>
  
int del_char(char a[],char ch)
{
    int len;
    len=strlen(a);
    char b[len];
    int i,j=0;
    for(i=0;i<=len;i++)
    {
        if(a[i]!=ch)
        {
            b[j]=a[i];
            j++;
        }
    }
    printf("%s\n",b);
    return(b[j]);
} 
  
int main()
{
    char a[100];
    char ch;
    scanf("%c\n",&ch);
    scanf("%s",a);
    del_char(a,ch);
    return 0;
}
