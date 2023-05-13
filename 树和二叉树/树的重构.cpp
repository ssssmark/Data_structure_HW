#include<iostream>
#include<iomanip>
using namespace std;
typedef int Status;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
typedef struct CSNode {
	char data;
	struct CSNode* firstchild, * nextsibling,*parent;
}CSNode, * CSTree;
CSTree T;
Status InitCSTree(CSTree& T)
{
	T = (CSNode*)malloc(sizeof(CSNode));
	if (!T)
		exit(OVERFLOW);
	T->data = '*';
	T->parent = NULL;
	T->firstchild = NULL;
	T->nextsibling = NULL;
	return OK;
}
Status CreateCSTree(CSTree &T, string s)
{
	int i = 0;
	int count = 0;
	CSTree p = T;
	CSTree q = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == 'd')
		{
			if (p->firstchild == NULL)
			{
				q = (CSNode*)malloc(sizeof(CSNode));
				if (!q)
					exit(OVERFLOW);
				q->data = '*';
				q->parent = p;
				q->firstchild = NULL;
				q->nextsibling = NULL;
				p->firstchild=q;
				p = q;
			}
			else {
				q->nextsibling = (CSNode*)malloc(sizeof(CSNode));
				if (!q->nextsibling)
					exit(OVERFLOW);
				q = q->nextsibling;
				q->parent = p;
				q->data = '*';
				q->firstchild = NULL;
				q->nextsibling = NULL;
				p = q;
			}
		}
		else if (s[i] == 'u')
		{
			if (q != p)
				q = q->parent;
			p = p->parent;
		}
		i++;
	}
	return OK;
}
int depth_BiTree(CSTree& T)
{
	if (T == NULL)
		return 0;
	else {
		int i = depth_BiTree(T->firstchild);
		int j = depth_BiTree(T->nextsibling);
		if (i > j)
			return i+1;
		else return j+1;
	}
}
int depth_CSTree(CSTree& T)
{
	
	if (T == NULL)
			return 0;
		int firstchild_depth = depth_CSTree(T->firstchild);
		int nextsibling_depth = depth_CSTree(T->nextsibling);

		return (firstchild_depth + 1 > nextsibling_depth ? firstchild_depth + 1 : nextsibling_depth);
	
}
int main()
{
	string s;
	int i = 1;
	while (1)
	{
		cin >> s;
		if (s == "#")
			break;
		InitCSTree(T);
		CreateCSTree(T, s);
		cout << "Tree " << i << ": " << depth_CSTree(T)-1 << " => " << depth_BiTree(T)-1<<endl;
		i++;
	}
	return 0;

}
