#include<iostream>
using namespace std;

typedef struct node {
	char data;
	struct node* child, * bro;
}TR;

//创建二叉树，传入的数据是二叉链表的先序遍历结果和中序遍历结果
TR* createTR(char* in, char* pre, int k) {
	if (k <= 0)
		return NULL;
	else
	{
		TR* node = new TR;
		node-> data = pre[0];
		int i;
		for (i = 0; in[i] != pre[0]; ++i);
	}
}