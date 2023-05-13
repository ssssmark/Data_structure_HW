/******************************************************************
* 给定一个队列，有下列3个基本操作：

（1）Enqueue(v): v 入队

（2）Dequeue(): 使队首元素删除，并返回此元素

（3）GetMax(): 返回队列中的最大元素

请设计一种数据结构和算法，让GetMax操作的时间复杂度尽可能地低。

要求运行时间不超过一秒

输入
第1行1个正整数n, 表示队列的容量(队列中最多有n个元素)
接着读入多行，每一行执行一个动作。
若输入"dequeue"，表示出队，当队空时，输出一行“Queue is Empty”;否则，输出出队的元素；
若输入"enqueue m"，表示将元素m入队,当队满时(入队前队列中元素已有n个)，输出"Queue is Full"，否则，不输出；
若输入"max",输出队列中最大元素，若队空，输出一行“Queue is Empty”。
若输入"quit",结束输入，输出队列中的所有元素
对于20%的数据，有0<=n<=100，|max(m) - min(m)|<=1e4；
对于40%的数据，有0<=n<=6000，|max(m) - min(m)|<=1e6；（未优化O(nm)程序运行时间略微超过一秒）
对于100%的数据，有0<=n<=10000,|max(m) - min(m)|<=1e8；
对于每个测试点，0x80000000 <= min(m) < max(m) <= 0x7fffffff
对于每个测试点，操作的个数约为队列大小的10倍左右
事实上，测试数据保证对于后80%左右的操作，队列内空位不会超过15%
具体测试数据生成见p101.py，下载并运行p101.py生成随机测试数据
输出
多行，分别是执行每次操作后的结果
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