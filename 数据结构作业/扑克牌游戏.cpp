/*************************************************************
扑克牌游戏
题目描述
扑克牌有4种花色：黑桃（Spade）、红心（Heart）、梅花（Club）、方块（Diamond）。每种花色有13张牌，编号从小到大为：A,2,3,4,5,6,7,8,9,10,J,Q,K。
对于一个扑克牌堆，定义以下4种操作命令：
1) 添加（Append）：添加一张扑克牌到牌堆的底部。如命令“Append Club Q”表示添加一张梅花Q到牌堆的底部。
2) 抽取（Extract）：从牌堆中抽取某种花色的所有牌，按照编号从小到大进行排序，并放到牌堆的顶部。如命令“Extract Heart”表示抽取所有红心牌，排序之后放到牌堆的顶部。
3)反转（Revert）：使整个牌堆逆序。
4)弹出（Pop）：如果牌堆非空，则除去牌堆顶部的第一张牌，并打印该牌的花色和数字；如果牌堆为空，则打印NULL。
初始时牌堆为空。输入n个操作命令（1 ≤ n ≤200），执行对应指令。所有指令执行完毕后打印牌堆中所有牌花色和数字（从牌堆顶到牌堆底），如果牌堆为空，则打印NULL
注意：每种花色和编号的牌数量不限。
对于20%的数据，n<=20，有Append、Pop指令
对于40%的数据，n<=50，有Append、Pop、Revert指令
对于100%的数据，n<=200，有Append、Pop、Revert、Extract指令
从右上方下载p98.py并运行以生成随机测试数据
输入描述
第一行输入一个整数n，表示命令的数量。
接下来的n行，每一行输入一个命令。
输出描述
输出若干行，每次收到Pop指令后输出一行（花色和数子或NULL），最后将牌堆中的牌从牌堆顶到牌堆底逐一输出（花色和数字），若牌堆为空则输出NULL
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