#include <iostream>
#include <list>

using namespace std;

int josephus(int n, int q) {
    list<int> people;

    // 初始化人员编号
    for (int i = 1; i <= n; i++) {
        people.push_back(i);
    }

    list<int>::iterator current = people.begin();
    while (people.size() > 1) {
        // 报数，移动迭代器
        for (int count = 1; count < q; count++) {
            current++;
            if (current == people.end()) {
                current = people.begin();
            }
        }

        // 移除被杀掉的人
        current = people.erase(current);

        // 如果已经到达末尾，则重新指向开头
        if (current == people.end()) {
            current = people.begin();
        }
    }

    // 返回最后剩下的人的编号
    return people.front();
}

int main() {
    int n, q;
    cin >> n >> q;
    int survivor = josephus(n, q);
    cout << survivor << endl;

    return 0;
}