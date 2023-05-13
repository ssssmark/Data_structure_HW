#include<iostream>
#include<math.h>
using namespace std;
int nums[1000] = { 0 };
int queries[1000] = { 0 };
int answer[1000] = { 0 };
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0;i < n;i++)
		cin >> nums[i];
	for (int j = 0;j < m;j++)
		cin >> queries[j];
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n - i - 1;j++)
		{
			if (nums[j] > nums[j+1])
			{
				int temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
			}
		}
	}
	for (int j = 0;j < m;j++)
	{
		int count = 0;
		int sum = 0;
		for (int i = 0;;i++)
		{
			
			if (sum <= queries[j])
			{
				sum += nums[i];
				count++;
				if (count > n)
				{
					answer[j] = n;
					break;
				}
			}
			else
			{
				answer[j] = count-1;
				break;
			}
		}
	}
	for (int i = 0;i < m;i++)
	{
		cout << answer[i] << " ";
	}
	return 0;
}