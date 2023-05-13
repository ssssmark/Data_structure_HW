#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;

int a[10005];
int b[10005];
struct node{
	int indexa, indexb;
	int sum;
	bool operator>(const node& a) const { return sum > a.sum; }
}T;
priority_queue <node, vector<node>, greater<node>> nums;
int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	for (int j = 1;j <= n;j++)
	{
		cin >> b[j];
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
		for (int j = 1;j <= n;j++)
		{
			nums.push({ j,1,a[j] + b[1] });
		}
		int index = 1;
	while (k--)
	{
		node temp = nums.top();
		nums.pop();
		cout << temp.sum << " ";
		temp.sum=a[temp.indexa] + b[++temp.indexb];
		nums.push(temp);
	}
	return 0;
}
