#include<stdio.h>
#include<string.h>

int isPalindrome(char s[]) 
{
	int i,cnt;
	int len;
	len = strlen(s);
	for(i=0;i<len;i++) 
	{ 
		if(s[i]!=s[len-i-1]) 
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
	char str[100];
	int t,T;
	scanf("%d\n",&T);
	for(t=1;t<=T;t++) 
	{ 
		scanf("%s",str);
		if(isPalindrome(str)) printf("Yes\n");
		else printf("No\n");
	} 
	return 0;
}
