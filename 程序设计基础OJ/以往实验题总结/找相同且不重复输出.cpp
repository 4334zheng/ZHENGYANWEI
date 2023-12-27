#include<stdio.h>
int main(void)
{
 	int a[6],b[8],c[6],d[6];
	int i,j,k = 0;
 	for(i=0;i<6;i++)
 	{
 	 	scanf("%d",&a[i]);
 	}
 	for(i=0;i<8;i++)
 	{
  		scanf("%d",&b[i]);
 	}
 	for(i=0;i<6;i++)
 	{
  		int cnt = 0;
  		for(j=0;j<8;j++)
  		{
   			if(a[i]==b[j]){
    			cnt++;
    			break;
   			}
  		}
  		if(cnt==1){
   			c[k] = a[i];
   			d[k] = 1;
   			k++;
  		}
 	}
 	for(i=0;i<k;i++)
 	{
  		for(j=i+1;j<k;j++)
  		{
   			if(c[i] == c[j]){
    		d[j] = 0;
   			}
  		}
 	}
 
 	printf("%d ",c[0]);
 	for(i=1;i<=k;i++){
  		if(d[i]){
   			printf("%d ",c[i]);
  		}
 	}
 	return 0;
} 
