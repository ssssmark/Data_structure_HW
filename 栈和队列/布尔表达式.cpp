/**********************************************************************
题目描述
计算如下布尔表达式 ( V | V ) & F & ( F | V ) 其中V表示True，F表示False，|表示or，&表示and，！表示not（运算符优先级not> and > or）

输入：
文件输入，有若干（A<=20）个表达式，其中每一行为一个表达式。 表达式有（N<=100）个符号，符号间可以用任意空格分开，或者没有空格，所以表达式的总长度，即字符的个数，是未知的。

对于20%的数据，有A<=5，N<=20，且表达式中包含V、F、&、|

对于40%的数据，有A<=10，N<=50，且表达式中包含V、F、&、|、!

对于100%的数据，有A<=20，N<=100，且表达式中包含V、F、&、|、!、(、)

所有测试数据中都可能穿插空格

下载并运行96.py生成随机测试数据

输出：

对测试用例中的每个表达式输出“Expression”，后面跟着序列号和“: ”，然后是相应的测试表达式的结果（V或F），每个表达式结果占一行（注意冒号后面有空格）。
**************************************************************************/
#include<iostream>
#include<string.h>
#include<conio.h>
using namespace std;
#define OVERFLOW 3
#define ERROR -1
#define STACK_INITSIZE 300
typedef int Status;
typedef struct {
	char* base;
	char* top;
	int stacksize;
}sqstack;
sqstack OPTR, OPND;
Status Initstack(sqstack& L)
{
	L.base = (char*)malloc(sizeof(char) * STACK_INITSIZE);
	if (!L.base) return OVERFLOW;
	L.top = L.base;
	L.stacksize = STACK_INITSIZE;
}
bool in(char c)
{
	if (c == '&' || c == '|' || c == '!' || c == '(' || c == ')' || c == '#')
		return true;
	else return false;
}
Status push(sqstack& L, char m)
{
	if (L.top - L.base >= L.stacksize)
		L.base = (char*)realloc(L.base, (STACK_INITSIZE + 10) * sizeof(char));
	if (!L.base)return (OVERFLOW);
	L.top++;
	*L.top = m;

}
Status pop(sqstack& L)
{
	if (L.base == L.top)
		return ERROR;
	L.top--;
}
char priority(char a, char b)
{
	if (a == '(' && b == ')')return '=';
	/*else if (a == '(' && b == '(')return '>';*/
	else if (a == '#' && b == '#')return '=';
	else if (a == ')' && (b == '!' || b == '&' || b == '|'))return '>';
	else if (b == ')' && (a == '!' || a == '&' || a == '|'))return '>';
	else if (a == '(' && (b == '!' || b == '&' || b == '|'))return '<';
	else if (b == '(' && (a == '!' || a == '&' || a == '|'))return '<';
	else if (a == '!' && b == '&')return '>';
	else if (a == '!' && b == '|')return '>';
	else if (a == '&' && b == '|')return '>';
	else if (a == '&' && b == '!')return '<';
	else if (a == '|' && b == '!')return '<';
	else if (a == '|' && b == '&')return '<';
	else if ((b == '(' || b == ')' || b == '!' || b == '&' || b == '|') && a == '#')return '<';
	else if ((a == '(' || a == ')' || a == '!' || a == '&' || a == '|') && b == '#')return '>';
	else if ((a != '#' && b != '#') && a == b)return '<';
}
char operate1(char a)
{
	if (a == 'V')
		return 'F';
	else if (a == 'F')return 'V';
	else return ERROR;


}
char operate2(char a, char b, char n)
{
	if (a == 'V' && b == 'V')
	{
		if (n == '&')
			return 'V';
		if (n == '|');
		return 'V';
	}
	else if (a == 'V' && b == 'F')
	{
		if (n == '&')
			return 'F';
		if (n == '|');
		return 'V';
	}
	else if (a == 'F' && b == 'V')
	{
		if (n == '&')
			return 'F';
		if (n == '|');
		return 'V';
	}
	else if (a == 'F' && b == 'F')
	{
		if (n == '&')
			return 'F';
		if (n == '|');
		return 'F';
	}
}
void Caculate(char* exp, sqstack& OPTR, sqstack& OPND)
{
	push(OPTR, '#');
	while ((*exp != '#' || *OPTR.top != '#'))
	{
		if ((int)*exp == 32)
			exp++;
		else {
			if (in(*exp) == 0)
			{
				push(OPND, *exp);
				exp++;
			}
			else {
				switch (priority(*OPTR.top, *exp))
				{
				case'>':
					if (*OPTR.top == '!')
					{
						char x = operate1(*OPND.top);
						pop(OPTR);
						pop(OPND);
						push(OPND, x);
					}

					else {
						char m = *OPND.top;
						pop(OPND);
						char n = *OPND.top;
						pop(OPND);
						char ch;
						ch = operate2(m, n, *OPTR.top);
						pop(OPTR);
						push(OPND, ch);


					}
					break;
				case'<':
					push(OPTR, *exp);
					exp++;break;

				case'=':
					pop(OPTR);
					exp++;
					break;
				}
			}
		}
	}
}

int main()
{
	Initstack(OPTR);
	Initstack(OPND);
	int i = 1;
	while (1)
	{
		char exp[500];
		char* p = exp;
		cin.getline(exp, 500);
		if (cin.eof() == 1)break;
		strcat_s(exp, "#");
		Caculate(exp, OPTR, OPND);
		cout << "Expression " << i << ": " << *OPND.top << endl;
		i++;
	}
}