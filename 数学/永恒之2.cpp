//找出1-k的十六进制中2出现了多少次
#include<iostream>
#include<stdio.h>
using namespace std;
long long p[15] = {1},a[15],ans,n;
char s[15];

signed main()
{
	int n;
	cin >> n >> s;
	for (int i = 1;i <= n;i++)
	{
		p[i] = p[i - 1] * 16;
	}
	for (int i = 0;i < n;i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
			a[i] = s[i] - '0';
		else {
			a[i] = s[i] - 'A' + 10;
		}
	}
	for (int i = 0;i < n;i++)
	{

	}
}