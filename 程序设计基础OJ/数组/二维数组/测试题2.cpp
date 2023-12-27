#include<stdio.h>
int main()
{
      int i,j,a[3][3]={1,2,3,4,5,6,7,8,9},t;
      for(i=0;i<3;i++)
     {
          t=a[0][i];
          for(j=1;j<3;j++)
               if(a[j][i]>t)
                      t=a[j][i];
          printf("%3d",t);
     }
      printf("\n");
}


