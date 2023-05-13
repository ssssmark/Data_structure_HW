/**
 * @name    p90_data.cpp
 * @brief   p90 ��������������ɳ���
 * @author  ��У
 * @date    2021-12-11
 */

#include <iostream>
#include <fstream>
#include <map>
#include<string>
using namespace std;

/**
 * @brief ƽ�����������
 */
class SORTTREE {
public:
    static const int MAX_ELEM = 100000;
    static const int RANDOM_GAP = 10; // ������֤ MAX_ELEM / RANDOM_GAP > n
    struct NODE {
        NODE* left_, * right_, * parent_;
        int elem_, count_, height_;
        NODE(int elem, NODE* parent) : elem_(elem), parent_(parent) {
            left_ = NULL;
            right_ = NULL;
            count_ = 1;
            height_ = 1;
        }
        ~NODE() {
            if (left_)
                delete left_;
            if (right_)
                delete right_;
        }
        /**
         * @brief ����ƽ���
         */
        int Balance() {
            return -(left_ ? left_->height_ : 0) + (right_ ? right_->height_ : 0);
        }
        /**
         * @brief ���½ڵ�߶�
         */
        void UpdateHeight() {
            height_ = std::max((left_ ? left_->height_ : 0), (right_ ? right_->height_ : 0)) + 1;
        }
        /**
         * @name    bool Find(int elem, NODE *&last, NODE *&thiss, NODE *&next, bool &found)
         * @brief   ����һ��Ԫ�صĶ�Ӧǰ������Ӧ�ڵ㡢��Ӧ�����ڵ�
         * @param   elem �����ҵ�Ԫ��
         * @param   last ǰ������û����ΪNULL����Ҫ��ʼ��ΪNULL
         * @param   thiss ��Ӧ�ڵ㣬��û����ΪNULL
         * @param   next ��̣���û����ΪNULL����Ҫ��ʼ��ΪNULL
         * @param   found �Ƿ��Ѿ��ҵ���true��ʾ�Ѿ��ҵ����������ݹ��ҵ���̽ڵ���˳�
         * @return  �Ƿ��ҵ���̣����ҽ���
         */
        bool Find(int elem, NODE*& last, NODE*& thiss, NODE*& next, bool& found) {
            if (left_)
                if (left_->Find(elem, last, thiss, next, found))
                    return true;
            if (found) { // �Ѿ��ҵ����ýڵ㼴Ϊ��̽ڵ㣬���нڵ㶼�ҵ��������˳�
                next = this;
                return true;
            }
            if (elem_ > elem) { // û�ж�Ӧ�ڵ㣬�ҵ�ǰ���ͺ�̣������˳�
                thiss = NULL;
                next = this;
                return true;
            }
            if (elem_ == elem) { // �ҵ���Ӧ�ڵ㣬��Ҫ�����������Һ��
                thiss = this;
                found = true;
            }
            else
                last = this; // û���ҵ���Ӧ�ڵ㣬��ǰ�ڵ�ֵС�ڲ���Ԫ�أ���ʱ��Ϊǰ��
            if (right_)
                return right_->Find(elem, last, thiss, next, found);
            return false; // ���һ�δ����
        }
    };

    SORTTREE() { root_ = NULL; }
    ~SORTTREE() { delete root_; }
    /**
     * @brief ����һ��Ԫ��
     */
    void Insert(int elem) {
        if (!root_) {
            root_ = new NODE(elem, NULL);
            return;
        }
        NODE* l = NULL, * p = NULL, * n = NULL;
        bool found = false;
        root_->Find(elem, l, p, n, found);

        if (p) {
            p->count_++;
            return;
        }
        // ǰ�����Һ��Ӻͺ�̵�����֮��һ����һ��Ϊ�գ����½ڵ����
        if (l && !l->right_) {
            p = (l->right_ = new NODE(elem, l));
        }
        else {
            p = (n->left_ = new NODE(elem, n));
        }
        KeepBalance(p);
    }
    /**
     * @brief ɾ��һ��Ԫ��
     */
    bool Delete(int elem) {
        if (!root_)
            return false;
        NODE* l = NULL, * p = NULL, * n = NULL;
        bool found = false;
        root_->Find(elem, l, p, n, found);
        if (!p) // û�ҵ�
            return false;
        if (p->count_ > 1) { // ��ɾ��Ԫ�ز�ֹһ����������һ����
            p->count_--;
            return true;
        }
        // ��ɾ��Ԫ��ֻ��һ������Ҫɾ���ڵ�
        if (!p->left_ && !p->right_) { // ��ɾ���ڵ�ΪҶ�ӽڵ�
            if (!p->parent_) {
                root_ = NULL;
            }
            else {
                ChangeParent(p, NULL);
                KeepBalance(p->parent_);
            }
        }
        else if (!p->left_) { // û�����������޷���ǰ�������Լ����������������Լ�
            // ���û����������Ҳ����ֱ���������������Լ�
            ChangeParent(p, p->right_);
            KeepBalance(p->parent_);
        }
        else { // ������������ǰ��һ�����������У���ǰ�������Լ�
            if (p->left_ == l) { // ǰ����������
                l->right_ = p->right_;
                if (p->right_)
                    p->right_->parent_ = l;
                ChangeParent(p, l);
                KeepBalance(l);
            }
            else { // �ҵ�ǰ������ǰ�������Լ����������ӹ�ϵ
                NODE* t = l->parent_;
                t->right_ = l->left_;
                if (l->left_)
                    l->left_->parent_ = t;

                l->left_ = p->left_;
                p->left_->parent_ = l;
                l->right_ = p->right_;
                if (p->right_)
                    p->right_->parent_ = l;

                ChangeParent(p, l);
                KeepBalance(t);
            }
        }
        p->left_ = p->right_ = NULL;
        delete p;
        return true;
    }
    /**
     * @brief Ԫ�ؼ���
     */
    int Count(int elem) {
        if (!root_)
            return 0;
        NODE* l = NULL, * p = NULL, * n = NULL;
        bool found = false;
        root_->Find(elem, l, p, n, found);
        if (p)
            return p->count_;
        return 0;
    }
    /**
     * @brief ������СԪ��
     */
    int FindMinElem() {
        if (!root_)
            return -1;
        NODE* p = root_;
        while (p->left_)
            p = p->left_;
        return p->elem_;
    }
    /**
     * @brief ����ǰ��Ԫ��
     */
    int FindFrontElem(int elem) {
        if (!root_)
            return -1;
        NODE* l = NULL, * p = NULL, * n = NULL;
        bool found = false;

        root_->Find(elem, l, p, n, found);
        if (l)
            return l->elem_;
        return -1;
    }
private:
    /**
     * @brief ��������ƽ��
     * @param p ����ʧ�����ͽڵ�
     */
    void KeepBalance(NODE* p) {
        while (p) {
            p->UpdateHeight();
            if (-2 >= p->Balance() || p->Balance() >= 2) {
                // ��ת
                if (p->Balance() < 0) {
                    if (p->left_->Balance() <= 0) {
                        RotateRight(p);
                    }
                    else {
                        RotateLeft(p->left_);
                        RotateRight(p);
                    }
                }
                else {
                    if (p->right_->Balance() >= 0) {
                        RotateLeft(p);
                    }
                    else {
                        RotateRight(p->right_);
                        RotateLeft(p);

                    }
                }
            }
            p = p->parent_;
        }
    }
    /**
     * @brief ����ת
     */
    void RotateRight(NODE* p) {
        NODE* t = p->left_;
        p->left_ = t->right_;
        if (t->right_)
            t->right_->parent_ = p;
        t->right_ = p;
        UpdateRelation(p, t);
    }
    /**
     * @brief ����ת
     */
    void RotateLeft(NODE* p) {
        NODE* t = p->right_;
        p->right_ = t->left_;
        if (t->left_)
            t->left_->parent_ = p;
        t->left_ = p;
        UpdateRelation(p, t);
    }
    /**
     * @brief ������ת��ڵ��ϵ
     */
    void UpdateRelation(NODE* p, NODE* t) {
        ChangeParent(p, t);
        p->parent_ = t;
        p->UpdateHeight();
        t->UpdateHeight();
    }
    /**
     * @brief �ý�p�ļ����ϵ����t
     */
    void ChangeParent(NODE* p, NODE* t) {
        if (t)
            t->parent_ = p->parent_;
        if (p->parent_) {
            if (p == p->parent_->left_)
                p->parent_->left_ = t;
            else
                p->parent_->right_ = t;
        }
        else
            root_ = t;
    }
    NODE* root_;
};

int RandomElem(std::map<int, int>& M) {
    if (!M.size())
        return rand() % SORTTREE::MAX_ELEM + 1;
    std::map<int, int>::iterator it = M.begin();
    std::advance(it, rand() % M.size());
    return (*it).first;
}

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // ���Ե����
    for (int index = 1; index <= test_num; index++) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n;
        if (index <= test_num * 0.2) {
            n = rand() % 6 + 15;
        }
        else if (index <= test_num * 0.4) {
            n = rand() % 11 + 90;
        }
        else if (index <= test_num * 0.6) {
            n = rand() % 51 + 500;
        }
        else {
            n = rand() % 101 + 900;
        }
        fin << n << std::endl;

        SORTTREE& T = *(new SORTTREE);
        std::map<int, int> M;

        int last_insert;
        for (int i = 0; i < n; i++) {
            int ope, elem = 0, last = 0;
            // �����������������
            if (index % 2 == 0) { // һ������ݻῼ���������ܣ������������������
                if (i == 0) {
                    ope = 1;
                    if (index % 4 == 0)
                        elem = SORTTREE::MAX_ELEM - rand() % SORTTREE::RANDOM_GAP;
                    else
                        elem = rand() % SORTTREE::RANDOM_GAP;
                    last_insert = elem;
                }
                else if (i <= 0.7 * n) { // ǰ70%�����о��󲿷�Ϊ���룬�Ҳ������ݻ�������
                    int select = rand() % 20;
                    if (select < 16) {
                        ope = 1;
                        if (index % 4 == 0) {
                            elem = std::max(1, last_insert - (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP));
                            last_insert = std::min(last_insert, elem);
                        }
                        else {
                            elem = last_insert + (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP);
                            last_insert = std::max(last_insert, elem);
                        }
                    }
                    else if (select == 16) {
                        ope = 2;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                    else if (select == 17) {
                        ope = 3;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                    else if (select == 18) {
                        ope = 4;
                    }
                    else {
                        ope = 5;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                }
                else { // ��һ�������в��ҾӶ࣬�һ���λ�����׶�
                    int select = rand() % 20;
                    if (select < 2) {
                        ope = 1;
                        if (rand() % 3 != 0) {
                            if (index % 4 == 0) {
                                elem = last_insert + (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP);
                                last_insert = std::max(last_insert, elem);
                            }
                            else {
                                elem = last_insert - (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP);
                                last_insert = std::min(last_insert, elem);
                            }
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select < 4) {
                        ope = 2;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                    else if (select < 14) {
                        ope = 3;
                        if (index % 4 == 0) {
                            elem = rand() % int(SORTTREE::MAX_ELEM * 0.2);
                        }
                        else {
                            elem = SORTTREE::MAX_ELEM - rand() % int(SORTTREE::MAX_ELEM * 0.2);
                        }
                    }
                    else if (select == 14) {
                        ope = 4;
                    }
                    else {
                        ope = 5;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                }
            }
            else {
                if (i <= n * 0.1 || i > n * 0.3 && i <= n * 0.5) {
                    int select = rand() % 20;
                    if (select < 16) {
                        ope = 1;
                        if (rand() % 3 < 2) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select == 16) {
                        ope = 2;
                        if (rand() % 4 < 1) {
                            elem = RandomElem(M);
                        }
                        else {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                    else if (select == 17) {
                        ope = 3;
                        if (rand() % 4 < 1) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select == 18) {
                        ope = 4;
                    }
                    else if (select == 19) {
                        ope = 5;
                        elem = T.FindMinElem();
                        if (rand() % 5 != 0 || elem == -1) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                }
                else if (i <= n * 0.3) {
                    int select = rand() % 20;
                    if (select < 16) {
                        ope = 2;
                        if (rand() % 7 < 1) {
                            elem = RandomElem(M);
                        }
                        else {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                    else if (select == 16) {
                        ope = 1;
                        if (rand() % 3 < 2) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select == 17) {
                        ope = 3;
                        if (rand() % 4 < 1) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select == 18) {
                        ope = 4;
                    }
                    else if (select == 19) {
                        ope = 5;
                        elem = T.FindMinElem();
                        if (rand() % 5 != 0 || elem == -1) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                }
                else {
                    int select = rand() % 10;
                    if (select < 3) {
                        ope = 1;
                        if (rand() % 3 < 2) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select < 5) {
                        ope = 2;
                        if (rand() % 4 < 1) {
                            elem = RandomElem(M);
                        }
                        else {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                    else if (select == 6) {
                        ope = 3;
                        if (rand() % 4 < 1) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if (select == 7) {
                        ope = 4;
                    }
                    else {
                        ope = 5;
                        elem = T.FindMinElem();
                        if (rand() % 5 != 0 || elem == -1) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                }
            }
            fin << ope;
            if (ope != 4)
                fin << ' ' << elem;
            fin << std::endl;

            switch (ope) {
            case 1:
                T.Insert(elem);
                if (M.find(elem) != M.end())
                    M[elem] ++;
                else
                    M[elem] = 1;
                break;
            case 2:
                if (!T.Delete(elem))
                    fout << "None" << std::endl;
                if (M.find(elem) != M.end()) {
                    if (M[elem] > 0)
                        M[elem] --;
                    else
                        M.erase(elem);
                }
                break;
            case 3:
                fout << T.Count(elem) << std::endl;
                break;
            case 4:
                fout << T.FindMinElem() << std::endl;
                break;
            case 5:
                last = T.FindFrontElem(elem);
                if (last == -1)
                    fout << "None" << std::endl;
                else
                    fout << last << std::endl;
                break;
            default:
                break;
            }
        }
        delete& T;
        fin.close();
        fout.close();
    }
    return 0;
}