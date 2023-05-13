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
bool cmp(student s1,student s2)
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
		while (i < j && cmp(nums[j],center)==0)
		{
			j--;
		}
		if (i < j)//游标ij没有相遇
		{
			swap(nums[i], nums[j]);
			i++;
		}
		while (i < j && cmp(center,nums[i])==0)
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
int main()
{
	int n;
	cin >> n;
	student* s = new student[n];
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine gen(seed);
	normal_distribution<double> chn(110, 12);
	normal_distribution<double> math(120, 18);
	normal_distribution<double> eng(125, 10);
	for (int i = 0; i < n; ++i)
	{
		cin >> s[i].no >> s[i].name;
		if (chn(gen) > 150)
			s[i].chinese = 150;
		s[i].chinese = floor(chn(gen));
		if (math(gen) > 150)
			s[i].math = 150;
		s[i].math = floor(math(gen));
		if (eng(gen) > 150)
			s[i].eng= 150;
		s[i].eng = floor(eng(gen));
		s[i].totalscore = s[i].chinese + s[i].eng + s[i].math;
	}
	for (int i = 0;i < n;i++)
	{
		cout << s[i].no << " " << s[i].name << " " << s[i].totalscore << " " << s[i].chinese << " " << s[i].math << " " << s[i].eng << endl;
	}
	quicksort(s, 0, n - 1);
	for (int i = 0;i < n;i++)
	{
		cout << s[i].no << " " << s[i].name << " " << s[i].totalscore << " " << s[i].chinese << " " << s[i].math << " " << s[i].eng << endl;
	}
	
	return 0;
}