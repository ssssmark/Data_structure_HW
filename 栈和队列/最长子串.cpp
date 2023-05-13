/*已知一个长度为n，仅含有字符'('和')'的字符串，请计算出最长的正确的括号子串的长度及起始位置，若存在多个，取第一个的起始位置。
子串是指任意长度的连续的字符序列。
例1：对字符串 "(()()))()"来说，最长的子串是"(()())"，所以长度 = 6，起始位置是0。
例2：对字符串")())"来说，最长的子串是"()", 子串长度 = 2，起始位置是1。
例3；对字符串""来说，最长的子串是"", 子串长度 = 0，空串的起始位置规定输出0。
字符串长度：0≤n≤1 * 105
对于20 % 的数据：0 <= n <= 20
对于40 % 的数据：0 <= n <= 100
对于60 % 的数据：0 <= n <= 10000
对于100 % 的数据：0 <= n <= 100000
下载并运行p125_data.cpp生成随机测试数据
提示：找最长的正确的括号子串可以用栈来实现，注意会有非法的右括号，比如例2中的第一个右括号。
输入
一行字符串。
输出
子串长度，及起始位置*/
#include<iostream>
#include<string.h>
using namespace std;
#define STACK_INIT_SIZE 100000
#define ERROR -1
#define OVERFLOW 3
typedef int Status;
typedef struct {
	char a;
	int num;
}elem;
typedef struct {
	elem* base;
	elem* top;
	int stacksize;
}sqstack;
sqstack s;
Status Initstack(sqstack& s)
{
	s.base = (elem*)malloc(sizeof(elem) * STACK_INIT_SIZE);
	if (!s.base) exit(OVERFLOW);
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}
Status push(sqstack& s, char a, int i)
{
	if (s.top - s.base >= s.stacksize)
	{
		s.base = (elem*)realloc(s.base, (s.stacksize + 100) * sizeof(elem));
		if (!s.base) return (OVERFLOW);
		s.top = s.base + s.stacksize;
		s.stacksize += 100;
	}
	s.top++;
	s.top->a = a;
	s.top->num = i;

}
Status pop(sqstack& s)
{
	if (s.top == s.base)return ERROR;
	s.top--;

}
void input(string& l)
{
	cin >> l;

}
int count(sqstack& s, string& l, int& n)
{
	int last = -1;
	int ans = 0;
	for (int i = 0;i < l.length();i++)
	{
		if (l[i] != '(' && l[i] != ')')
			return ans;
		if (l[i] == '(')
		{
			push(s, l[i], i);

		}

		if (l[i] == ')')
		{
			if (s.base == s.top)
				last = i;
			else {
				pop(s);
				if (s.base == s.top)
				{
					if (i - last > ans)
						n = last + 1;
					ans = max(ans, i - last);

				}
				else {
					if (i - s.top->num > ans)
						n = s.top->num + 1;
					ans = max(ans, i - s.top->num);

				}
			}
		}
	}
	return ans;
}
int main()
{
	int n = 0;
	string l;
	Initstack(s);
	input(l);
	cout << count(s, l, n) << " ";
	cout << n;
	return 0;
}
