/****************************************************************
һԪ����ʽ���������Ա�ĵ���Ӧ�ã���һ������Ϊm��ÿ��Ԫ�������������ϵ�����ָ��������Ա�((p1,e1),(p2,e2),...,(pm,em))����Ψһ�ر�ʾһ������ʽ�� ����ʵ�ֶ���ʽ����Ӻ�������㡣�������뱣֤�ǰ���ָ�����������ġ�

����%15�����ݣ���1<=n,m<=15

����%33�����ݣ���1<=n,m<=50

����%66�����ݣ���1<=n,m<=100

����100%�����ݣ���1<=n,m<=2050

�����ܷ�150�֣��õ�100�ֻ����Ͽ���Ϊ����

��δ���Լ�������

�����Ͻ�����p77_data.cpp�����벢�������������������

����
��1��һ������m����ʾ��һ��һԪ����ʽ�ĳ���
��2����2m�p1 e1 p2 e2 ...���м��Կո�ָ�,��ʾ��1������ʽϵ����ָ��
��3��һ������n,��ʾ�ڶ���һԪ����ʽ������
��4����2n�p1 e1 p2 e2 ...���м��Կո�ָ�,��ʾ��2������ʽϵ����ָ��
��5��һ����������Ϊ0,ִ�мӷ����㲢����������Ϊ1��ִ�г˷����㲢����������Ϊ2�����һ�мӷ������һ�г˷��Ľ����
���
�����Ķ���ʽ����Ҫ��ָ����С��������
��������Ϊ0 0ʱ���������
********************************************************************/
#include<iostream>
#include<math.h>
using namespace std;
#define Status int
#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef struct LNode { //�������
	int coef;
	int exp;
	struct LNode* next;
}*Link, * position;
typedef struct { //��������
	Link head, tail; /* �ֱ�ָ�����������е�ͷ�������һ����� */
	Link current; //ָ��ǰ���ʵĽ��ָ��
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
	while (p2 != NULL)//L1�ĵ�һ���ڵ��L2��� ����L2,�������result
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
	//L1��һ���ڵ�֮���ÿһ���ڵ���L2ÿһ����ˣ���˳�����result
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
