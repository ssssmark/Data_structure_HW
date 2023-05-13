/*************************************************************
�˿�����Ϸ
��Ŀ����
�˿�����4�ֻ�ɫ�����ң�Spade�������ģ�Heart����÷����Club�������飨Diamond����ÿ�ֻ�ɫ��13���ƣ���Ŵ�С����Ϊ��A,2,3,4,5,6,7,8,9,10,J,Q,K��
����һ���˿��ƶѣ���������4�ֲ������
1) ��ӣ�Append�������һ���˿��Ƶ��ƶѵĵײ��������Append Club Q����ʾ���һ��÷��Q���ƶѵĵײ���
2) ��ȡ��Extract�������ƶ��г�ȡĳ�ֻ�ɫ�������ƣ����ձ�Ŵ�С����������򣬲��ŵ��ƶѵĶ����������Extract Heart����ʾ��ȡ���к����ƣ�����֮��ŵ��ƶѵĶ�����
3)��ת��Revert����ʹ�����ƶ�����
4)������Pop��������ƶѷǿգ����ȥ�ƶѶ����ĵ�һ���ƣ�����ӡ���ƵĻ�ɫ�����֣�����ƶ�Ϊ�գ����ӡNULL��
��ʼʱ�ƶ�Ϊ�ա�����n���������1 �� n ��200����ִ�ж�Ӧָ�����ָ��ִ����Ϻ��ӡ�ƶ��������ƻ�ɫ�����֣����ƶѶ����ƶѵף�������ƶ�Ϊ�գ����ӡNULL
ע�⣺ÿ�ֻ�ɫ�ͱ�ŵ����������ޡ�
����20%�����ݣ�n<=20����Append��Popָ��
����40%�����ݣ�n<=50����Append��Pop��Revertָ��
����100%�����ݣ�n<=200����Append��Pop��Revert��Extractָ��
�����Ϸ�����p98.py�����������������������
��������
��һ������һ������n����ʾ�����������
��������n�У�ÿһ������һ�����
�������
��������У�ÿ���յ�Popָ������һ�У���ɫ�����ӻ�NULL��������ƶ��е��ƴ��ƶѶ����ƶѵ���һ�������ɫ�����֣������ƶ�Ϊ�������NULL
***********************************************************/
#include<iostream>
#include<string.h>
#include<map>
using namespace std;
#define LIST_INIT_SIZE 500
#define OK 1
#define OVERFLOW -2
//typedef map<char, int> map_ci;
map<string, int> priority;
typedef int Status;
typedef struct card {
	char a[5];
	char color[10];
	/*card() {
		color = (char*)malloc(10);
	}*/
}card;
typedef struct {
	card* x;
	int length;
	int listsize;
}cardlist;
cardlist L;
Status Initlist(cardlist& L)
{
	L.x = (card*)malloc(LIST_INIT_SIZE * sizeof(card));
	if (!L.x)exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
Status append(cardlist& L, char m[], char n[])
{
	card* p, * q, * newbase = NULL;
	if (L.length == 0)
	{
		strcpy_s(L.x[0].a, m);
		//q=&(L.x[0]);
		/*while (n != NULL)
		{
			*(q->color) = *n;
			n++;
			(q->color)++;
		}*/
		strcpy_s(L.x[0].color, 10, n);
		/*L.x[0].color = n;*/
		L.length++;
	}
	else {


		if (L.length >= L.listsize)
		{
			newbase = (card*)realloc(L.x, L.listsize + 100);
		}
		q = &(L.x[0]);
		for (p = &(L.x[L.length - 1]);p >= q;--p)
			*(p + 1) = *p;
		strcpy_s(q->a, m);
		/*q->color = n;*/
		/*while (n != NULL)
		{
			*(q->color) = *n;
			n++;
			q->color++;
		}*/
		strcpy_s(q->color, 10, n);
		++L.length;
	}
	return OK;
}
cardlist extract(char s[], map<string, int> priority)
{
	cardlist C;
	Initlist(C);
	for (int i = 0;i < L.length;i++)
	{
		if (strcmp(L.x[i].color, s) == 0)
		{
			append(C, L.x[i].a, L.x[i].color);
		}
	}
	//sort
	for (int i = 1;i < C.length;i++)
	{
		for (int j = 0;j < C.length - i;j++)
		{
			string a = C.x[j].a;
			string b = C.x[j + 1].a;
			if (priority[a] > priority[b])
			{
				card temp = C.x[j];
				C.x[j] = C.x[j + 1];
				C.x[j + 1] = temp;
			}
		}
	}
	for (int i = L.length - 1;i >= 0;i--)
	{
		if (strcmp(L.x[i].color, s) != 0)
		{
			append(C, L.x[i].a, L.x[i].color);
		}
	}
	return C;
}
void revert(cardlist& L)
{

	card temp;
	for (int i = 0;i < L.length / 2;i++)
	{
		temp = L.x[i];
		L.x[i] = L.x[L.length - 1 - i];
		L.x[L.length - 1 - i] = temp;
	}
}
void pop(cardlist& L)
{
	if (L.length == 0)
		cout << "NULL" << endl;
	else {
		card* p = &(L.x[L.length - 1]);
		cout << p->color << " " << p->a << endl;
		--L.length;
	}
}
void print(cardlist L)
{
	for (int i = L.length - 1;i >= 0;i--)
		cout << L.x[i].color << " " << L.x[i].a << endl;
}
int main()
{
	priority["A"] = 0;
	priority["2"] = 1;
	priority["3"] = 2;
	priority["4"] = 3;
	priority["5"] = 4;
	priority["6"] = 5;
	priority["7"] = 6;
	priority["8"] = 7;
	priority["9"] = 8;
	priority["10"] = 9;
	priority["J"] = 10;
	priority["Q"] = 11;
	priority["K"] = 12;
	int n;
	char a[5];
	char b[10];
	char c[10];
	cin >> n;
	char command[20];
	Initlist(L);
	for (int i = 0;i < n;i++)
	{
		cin >> command;
		if (strcmp(command, "Append") == 0)
		{
			cin >> b >> a;
			append(L, a, b);
		}
		else if (strcmp(command, "Extract") == 0)
		{
			cin >> c;
			L = extract(c, priority);
		}
		else if (strcmp(command, "Pop") == 0)
		{
			pop(L);

		}
		else if (strcmp(command, "Revert") == 0)
		{
			revert(L);
		}
	}


	print(L);
	return 0;
}