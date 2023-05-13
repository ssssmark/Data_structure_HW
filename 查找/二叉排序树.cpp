#include<iostream>
#include<string.h>
#include<iomanip>
using namespace std;
typedef struct BSTNode {
	BSTNode *lchild, *rchild;
	int data;
	int coun;
}BSTNode,*BSTree;
BSTree T;
BSTree search(BSTree &T, int target,BSTree &front)
{
	if (!T)
		return NULL;
	BSTree p = T;
	while (p)
	{
		if (p->data == target)
			return p;
		else {
			if (p->data > target)
			{
				front = p;
				p = p->lchild;
			}
				
			else
			{
				front = p;
				p = p->rchild;
			}
				
		}
	}
	return NULL;
}
void insertBST(BSTree& T,int x)
{
	if (!T)
	{
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = x;
		T->coun = 1;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else
	{
		BSTree q=new BSTNode;
		BSTree p=search(T, x,q);
		if (p!= NULL)
		{
			p->coun++;
		}
		else
		{
			p = (BSTree)malloc(sizeof(BSTNode));
			p->data = x;
			p->lchild = NULL;
			p->rchild = NULL;
			p->coun = 1;
			BSTree s = T;
			int flag = 0;
			while (1)
			{
				if (p->data < s->data)
				{
					if (s->lchild != NULL)
						s = s->lchild;
					else
					{
						flag = 1;
						break;
					}
				}
					
				else if (p->data > s->data)
				{
					if (s->rchild != NULL)
						s = s->rchild;
					else
					{
						flag = 2;
						break;
					}
				}
			}
			
			if (flag == 1)
			{
				s->lchild = p;
			}
			else if (flag == 2)
			{
				s->rchild = p;
			}
		}
	
	}
}
void deletenode(BSTree& T, int x)
{
	BSTree q= (BSTree)malloc(sizeof(BSTNode));
	BSTree p = search(T, x,q);
	if (p == NULL)
	{
		cout << "None" << endl;
		return;
	}
	else {
		p->coun--;
		if (p->coun == 0)
		{
			
			if (p->lchild == NULL && p->rchild == NULL)
			{
				if (q->lchild == p)
				{
					q->lchild = NULL;
				}
				else if (q->rchild == p)
				{
					q->rchild = NULL;
				}
			}
			else if (p->lchild == NULL )
			{
				q = p;
				p = p->rchild;
				/*free(q);*/
			}
			else if (p->rchild == NULL)
			{
				q = p;
				p = p->lchild;
				/*free(q);*/
			}
			else {
				BSTree s=p->lchild;
				q = p;
				while (s->rchild)
				{
					q = s;
					s = s->rchild;
				}
				p->data = s->data;
				p->coun = s->coun;
				if (q != p)
				{
					q->rchild = s->lchild;
				}
				else q->lchild = s->lchild;
				delete s;
			}
		}
	}
}
void getmin(BSTree& T)
{
	BSTree p = T;
	if (!T)
	{
		cout << -1 << endl;
		return;
	}
	while (p->lchild)
	{
		p = p->lchild;
	}
	cout << p->data << endl;
}
void getprior(BSTree &T,int x)
{
	BSTree q=new BSTNode;
	BSTree p = search(T, x, q);
	BSTree minx = T;
	if (T)
	{
		while (minx->lchild)
		{
			minx = minx->lchild;
		}
		if (p == minx)
		{
			cout << "None" << endl;
			return;
		}
	}
     if (p == NULL)
	{
		BSTree min = T;
		while (min->lchild)
		{
			min = min->lchild;
		}
		if (x < min->data)
			cout << "None" << endl;
		else
		{
			BSTree m = T;
			while (1)
			{
				if (m->data < x)
				{
					if (m->rchild != NULL)
						m = m->rchild;
					else
					{
						cout << m->data << endl;
						break;
					}
				}

				else if (m->data > x)
				{
					if (m->lchild != NULL)
						m = m->lchild;
					else
					{
						getprior(T, m->data);
						break;
					}
				}
			}
		}
		return;
	}
	else {
		if (p->lchild!= NULL)//如果有左子树
		{
			BSTree s = p->lchild;
			while (s->rchild)
			{
				s = s->rchild;
			}
			cout << s->data << endl;
		}
		else {
			if (p == q->rchild)
			{
				cout << q->data << endl;
			}
			else if (p == q->lchild)
			{
				while (1)
				{
					BSTree front=new BSTNode;
					BSTree ret=search(T, q->data, front);
					if (front == T&&front->lchild==q||front==NULL)
					{
						cout << "None" << endl;
						break;
					}
					if (front->rchild == q)
					{
						cout << front->data << endl;
						break;
					}
					else
						q = front;
					
				}
			}
		}
	}
}
void getcoun(BSTree& T, int x)
{
	BSTree q;
	BSTree p = search(T, x, q);
	if (p == NULL)
	{
		cout << 0 << endl;
	}
	else cout << p->coun<<endl;
}
int main()
{
	int num;
	cin >> num;
	for (int i = 0;i < num;i++)
	{
		int op;
		cin >> op;
		switch (op)
		{
		case 1:int x1;
			cin >> x1;
			insertBST(T, x1);
			break;
		case 2:int x2;
			cin >> x2;
			deletenode(T, x2);
			break;
		case 3:int x3;
			cin >> x3;
			getcoun(T, x3);
			break;
		case 4:getmin(T);
			break;
		case 5:int x5;
			cin >> x5;
			getprior(T, x5);
			break;
		}
	}
	return 0;
}

