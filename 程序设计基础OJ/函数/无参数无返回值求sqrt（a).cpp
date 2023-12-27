#include<stdio.h>
#include<math.h>
int showerror();
int main()
{
	int a;
	scanf("%d",&a);
	while(a<0)
	{
		showerror();
		scanf("%d",&a);
	}
	printf("sqrt(a)=%.2f\n",sqrt(a));
}
int showerror()
{
	printf("input error!\n");
}
	
