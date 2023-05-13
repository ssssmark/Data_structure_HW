#include<iostream>
using namespace std;
#define OVERFLOW 3
typedef struct BiThrNode
{
	char data;
	struct BiThrNode* lchild, * rchild;      /*���Һ���ָ��*/
	int LTag, RTag;             			    /*���ұ�־*/
}BiThrNode, * BiThrTree;
BiThrTree pre=new BiThrNode;
char ans[1000000] = {};
void CreateBiTree(BiThrTree& T)
{
	char ch;
	/*�������������������н���ֵ(һ���ַ�)���������������ʾ�Ķ�����T*/
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
/*�Խ��pΪ������������������*/
void InThrding(BiThrTree p)
{
	
	/*pre��ȫ�ֱ�������ʼ��ʱ���Һ���ָ��Ϊ�գ���������������㿪ʼ������*/
	if (p)
	{
		InThrding(p->lchild);            /*�������ݹ�������*/
		if (!(p->lchild))                      /*p������Ϊ��*/
		{
			p->LTag = 1;                     /*��p����������*/
			p->lchild = pre;                 /*p������ָ��ָ��pre(ǰ��)*/
		}
		else
		{
			p->LTag = 0;
		}
		if (!(pre->rchild))                  /*pre���Һ���Ϊ��*/
		{
			pre->RTag = 1;                  /*��pre����������*/
			pre->rchild = p;                /*pre���Һ���ָ��ָ��p(���)*/
		}
		else
		{
			pre->RTag = 0;
		}
		pre = p;                            /*����preָ��p��ǰ��*/
		InThrding(p->rchild);           /*�������ݹ�������*/
	}
}
/*��ͷ��������������*/
void InOrderThrding(BiThrTree& Thrt, BiThrTree T)
{
	/*�������������T��������������������Thrtָ��ͷ���*/
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));  		/*��ͷ��ͷ*/
	if (!Thrt)
		exit (OVERFLOW);
	Thrt->LTag = 0;               /*ͷ��������ӣ������ǿգ���������Ϊ����*/
	Thrt->RTag = 1;               /*ͷ�����Һ���ָ��Ϊ������*/
	Thrt->rchild = Thrt;          /*��ʼ��ʱ��ָ��ָ���Լ�*/
	if (!T) Thrt->lchild = Thrt;   /*����Ϊ�գ�����ָ��Ҳָ���Լ�*/
	else
	{
		Thrt->lchild = T; pre = Thrt; /*ͷ��������ָ�����pre��ֵָ��ͷ���*/
		InThrding(T);            /*���������㷨������TΪ���Ķ�������������������*/
		pre->rchild = Thrt;        /*�㷨������preΪ���ҽ�㣬pre��������ָ��ͷ���*/
		pre->RTag = 1;
		Thrt->rchild = pre;        /*ͷ����������ָ��pre*/
	}
}
char InOrderTraverse_Thr(BiThrTree T)
{
	char last=' ';
	/*Tָ��ͷ��㣬ͷ��������lchildָ������*/
	/*�����������������T�ķǵݹ��㷨����ÿ������Ԫ��ֱ�����*/
	BiThrTree p = T->lchild;    /*pָ������*/
	while (p != T)
	{
		while (p->LTag == 0)      /*����������*/
		{
			p = p->lchild;
		}
		cout << p->data ; 
		last = p->data;/*������������Ϊ�յĽ��*/
		while (p->RTag == 1 && p->rchild != T)  /*�����������ʺ�̽��*/
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
	BiThrTree p = Thrt->lchild;    /*pָ������*/
	int flag = 0;
	while (p != Thrt)
	{
		while (p->LTag == 0)      /*����������*/
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
		while (p->RTag == 1 && p->rchild != Thrt)  /*�����������ʺ�̽��*/
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
	InOrderThrding(Thrt, T); /*��ͷ��������������*/
	char last=InOrderTraverse_Thr(Thrt);/*������������������*/
	cout << ans;
	cout << endl;
	search(Thrt, a,last);
	return 0;
}
