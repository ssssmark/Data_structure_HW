#include<iostream>
using namespace std;
int ans[100010] = {};
int coun=0;
//�����������(һ���ѡ�񷨳�ʱ��
int cal(int n, int a[])
{
	int i = 0,j = 1;
	int coun = 0;
	while (i < j)
	{
		if (a[i] > a[j])
		{
			coun++;
		}
		if (j < n - 1)
			j++;
		else
		{
			i++;
			if (i == n - 1)
				break;
			else
				j = i + 1;
		}
	}
	return coun;
}

void mergesort(int a[],int left,int right)
{
	if (left >= right)
		return ;
	int mid = (left + right)/2;
	int i = left, j = mid + 1;
	mergesort(a, left, mid);//��벿�ֹ鲢����
	mergesort(a, mid+1, right);//�Ұ벿�ֹ鲢����
	int k = 0;
	while (i <= mid && j <= right)
	{
		if (a[i] <= a[j])
		{
			ans[k] = a[i];
			i++;
			k++;
		}
		else//���������� i�������еĶ��������
		{
			coun += mid - i + 1;
			ans[k] = a[j];
			j++;
			k++;
		}
		
	}
	while (i <= mid)
		ans[k++] = a[i++];
	while (j <= right)
		ans[k++] = a[j++];
	for (int i = left, j = 0;i <= right;i++, j++)
		a[i] = ans[j];
}
int main()
{
	while (1)
	{
		int n;
		cin >> n;
		if (n == 0)//����0����
			break;
		int* a = (int*)malloc(sizeof(int)*(n+1));
		for (int i = 0;i < n;i++)
		{
			cin >> a[i];
		}
		mergesort(a, 0, n-1);
		cout << coun << endl;
		coun = 0;
		
	}
	return 0;
}
