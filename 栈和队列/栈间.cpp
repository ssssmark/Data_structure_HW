//要构建一个从中间访问的栈
#include<iostream>
#include<stack>
using namespace std;
typedef struct Stack {
	int a[5000005];
	int base;
	int top;
};
Stack S;
void init_stack(Stack &S)
{
	S.top = S.base = 0;
}
void push(Stack& S, int x)
{
	S.a[++S.top] = x;
}
int top(Stack& S)
{
	return S.a[S.top];
}
int si(Stack& S, int i)
{
	return S.a[i+1];
}
void pop(Stack &S)
{
	if(S.top)
	S.top--;
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
			int x;
			cin >> x;
			push(S, x);
			break;
		case 2:
			cout << top(S)<<endl;
			break;
		case 3:
			int m;
			cin >> m;
			cout << si(S, m)<<endl;
			break;
		case 4:
			pop(S);
			break;
		}
	}
	return 0;
}