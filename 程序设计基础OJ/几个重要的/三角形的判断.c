#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,c;
	scanf("%lf\n%lf\n%lf",&a,&b,&c);
	if(a+b>c&&b+c>a&&a+c>b)
	{
		if(fabs(a-b)<0.001||fabs(a-c)<0.001||fabs(b-c)<0.001)
		{
			if(a==b&&b==c)
		    printf("�ȱ�������\n");
		    else
			{
		    	if(fabs(a*a+b*b-c*c)<0.001||fabs(b*b+c*c-a*a)<0.001||fabs(a*a+c*c-b*b)<0.001)
			    printf("����ֱ��������\n");
			    else printf("����������\n");
			}
		
		}
		else printf("��ͨ������\n");
	} 
	else printf("��������\n");
	 return 0;
}
