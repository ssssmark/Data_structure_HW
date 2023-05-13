/****************************************************************
一元多项式是有序线性表的典型应用，用一个长度为m且每个元素有两个数据项（系数项和指数项）的线性表((p1,e1),(p2,e2),...,(pm,em))可以唯一地表示一个多项式。 本题实现多项式的相加和相乘运算。本题输入保证是按照指数项递增有序的。

对于%15的数据，有1<=n,m<=15

对于%33的数据，有1<=n,m<=50

对于%66的数据，有1<=n,m<=100

对于100%的数据，有1<=n,m<=2050

本题总分150分，得到100分或以上可视为满分

尚未测试极限数据

从右上角下载p77_data.cpp，编译并运行生成随机测试数据

输入
第1行一个整数m，表示第一个一元多项式的长度
第2行有2m项，p1 e1 p2 e2 ...，中间以空格分割,表示第1个多项式系数和指数
第3行一个整数n,表示第二个一元多项式的项数
第4行有2n项，p1 e1 p2 e2 ...，中间以空格分割,表示第2个多项式系数和指数
第5行一个整数，若为0,执行加法运算并输出结果，若为1，执行乘法运算并输出结果；若为2，输出一行加法结果和一行乘法的结果。
输出
运算后的多项式链表，要求按指数从小到大排列
当运算结果为0 0时，不输出。
********************************************************************/
#include<iostream>
#include<math.h>
using namespace std;
#define Status int
#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef struct LNode { //结点类型
	int coef;
	int exp;
	struct LNode* next;
}*Link, * position;
typedef struct { //链表类型
	Link head, tail; /* 分别指向线性链表中的头结点和最后一个结点 */
	Link current; //指向当前访问的结点指针
}Linklist;
Linklist L1, L2, L3, L4, result;

Status InitList(Linklist& L)
{
	L.head = (Link)malloc(sizeof(LNode));
	if (!L.head)
		exit(OVERFLOW);
	else
		L.head->next = NULL;
	L.tail = L.head;
	return OK;
}
Status creatlist(Linklist& L, int n)
{
	Link newnode;
	L.head = (Link)malloc(sizeof(LNode));
	if (!L.head)
		return ERROR;
	L.tail = L.head;
	L.tail->next = NULL;
	;
	for (int i = 0;i < n;i++)
	{
		newnode = (Link)malloc(sizeof(LNode));
		if (!newnode)
			return ERROR;
		else
		{
			cin >> newnode->coef >> newnode->exp;
			L.tail->next = newnode;
			L.tail = newnode;
		}
	}
	L.tail->next = NULL;
	return OK;
}
Status insertafter(Link& s, int a, int b)
{
	Link p;
	p = (Link)malloc(sizeof(LNode));
	if (!p)
		return ERROR;
	else
	{
		p->coef = a;
		p->exp = b;

		if (s->next == NULL)
		{
			s->next = p;
			s = p;
			s->next = NULL;
		}
		else
		{
			p->next = s->next;
			s->next = p;
		}
	}
	return OK;
}void sum(Linklist& L1, Linklist& L2, Linklist& L3)
{
	Link p1, p2, p;
	p1 = L1.head->next;
	p2 = L2.head->next;
	while (p1 && p2)
	{
		if (p1->exp == p2->exp)
		{
			int t = p1->coef + p2->coef;
			if (t != 0)
				insertafter(L3.tail, t, p1->exp);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->exp < p2->exp)
		{
			insertafter(L3.tail, p1->coef, p1->exp);
			p1 = p1->next;
		}
		else if (p1->exp > p2->exp)
		{
			insertafter(L3.tail, p2->coef, p2->exp);
			p2 = p2->next;
		}
	}
	if (p1 != NULL)p = p1;
	else p = p2;
	while (p != NULL)
	{
		insertafter(L3.tail, p->coef, p->exp);
		p = p->next;
	}
}
void cheng(Linklist& L1, Linklist& L2)
{
	Link p1 = L1.head->next;
	Link p2 = L2.head->next;
	Link pi;

	InitList(result);
	while (p2 != NULL)//L1的第一个节点和L2相乘 遍历L2,结果存入result
	{
		/*pi = (Link)malloc(sizeof(LNode));
		if (!pi)
			exit(OVERFLOW);*/
		insertafter(result.tail, p2->coef * p1->coef, p2->exp + p1->exp);
		p2 = p2->next;

	}
	pi = (Link)malloc(sizeof(LNode));
	if (!pi)
		exit(OVERFLOW);
	p1 = p1->next;
	Link q = result.head;
	pi = result.head->next;
	//L1第一个节点之后的每一个节点与L2每一项相乘，按顺序插入result
	while (p1 != NULL)
	{
		p2 = L2.head->next;
		while (p2)
		{
			pi = result.head->next;
			q = result.head;
			while (pi != NULL && pi->exp < (p1->exp + p2->exp))
			{
				pi = pi->next;
				q = q->next;
			}
			if (pi != NULL) {
				if (pi->exp == (p1->exp + p2->exp))
				{
					pi->coef += p1->coef * p2->coef;
				}
				if (pi->exp < (p1->exp + p2->exp))
				{
					insertafter(result.tail, p1->coef * p2->coef, p1->exp + p2->exp);
				}
				if (pi->exp > (p1->exp + p2->exp))
				{
					insertafter(q, p1->coef * p2->coef, p1->exp + p2->exp);
				}
			}
			else {
				if (q->exp == (p1->exp + p2->exp)) {
					q->coef += p1->coef * p2->coef;
				}
				if (q->exp < (q->exp + q->exp))
				{
					insertafter(result.tail, p1->coef * p2->coef, p1->exp + p2->exp);
				}
			}

			/*if (q->exp == (p1->exp + p2->exp) && pi == NULL) {
				q->coef += p1->coef * p2->coef;
			}
			if (pi->exp > (p1->exp + p2->exp))
			{
				insertafter(q, p1->coef * p2->coef, p1->exp + p2->exp);
			}
			if (pi->exp < (p1->exp + p2->exp))
			{
				insertafter(result.tail, p1->coef * p2->coef, p1->exp + p2->exp);
			}*/
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}
void print(Linklist L)
{
	Link p = L.head->next;
	while (p != NULL)
	{
		cout << p->coef << " " << p->exp << " ";
		p = p->next;
	}
}
int main()
{
	int m, n, k;
	cin >> n;
	InitList(L3);
	creatlist(L1, n);
	cin >> m;
	creatlist(L2, m);
	cin >> k;
	switch (k)
	{
	case 0:sum(L1, L2, L3);print(L3);break;
	case 1:cheng(L1, L2);print(result);break;
	case 2:
		cout << endl;
		sum(L1, L2, L3);
		cheng(L1, L2);
		print(L3);
		cout << endl;
		print(result);
		break;

	}
	return 0;
}
