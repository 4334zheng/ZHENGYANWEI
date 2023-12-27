#include<stdio.h>
#define NUM_std 5
#define NUM_course 4
int main()
{
	int i,j;
	float score[NUM_std+1][NUM_course+1]={0};//+1多留一个空间给平均成绩
	for(i=0;i<NUM_std;i++)
	for(j=0;j<NUM_course;j++)
	{
		printf("input the mark of %dth course of %dth student",j+1,i+1);
		scanf("%f",&score[i][j]);//输入第i个学生第j门课程的成绩 
	 } 
	for(i=0;i<NUM_std;i++)
	{
		for(j=0;j<NUM_course;j++)
		{
			score[i][NUM_course]+=score[i][j];
			score[NUM_std][j]+=score[i][j];
		}
		score[i][NUM_course]/=NUM_course;//第i个学生的平均成绩 
		printf("the average mark of the %dth course is %f\n",i+1,score[i][NUM_course]);
	}
	for(j=0;j<NUM_course;j++)
	{
		score[NUM_std][j]/=NUM_std;//第j门课程平均成绩
		printf("the average mark of the %dth course is %f\n",j+1,score[NUM_std][j]); 
	}
	return 0;
 } 
