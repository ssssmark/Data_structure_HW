/*
列车进站
描述
每一时刻，列车可以从入口进车站或直接从入口进入出口，再或者从车站进入出口。即每一时刻可以有一辆车沿着箭头a或b或c的方向行驶。 现在有一些车在入口处等待，给出该序列，然后给你多组出站序列，请你判断是否能够通过上述的方式从出口出来。

输入
第1行，一个串，入站序列。
后面多行，每行一个串，表示出栈序列
当输入 = EOF时结束
输出
多行，若给定的出栈序列可以得到，输出yes, 否则输出no。 */
#include<iostream>
#include<string.h>
using namespace std;
typedef int Status;
#define ERROR -1
#define OVERFLOW 3
#define STACK_INITSIZE 500
typedef struct {
	char* base;
	char* top;
	int stacksize;
}sqstack;
sqstack L;
Status Initstack(sqstack& L)
{
	L.base = (char*)malloc(sizeof(char) * 500);
	if (!L.base)return (OVERFLOW);
	L.top = L.base;
	L.stacksize = STACK_INITSIZE;
}
Status push(sqstack& L, char m)
{
	if (L.top - L.base >= L.stacksize)
		L.base = (char*)realloc(L.base, (STACK_INITSIZE + 10) * sizeof(char));
	if (!L.base)return (OVERFLOW);
	L.top++;
	*L.top = m;

}
void input(char s[])
{
	cin >> s;
}
void judge(char s[], char l[], sqstack& L)
{
	char out[100] = "";
	char* p, * q, * k;
	p = &(l[0]);
	q = &(s[0]);
	k = &(out[0]);
	while (*p != '\0' && *q != '\0')
	{
		if (*p == *q)
		{
			*k = *q;
			q++;
			p++;
			k++;
		}
		else if (L.top != L.base && (*L.top == *p))
		{
			*k = *L.top;
			k++;
			p++;
			L.top--;
		}
		else {
			push(L, *q);
			q++;
		}
	}

	for (int j = 0;L.top != L.base;j++)
	{
		char* x;
		x = out;
		while (*x != '\0')
			x++;
		*x = *L.top;
		L.top--;
	}
	bool flag = 1;
	for (int i = 0;out[i] != '\0';i++)
	{
		if (out[i] != l[i])
			flag = 0;

	}
	if (flag == 1)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}
int main()
{
	char s[100];
	char a[100];
	Initstack(L);
	input(s);
	while (1)
	{
		cin >> a;
		if (cin.eof() == 1)break;
		/*if (strcmp(a,"EOF")==0)
			break;*/
		judge(s, a, L);

	}
	return 0;
}