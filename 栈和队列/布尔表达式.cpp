/**********************************************************************
��Ŀ����
�������²������ʽ ( V | V ) & F & ( F | V ) ����V��ʾTrue��F��ʾFalse��|��ʾor��&��ʾand������ʾnot����������ȼ�not> and > or��

���룺
�ļ����룬�����ɣ�A<=20�������ʽ������ÿһ��Ϊһ�����ʽ�� ���ʽ�У�N<=100�������ţ����ż����������ո�ֿ�������û�пո����Ա��ʽ���ܳ��ȣ����ַ��ĸ�������δ֪�ġ�

����20%�����ݣ���A<=5��N<=20���ұ��ʽ�а���V��F��&��|

����40%�����ݣ���A<=10��N<=50���ұ��ʽ�а���V��F��&��|��!

����100%�����ݣ���A<=20��N<=100���ұ��ʽ�а���V��F��&��|��!��(��)

���в��������ж����ܴ���ո�

���ز�����96.py���������������

�����

�Բ��������е�ÿ�����ʽ�����Expression��������������кź͡�: ����Ȼ������Ӧ�Ĳ��Ա��ʽ�Ľ����V��F����ÿ�����ʽ���ռһ�У�ע��ð�ź����пո񣩡�
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