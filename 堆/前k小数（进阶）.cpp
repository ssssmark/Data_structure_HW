#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;
const int N = 1e8;
int a[N];
int b[N];
int c[N];
struct node {
	int indexa, indexb;
	int sum;
	bool operator>(const node& a) const { return sum > a.sum; }
}T;
priority_queue <node, vector<node>, greater<node>> nums;
int main()
{
	int n, m, k;
	cin >> n >>m>> k;
	for (int i = 1;i <= m;i++)
	{
		cin >> a[i];
	}
	for (int j = 1;j <= m;j++)
	{
		cin >> b[j];
	}
	sort(a + 1, a + m + 1);
	sort(b + 1, b + m + 1);
	for (int j = 1;j <= m;j++)
	{
		nums.push({ j,1,a[j] + b[1] });
	}
	int index = 1;
	for (int i = 1;i <= k;i++)
	{
		node temp = nums.top();
		nums.pop();
		c[i] = temp.sum;
		temp.sum = a[temp.indexa] + b[++temp.indexb];
		nums.push(temp);
	}
	n -= 2;
	while (n--) {
		while (!nums.empty())
		{
			nums.pop();
		}
		for (int i = 1;i <= k;i++)
		{
			a[i] = c[i];
		}
		for (int i = 1;i <= k;i++)
			cin >> b[i];
		sort(b + 1, b + m + 1);
		for (int j = 1;j <= k;j++)
		{
			nums.push({ j,1,a[j] + b[1] });
		}
		for (int i = 1;i <= k;i++)
		{
			node temp = nums.top();
			nums.pop();
			c[i] = temp.sum;
			temp.sum = a[temp.indexa] + b[++temp.indexb];
			nums.push(temp);
		}
		
	}
	for (int i = 1;i <= k;i++)
		cout << c[i] << " ";
	return 0;
}
