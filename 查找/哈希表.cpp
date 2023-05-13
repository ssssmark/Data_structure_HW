#include<iostream>
#include<string.h>
#include<iomanip>
#include<math.h>
using namespace std;
bool is_su(int x)
{
	if (x == 1)
		return false;
	for (int i = 2;i <= sqrt(x);i++)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}
void hashtable(char key[], long long int hkey, int M, int* hash)
{
	hkey = key[0];
	int length = 0;
	int location;
	while (1)
	{
		if (key[length] != '\0')
			length++;
		else {
			break;
		}
	}
	for (int i = 1;i<=length-1;i++)
	{
		hkey = ((((hkey%M) *(37%M))%M)%M + key[i]%M)%M;
	}
	if (length == 1)
		location = hkey % M;
	else location = hkey;
	if (hash[location]==-1)
	{
		hash[location] = hkey;
		cout << location << " ";
	}
	else
	{
		int flag = 0;
		for (int i = 1;i<=M-1;i++)
		{
			location += i * i;
			if (location > M-1)
			{
				location = (location)% M;
			}
			if (hash[location] == -1)
			{
				hash[location] = hkey;
				cout << location << " ";
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			cout << "-" << " ";
		}
	}
}
int main()
{
	int N, P,M;//N为关键字个数，P为表长
	long long int hkey=0;
	int* hash = (int*)malloc(sizeof(int) * 10000);
	cin >> N >> P;
	if (is_su(P) == false)
	{
		while (1)
		{
			P++;
			if (is_su(P) == true)
				break;
		}
	}
	if (P == 1)
	{
		M = 2;
		P = 2;
	}
	M = P;
	
	for (int i = 0;i < M;i++)
		hash[i] = -1;
	for (int i = 0;i < N;i++)
	{
		char s[10000] = {};
		cin >> s;
		hashtable(s, hkey, M, hash);
	}
	return 0;
}