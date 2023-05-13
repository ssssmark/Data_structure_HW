/*�����֪���������ջ�Ĳ������У��Ϳ�Ψһ��ȷ��һ�ö���������������ö������ĺ���������С�
��ʾ�������ж��ֽⷨ����ϸ�����������ǵݹ����������ջ�Ĳ���������������еĹ�ϵ���ɽ����������������

����
��һ��һ������n����ʾ�������Ľ�������
������2n�У�ÿ������һ��ջ��������ʽΪ��push X ��ʾ�����Xѹ��ջ�У�pop ��ʾ��ջ�е���һ����㡣
(X��һ���ַ���ʾ)

���
һ�У�����������С�*/
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