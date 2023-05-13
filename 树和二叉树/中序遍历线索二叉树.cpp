#include<iostream>
using namespace std;
#define OVERFLOW 3
typedef struct BiThrNode
{
	char data;
	struct BiThrNode* lchild, * rchild;      /*左右孩子指针*/
	int LTag, RTag;             			    /*左右标志*/
}BiThrNode, * BiThrTree;
BiThrTree pre=new BiThrNode;
char ans[1000000] = {};
void CreateBiTree(BiThrTree& T)
{
	char ch;
	/*按先序次序输入二叉树中结点的值(一个字符)，创建二叉链表表示的二叉树T*/
	cin >> ch;
	if (ch == '#') T = NULL;
	else
	{
		T = (BiThrNode*)malloc(sizeof(BiThrNode));
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
/*以结点p为根的子树中序线索化*/
void InThrding(BiThrTree p)
{
	
	/*pre是全局变量，初始化时其右孩子指针为空，便于在树的最左点开始建线索*/
	if (p)
	{
		InThrding(p->lchild);            /*左子树递归线索化*/
		if (!(p->lchild))                      /*p的左孩子为空*/
		{
			p->LTag = 1;                     /*给p加上左线索*/
			p->lchild = pre;                 /*p的左孩子指针指向pre(前驱)*/
		}
		else
		{
			p->LTag = 0;
		}
		if (!(pre->rchild))                  /*pre的右孩子为空*/
		{
			pre->RTag = 1;                  /*给pre加上右线索*/
			pre->rchild = p;                /*pre的右孩子指针指向p(后继)*/
		}
		else
		{
			pre->RTag = 0;
		}
		pre = p;                            /*保持pre指向p的前驱*/
		InThrding(p->rchild);           /*右子树递归线索化*/
	}
}
/*带头结点的中序线索化*/
void InOrderThrding(BiThrTree& Thrt, BiThrTree T)
{
	/*中序遍历二叉树T，并将其中序线索化，Thrt指向头结点*/
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));  		/*建头结头*/
	if (!Thrt)
		exit (OVERFLOW);
	Thrt->LTag = 0;               /*头结点有左孩子，若树非空，则其左孩子为树根*/
	Thrt->RTag = 1;               /*头结点的右孩子指针为右线索*/
	Thrt->rchild = Thrt;          /*初始化时右指针指向自己*/
	if (!T) Thrt->lchild = Thrt;   /*若树为空，则左指针也指向自己*/
	else
	{
		Thrt->lchild = T; pre = Thrt; /*头结点的左孩子指向根，pre初值指向头结点*/
		InThrding(T);            /*调用上述算法，对以T为根的二叉树进行中序线索化*/
		pre->rchild = Thrt;        /*算法结束后，pre为最右结点，pre的右线索指向头结点*/
		pre->RTag = 1;
		Thrt->rchild = pre;        /*头结点的右线索指向pre*/
	}
}
char InOrderTraverse_Thr(BiThrTree T)
{
	char last=' ';
	/*T指向头结点，头结点的左链lchild指向根结点*/
	/*中序遍历二叉线索树T的非递归算法，对每个数据元素直接输出*/
	BiThrTree p = T->lchild;    /*p指向根结点*/
	while (p != T)
	{
		while (p->LTag == 0)      /*沿左孩子向下*/
		{
			p = p->lchild;
		}
		cout << p->data ; 
		last = p->data;/*访问其左子树为空的结点*/
		while (p->RTag == 1 && p->rchild != T)  /*沿右线索访问后继结点*/
		{
			p = p->rchild;
			cout << p->data ;
			last = p->data;
		}
		p = p->rchild;
	}
	return last;
}
int findsucc(BiThrTree p)
{
	int flag = 0;
	if (p->RTag == 0)
	{
		BiThrTree q = p->rchild;
		while (q->LTag == 0)
			q = q->lchild;
		if (q->data!='!')
		cout<<"succ is "<< q->data << q->RTag<<endl;
		flag = 1;
	}
	else if (p->RTag == 1)
	{
		if (p->lchild->data!='!')
			cout << "succ is " << p->rchild->data << p->rchild->RTag<<endl;
			flag = 1;
	}
	return flag;
}
int findprev(BiThrTree p)
{
	int flag = 0;
	if (p->LTag == 0)
	{
		BiThrTree q = p->lchild;
		while (q->RTag == 0)
			q = q->rchild;
		if(q->data!='!')
		cout << "prev is " << q->data << q->LTag<<endl;
		flag = 1;
	}
	else if (p->LTag == 1)
	{
		if (p->lchild->data!='!')
			cout << "prev is " << p->lchild->data << p->lchild->LTag<<endl;	
			flag = 1;
	}
	return flag;
}
void search(BiThrTree& Thrt,char a,char last)
{
	BiThrTree p = Thrt->lchild;    /*p指向根结点*/
	int flag = 0;
	while (p != Thrt)
	{
		while (p->LTag == 0)      /*沿左孩子向下*/
		{
			p = p->lchild;
		}
		if (p->data == a)
		{
			flag = 1;
			if (p->rchild == Thrt)
				cout << "succ is NULL" << endl;
			else findsucc(p);
			if (p ->lchild==Thrt)
				cout << "prev is NULL"<<endl;
			else
				findprev(p);
		}
		while (p->RTag == 1 && p->rchild != Thrt)  /*沿右线索访问后继结点*/
		{

			p = p->rchild;
			if (p->data == a)
			{
				flag = 1;
				if (p->rchild == Thrt)
					cout << "succ is NULL" << endl;
				else findsucc(p);
				if (p ->lchild==Thrt)
					cout << "prev is NULL" << endl;
				else
				 findprev(p);
					
			}	
		}
		p = p->rchild;
	}
	if(flag==0)
	cout << "Not found" << endl;
}
int main()
{
	BiThrTree T;
	BiThrTree Thrt=new BiThrNode;
	Thrt->data = '!';
	CreateBiTree(T);
	/*Thrt = T;*/
	pre->RTag = 1;
	pre->rchild = NULL;
	char a;
	cin >> a;
	InOrderThrding(Thrt, T); /*带头结点的中序线索化*/
	char last=InOrderTraverse_Thr(Thrt);/*遍历中序线索二叉树*/
	cout << ans;
	cout << endl;
	search(Thrt, a,last);
	return 0;
}
