#include<stdio.h>
int main()
{
      int k,a[3][3]={1,2,3,4,5,6,7,8,9};
      for(k=0;k<3;k++)
           printf("%3d",a[k][2-k]);
      printf("\n");
}
