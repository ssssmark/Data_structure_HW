/*��֪һ������Ϊn���������ַ�'('��')'���ַ����������������ȷ�������Ӵ��ĳ��ȼ���ʼλ�ã������ڶ����ȡ��һ������ʼλ�á�
�Ӵ���ָ���ⳤ�ȵ��������ַ����С�
��1�����ַ��� "(()()))()"��˵������Ӵ���"(()())"�����Գ��� = 6����ʼλ����0��
��2�����ַ���")())"��˵������Ӵ���"()", �Ӵ����� = 2����ʼλ����1��
��3�����ַ���""��˵������Ӵ���"", �Ӵ����� = 0���մ�����ʼλ�ù涨���0��
�ַ������ȣ�0��n��1 * 105
����20 % �����ݣ�0 <= n <= 20
����40 % �����ݣ�0 <= n <= 100
����60 % �����ݣ�0 <= n <= 10000
����100 % �����ݣ�0 <= n <= 100000
���ز�����p125_data.cpp���������������
��ʾ���������ȷ�������Ӵ�������ջ��ʵ�֣�ע����зǷ��������ţ�������2�еĵ�һ�������š�
����
һ���ַ�����
���
�Ӵ����ȣ�����ʼλ��*/
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
