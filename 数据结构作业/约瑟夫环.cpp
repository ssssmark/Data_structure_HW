#include <iostream>
#include <list>

using namespace std;

int josephus(int n, int q) {
    list<int> people;

    // ��ʼ����Ա���
    for (int i = 1; i <= n; i++) {
        people.push_back(i);
    }

    list<int>::iterator current = people.begin();
    while (people.size() > 1) {
        // �������ƶ�������
        for (int count = 1; count < q; count++) {
            current++;
            if (current == people.end()) {
                current = people.begin();
            }
        }

        // �Ƴ���ɱ������
        current = people.erase(current);

        // ����Ѿ�����ĩβ��������ָ��ͷ
        if (current == people.end()) {
            current = people.begin();
        }
    }

    // �������ʣ�µ��˵ı��
    return people.front();
}

int main() {
    int n, q;
    cin >> n >> q;
    int survivor = josephus(n, q);
    cout << survivor << endl;

    return 0;
}