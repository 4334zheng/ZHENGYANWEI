#include<stdio.h>
#include<math.h>
int rank[15];//pos��i�� 
int vis[15];//��ǵ�i���Ƿ��߹�
int n,cnt=0;
int dfs(int pos)
{
	if(pos==n+1){
	int flag=true;
	for(int i=1;i<=n;i++)
	{
		int flag2=true;
		for(int j=i+1;j<=n;j++)
		{//ö�����������ʺ� 
			if(abs(i-j)==abs(rank[i]-rank[j]))
			{//�����ʺ���һ���Խ��� 
				flag=false;
				flag2=false;
				break;
			}
		}
		if(flag2==false) break;//���һ����������Խ��������������ϣ���ֱ������ѭ�� 
	}
		if(flag) cnt++;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{//ö��ÿһ�� 
		if(vis[i]==false)
		{//��i��û�߹� 
			rank[pos]=i;//pos����i�� 
			vis[i]=true;
			dfs(pos+1);//�ݹ���һ�� 
			vis[i]=false;
		}
	}
}

int main()
{
	while(scanf("%d\n",&n)!=0)
	{
		dfs(1);//�ӵ�һ�п�ʼö�� 
		printf("%d",cnt);
	}
	return 0;
}
