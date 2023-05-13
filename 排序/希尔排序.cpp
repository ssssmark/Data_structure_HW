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
	void Shell_Sort(vector<int>&src, int num) {
		

		int gap = num / 2;	//增量
		while (gap) {
			for (int i = gap; i < num; i++) {
				int tmp = src[i];
				int j = i;
				while (j >= gap && tmp < src[j - gap]) {
					src[j] = src[j - gap];
					
					j -= gap;
				}
				src[j] = tmp;
			}
			gap = gap == 2 ? 1 : (int)(gap / 2.2);	//增量变化
		}
		
	}

    std::vector<int> mySort(std::vector<int>& nums) {
        // 这里填写你的代码
		Shell_Sort(nums, nums.size());
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