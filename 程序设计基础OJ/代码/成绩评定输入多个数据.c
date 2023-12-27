#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
	float a;
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cin<<a;
		if(a>=85) cout<<'A'<<endl;
		else if(a>=75) cout<<'B'<<endl;
		else if(a>=65) cout<<'C'<<endl;
		else if(a>=60) cout<<'D'<<endl;
		else cout<<'F'<<endl; 
	}
	return 0;
 } 
