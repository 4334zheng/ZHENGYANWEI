#include<stdio.h>
#include<string.h>
int isPalindrome(char s[1000])
{
    int len;
    len=strlen(s);
    int i,cnt;
    for(i=0;i<len;i++)
    {
        if(s[i]!=s[len-1-i]) 
        {
            cnt=0;
            break;
        }
    }
    if(i==len) cnt=1;
    return cnt;
} 
int main()
{
    int T,t;
    scanf("%d",&T);
    for(t=0;t<T;t++)
    {
        char str[1000];
        scanf("%s",str);
        if(isPalindrome(str)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
