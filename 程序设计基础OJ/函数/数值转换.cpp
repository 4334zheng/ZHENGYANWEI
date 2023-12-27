#include<stdio.h>
#include<string.h>
#include<math.h>
long change(char s[100])
{
    int i,j,a;
    int sum=0;
    for(i=strlen(s)-1,j=0;i>=0;i--)
    {
        if(s[i]>='0'&&s[i]<='9') a=s[i]-48;
        if(s[i]>='A'&&s[i]<='F') a=s[i]-55;
        sum=sum+a*pow(16,j++);
    }
    return sum;
}
 
int main()
{
    int T,t;
    scanf("%d",&T);
    for(t=1;t<=T;t++)
    {
        char str[100];
        scanf("%s",str);
        printf("%d\n",change(str));
    }
    return 0;
}
