/**
 * @file    template.cpp
 * @name    p57ģ�����
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
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class Solution {
public:
	void Shell_Sort(vector<int>&src, int num) {
		

		int gap = num / 2;	//����
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
			gap = gap == 2 ? 1 : (int)(gap / 2.2);	//�����仯
		}
		
	}

    std::vector<int> mySort(std::vector<int>& nums) {
        // ������д��Ĵ���
		Shell_Sort(nums, nums.size());
		return nums;
    }
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
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