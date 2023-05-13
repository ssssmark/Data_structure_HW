/**
 * @name    template.cpp
 * @brief   p142ģ�����
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
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class FreqStack {
private:
    map<int, int> cnt; //��ֵ�� ��ֵ--���ִ���
    vector<int> s;
    int maxfq;
public:
    FreqStack() {
        // ������д��Ĵ���
        maxfq = 0;
    }

    void push(int val) {
        // ������д��Ĵ���
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
        // ������д��Ĵ���
        auto it=s.end()-1;
        while (it>=s.begin())
        {
            if (cnt[*it] == maxfq)
            {
                int a = *it;
                maxfq--;
                cnt[a]--;
                findmax();
                s.erase(it);//�����ܹ����ǳ�ʱ��
                return a;
            }
            else if(it>s.begin())
                it--;
         }
       
    }


};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
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

