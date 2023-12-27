#include<stdio.h>
#include<string.h>
 
int judge(char str[40])
{
    int a;
    int i;
    int cnt=0;
    a=strlen(str);
    if(a>31) cnt=0;
    else
    {
        if(str[0]!='_'&&(str[0]>'z'||str[0]<'a')&&(str[0]<'A'||str[0]>'Z')) cnt=0;
        else
        {
            for(i=1;i<a;i++)
                if(('A'<=str[i]&&str[i]<='Z')||('a'<=str[i]&&str[i]<='z')||('0'<=str[i]&&str[i]<='9')||str[i]=='_') cnt=1;
                else{
                    cnt=0;
                    break;
                }
        } 
    }
    return cnt;
}
 
int main()
{
    int T,t;
    scanf("%d\n",&T);
    for(t=1;t<=T;t++)
    {
        char s[100];
        gets(s);
        if(judge(s)) printf("YES\n");
        else printf("NO\n"); 
    }
    return 0;
}
