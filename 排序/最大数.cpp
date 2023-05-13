/**
 * @file    template.cpp
 * @name    模板程序
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
    bool comp(int a, int b)
    {
        string sa = to_string(a);
        string sb = to_string(b);
        return sa + sb > sb + sa;
    }
    std::string largestNumber(std::vector<int>& nums) {
        // 这里填写你的代码 
        int n = nums.size();
        //比较任意两个数构成的字符串，如果a+b>b+a，那么就把a排在b前面，选择排序即可
        for (int i=0;i<n;i++)
        {
            for (int j = i+1;j < n;j++)
            {
                if (comp(nums[i], nums[j]) == 0)
                {
                    int temp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = temp;
                }
             }
        }
        string ans="";
        for (int i = 0;i < n;i++)
        {
            ans += to_string(nums[i]);
        }
        return ans;
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
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}