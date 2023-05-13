/*如果已知中序遍历的栈的操作序列，就可唯一地确定一棵二叉树。请编程输出该二叉树的后序遍历序列。
提示：本题有多种解法，仔细分析二叉树非递归遍历过程中栈的操作规律与遍历序列的关系，可将二叉树构造出来。

输入
第一行一个整数n，表示二叉树的结点个数。
接下来2n行，每行描述一个栈操作，格式为：push X 表示将结点X压入栈中，pop 表示从栈中弹出一个结点。
(X用一个字符表示)

输出
一行，后序遍历序列。*/
#include<iostream>
#include<iomanip>
using namespace std;
typedef int Status;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
typedef struct BiNode {
	char data;
	struct BiNode* lchild, * rchild;
}BiNode,*BiTree;
BiTree T;
char sq[200] = {};
int c = 0;
Status CreateBiTree(BiTree& T,int n)
{
	static int i = 0;
	char a = sq[i];
	i++;
	/*if (i == 2 * n - 1)
		return OK;*/
	if (a == ' ')
	{
		T = NULL;
	}
	else {
		if (!(T = (BiNode*)malloc(sizeof(BiNode))))
			exit(OVERFLOW);
		T->data = a;
		CreateBiTree(T->lchild,n);
		CreateBiTree(T->rchild,n);
	}
	return OK;
}
Status visit(char a)
{
	cout << a;
	return OK;
}
Status PostorderTraverse(BiTree& T)
{
	if (T == NULL)
		return 0;
	PostorderTraverse(T->lchild);
	PostorderTraverse(T->rchild);
	visit(T->data);	
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0;i < 2 * n;i++)
	{
		string s;
		cin >> s;
		if (s == "push")
		{
			char a;
			cin >> a;
			sq[c] = a;
			c++;
		}
		else if (s == "pop")
		{
			sq[c] = ' ';
			c++;
		}
	}
	sq[2 * n] = ' ';
	CreateBiTree(T,n);
	PostorderTraverse(T);
	return 0;

}