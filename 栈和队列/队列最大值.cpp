/******************************************************************
* ����һ�����У�������3������������

��1��Enqueue(v): v ���

��2��Dequeue(): ʹ����Ԫ��ɾ���������ش�Ԫ��

��3��GetMax(): ���ض����е����Ԫ��

�����һ�����ݽṹ���㷨����GetMax������ʱ�临�ӶȾ����ܵص͡�

Ҫ������ʱ�䲻����һ��

����
��1��1��������n, ��ʾ���е�����(�����������n��Ԫ��)
���Ŷ�����У�ÿһ��ִ��һ��������
������"dequeue"����ʾ���ӣ����ӿ�ʱ�����һ�С�Queue is Empty��;����������ӵ�Ԫ�أ�
������"enqueue m"����ʾ��Ԫ��m���,������ʱ(���ǰ������Ԫ������n��)�����"Queue is Full"�����򣬲������
������"max",������������Ԫ�أ����ӿգ����һ�С�Queue is Empty����
������"quit",�������룬��������е�����Ԫ��
����20%�����ݣ���0<=n<=100��|max(m) - min(m)|<=1e4��
����40%�����ݣ���0<=n<=6000��|max(m) - min(m)|<=1e6����δ�Ż�O(nm)��������ʱ����΢����һ�룩
����100%�����ݣ���0<=n<=10000,|max(m) - min(m)|<=1e8��
����ÿ�����Ե㣬0x80000000 <= min(m) < max(m) <= 0x7fffffff
����ÿ�����Ե㣬�����ĸ���ԼΪ���д�С��10������
��ʵ�ϣ��������ݱ�֤���ں�80%���ҵĲ����������ڿ�λ���ᳬ��15%
��������������ɼ�p101.py�����ز�����p101.py���������������
���
���У��ֱ���ִ��ÿ�β�����Ľ��
*****************************************************************/
#include<iostream>
#include<stdlib.h>
using namespace std;
#define OVERFLOW 3
#define ERROR -1
#define OK 1
typedef int Status;
typedef struct QNode {
	int data;
	struct QNode* next;
	struct QNode* prior;
}QNode, * queueptr;
typedef struct {
	queueptr front;
	queueptr rear;
}LinkQueue;
LinkQueue Q, Q1;
int coun = 0;
int maxq = 0;
Status Initqueue(LinkQueue& Q, int n)
{
	Q.front = Q.rear = (queueptr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
void enqueue(int m, LinkQueue& Q, int n)
{
	if (coun == n)
	{
		cout << "Queue is Full" << endl;

	}
	else {
		queueptr p = (queueptr)malloc(sizeof(QNode));
		if (!p)exit(OVERFLOW);
		p->data = m;
		p->next = NULL;
		Q.rear->next = p;
		Q.rear = p;
		coun++;
	}
}
void enqueueQ1(int m, LinkQueue& Q, int n)
{
	queueptr p = (queueptr)malloc(sizeof(QNode));
	if (!p)exit(OVERFLOW);
	p->data = m;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}
void DequeueQ(LinkQueue& Q)
{
	int a;
	if (Q.front == Q.rear)
	{
		cout << "Queue is Empty" << endl;
	}
	else {
		queueptr p = Q.front->next;
		Q.front->next = p->next;
		a = p->data;
		if (Q.rear == p)
			Q.rear = Q.front;
		free(p);
		cout << a << endl;
		coun--;
	}

}
void DequeueQ1(LinkQueue& Q)
{
	int a;
	if (Q.front == Q.rear)
	{
		cout << "Queue is Empty" << endl;

	}
	else {
		queueptr p = Q.front->next;
		Q.front->next = p->next;
		a = p->data;
		if (Q.rear == p)
			Q.rear = Q.front;
		free(p);
	}

}
void DequeueQ1last(LinkQueue& Q)
{
	queueptr q = Q.front;
	queueptr p = Q.rear;
	while (q->next != p)
		q = q->next;
	q->next = NULL;
	Q.rear = q;
	free(p);

}
int main()
{
	int n;
	cin >> n;
	Initqueue(Q, n);
	Initqueue(Q1, n);
	string s;
	while (1)
	{
		cin >> s;
		if (s == "dequeue")
		{
			if (Q.front != Q.rear && Q1.front != Q1.rear && Q.front->next->data == Q1.front->next->data)
			{
				DequeueQ1(Q1);
			}
			DequeueQ(Q);

		}
		else if (s == "enqueue")
		{
			int m;
			cin >> m;

			if (coun < n)
			{
				if (Q1.front == Q1.rear)
				{
					enqueueQ1(m, Q1, n);
				}
				else {
					if (Q1.front != Q1.rear)
					{
						while (Q1.rear->data < m)
						{
							DequeueQ1last(Q1);
							if (Q1.front == Q1.rear)
								break;
						}

					}
					enqueueQ1(m, Q1, n);
				}
			}
			enqueue(m, Q, n);
		}
		else if (s == "max")
		{
			if (Q.front == Q.rear)
				cout << "Queue is Empty" << endl;
			else cout << Q1.front->next->data << endl;
		}
		else if (s == "quit")
		{
			if (Q.front != Q.rear)
			{
				queueptr t = Q.front->next;
				while (t != NULL)
				{
					cout << t->data << " ";
					t = t->next;
				}
			}
			break;
		}

	}
	return 0;
}