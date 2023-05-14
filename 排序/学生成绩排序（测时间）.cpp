#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<random>
#include<chrono>
#include<time.h>
#include<fstream>
using namespace std;
struct student {
	char name[10];
	char no[10];
	int totalscore;
	int chinese;
	int math;
	int eng;
};
//排序规则
bool cmp(student s1, student s2)
{
	if (s1.totalscore != s2.totalscore)
		return s1.totalscore > s2.totalscore;
	else if (s1.chinese != s2.chinese)
		return s1.chinese > s2.chinese;
	else if (s1.math != s2.math)
		return s1.math > s2.math;
	else
		return s1.eng > s2.eng;
}
int partition(student* nums, int low, int high)//把一组数由枢轴元素分成两断
{
	int i = low, j = high;
	student center = nums[i];
	while (i < j)
	{
		while (i < j && cmp(nums[j], center) == 0)
		{
			j--;
		}
		if (i < j)//游标ij没有相遇
		{
			swap(nums[i], nums[j]);
			i++;
		}
		while (i < j && cmp(center, nums[i]) == 0)
		{
			i++;
		}
		if (i < j)
		{
			swap(nums[i], nums[j]);
			j--;
		}
	}
	return i;
}
void quicksort(student* nums, int low, int high)
{
	int center;
	if (low < high)
	{
		center = partition(nums, low, high);
		quicksort(nums, low, center - 1);
		quicksort(nums, center + 1, high);
	}
}
void HeapAdjust(student* arr, int start, int end)
{
	student tmp = arr[start];
	for (int i = 2 * start + 1; i <= end; i = i * 2 + 1)
	{
		if (i < end && cmp(arr[i] , arr[i + 1]))//有右孩子并且左孩子小于右孩子
		{
			i++;
		}//i一定是左右孩子的最大值
		if (cmp(arr[i],tmp)==0)
		{
			arr[start] = arr[i];
			start = i;
		}
		else
		{
			break;
		}
	}
	arr[start] = tmp;
}
void HeapSort(student* arr, int len)
{
	//建立最大堆，从后往前依次调整
	for (int i = (len - 1 - 1) / 2;i >= 0;i--)
	{
		HeapAdjust(arr, i, len - 1);
	}
	//每次将根和待排序的最后一次交换，然后在调整
	student tmp;
	for (int i = 0; i < len - 1; i++)
	{
		tmp = arr[0];
		arr[0] = arr[len - 1 - i];
		arr[len - 1 - i] = tmp;
		HeapAdjust(arr, 0, len - 1 - i - 1);
	}
}

void mergesort(student a[], int left, int right,student*ans)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	int i = left, j = mid + 1;
	mergesort(a, left, mid,ans);//左半部分归并排序
	mergesort(a, mid + 1, right,ans);//右半部分归并排序
	int k = 0;
	while (i <= mid && j <= right)
	{
		if (cmp(a[i],a[j]))
		{
			ans[k] = a[i];
			i++;
			k++;
		}
		else
		{
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
	int n=0;
	for (;n<=500000;n+=10000)//对于不同的n执行num次测试排序时间
	{
		clock_t start, finish;
		student* s = new student[n];
		student* ans = new student[n];
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		default_random_engine gen(seed);
		normal_distribution<double> chn(110, 12);
		normal_distribution<double> math(120, 18);
		normal_distribution<double> eng(125, 10);
		for (int i = 0; i < n; ++i)
		{
			if (chn(gen) > 150)
				s[i].chinese = 150;
			s[i].chinese = floor(chn(gen));
			if (math(gen) > 150)
				s[i].math = 150;
			s[i].math = floor(math(gen));
			if (eng(gen) > 150)
				s[i].eng = 150;
			s[i].eng = floor(eng(gen));
			s[i].totalscore = s[i].chinese + s[i].eng + s[i].math;
		}
		ofstream in;
		start = clock();
		mergesort(s, 0,n-1,ans);
		finish = clock();
		double duration = (double)(finish - start) / CLOCKS_PER_SEC;
		in.open("mergesort_time_data.txt", std::ios::out | std::ios::app);
		in << duration << " ";

		/*start = clock();
		HeapSort(s, n);
		finish = clock();
		double duration = (double)(finish - start) / CLOCKS_PER_SEC;
		in.open("heapsort_time_data.txt", std::ios::out | std::ios::app);
		in << duration << " ";*/

		/*start = clock();
		quicksort(s, 0, n - 1);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "n=" << n << "时排序所用时间为：" << duration << "s\n";
		in.open("quicksort_time_data.txt", std::ios::out | std::ios::app);
		in << duration << " ";*/
	}


	return 0;
}