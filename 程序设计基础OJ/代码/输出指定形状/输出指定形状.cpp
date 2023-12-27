#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int i=0,sum=0; 
	int x=0;
    
	while(x<n) 
    {
    	int i=0;
    	while(i<sum){
    		printf(" "); 
    		i++;
		}
		i=0;
		while(i<n){
			printf("#");
			i++;
		}
    	x++;
    	sum++;
        printf("\n");
    }
    
	return 0;
 } 
