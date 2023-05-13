/**
 * @name    template.cpp
 * @brief   p142模板程序
 * @date    2022-12-02
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
class FreqStack {
private:
    map<int, int> cnt; //键值对 数值--出现次数
    vector<int> s;
    int maxfq;
public:
    FreqStack() {
        // 这里填写你的代码
        maxfq = 0;
    }

    void push(int val) {
        // 这里填写你的代码
        s.push_back(val);
        cnt[val]++;
        maxfq = max(maxfq, cnt[val]);

    }
    void findmax()
    {
        auto it = s.begin();
        while (it < s.end())
        {
            if (cnt[*it] > maxfq)
            {
                maxfq = cnt[*it];
            }
            
                it++;
        }
    }
    int pop() {
        // 这里填写你的代码
        auto it=s.end()-1;
        while (it>=s.begin())
        {
            if (cnt[*it] == maxfq)
            {
                int a = *it;
                maxfq--;
                cnt[a]--;
                findmax();
                s.erase(it);//这种能过但是超时了
                return a;
            }
            else if(it>s.begin())
                it--;
         }
       
    }


};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n--) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}

