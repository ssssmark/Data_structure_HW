/**
 * @file    template.cpp
 * @name    p57模板程序
 * @date    2022-11-22
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
public:
    int partition(vector<int>& nums, int low, int high)//把一组数由枢轴元素分成两断
    {
        int i = low, j = high;
        int center = nums[i];
        while (i < j)
        {
            while (i < j && center <= nums[j])
            {
                j--;
            }
            if (i < j)//游标ij没有相遇
            {
                swap(nums[i], nums[j]);
                i++;
            }
            while (i < j && center >= nums[i])
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
    void quicksort(vector<int>& nums, int low, int high)
    {
        int center;
        if (low < high)
        {
            center = partition(nums, low, high);
            quicksort(nums, low, center - 1);
            quicksort(nums, center+1, high);
        }
    }
    std::vector<int> mySort(std::vector<int>& nums) {
        // 这里填写你的代码
        int n = nums.size();
        quicksort(nums, 0, n - 1);
        return nums;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    Solution s;
    std::vector<int> after_sort(s.mySort(nums));
    std::cout << after_sort[0];
    for (int i = 1; i < n; i++) {
        std::cout << ' ' << after_sort[i];
    }
    std::cout << std::endl;
    return 0;
}