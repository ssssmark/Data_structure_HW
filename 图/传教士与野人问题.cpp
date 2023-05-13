#include<vector>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define MAXM 3
#define MAXC 3
typedef struct Node {
    int M, C, B;
    int g, h, f;
    int  parent;//��¼���ڵ���tree�е��±�
}Node;
vector<Node> open;
vector<Node> close;
vector<Node> tree;
Node boat[8] = {
    { 0,1,1,0,0,0,-1 },
    { 0,2,1,0,0,0,-1 },
    { 0,3,1,0,0,0,-1 },
    { 1,0,1,0,0,0,-1 },
    { 1,1,1,0,0,0,-1 },
    { 2,0,1,0,0,0,-1 },
    { 2,1,1,0,0,0,-1 },
    { 3,0,1,0,0,0,-1 }
};
void show_open() {//��ʾopen��
    vector<Node>::iterator ite;
    ite = open.end() - 1;
    for (; ite >= open.begin(); ite--) {
        printf("(%d,%d,%d,%d,%d,%d)\n", (*ite).M, (*ite).C, (*ite).B, (*ite).g, (*ite).h, (*ite).f);
        if (ite == open.begin()) break;
    }
}
void show_close() {//��ʾclose��
    vector<Node>::iterator ite;
    ite = close.begin();
    for (; ite < close.end(); ite++) {
        printf("(%d,%d,%d,%d,%d,%d)\n", (*ite).M, (*ite).C, (*ite).B, (*ite).g, (*ite).h, (*ite).f);
    }
}
bool operator ==(Node a, Node b) {
    return(a.M == b.M && a.C == b.C && a.B == b.B);
}
bool exit_open(Node p) {//�жϽڵ��Ƿ����open����
    if (find(open.begin(), open.end(), p) == open.end()) return false;
    else return true;
}
bool exit_close(Node p) {//�жϽڵ��Ƿ����close����
    if (find(close.begin(), close.end(), p) == close.end()) return false;
    else return true;
}
bool comp(Node a, Node b) {
    return a.f > b.f;//���ݹ��ۺ���ֵ��������
}
void add_open(Node p) {//open�����
    open.push_back(p);
    sort(open.begin(), open.end(), comp);//Ĭ���������У�����comp����������
}
void add_close(Node p) {//close�����
    close.push_back(p);
}
void out_open() {//open��ɾ��
    open.pop_back();
}
bool judge_Node(Node p) {//�ж�״̬p�Ƿ�Ϸ�
    if (p.M > MAXM || p.C > MAXC || p.M < 0 || p.C < 0)//���ڷ�Χ�ڡ����Ϸ�
        return false;
    /*if (((p.M >= p.C) && (MAXM - p.M >= MAXC - p.C)) || (p.M == MAXM) || (p.M == 0))
        return true;
    return false;*/
    else if (p.M != 0 && p.M < p.C)//�󰶴���ʿ������Ϊ0 ����С��Ұ����
        return false;
    else if (MAXM - p.M != 0 && MAXM - p.M < MAXC - p.C)//�Ұ�����ʿ������Ϊ0������ ��Ȼ��Ұ�����٣�����Ȼ����
        return false;
    else return true;
}
void expand(Node p) {//�Խڵ�p������չ
    Node q;
    printf("------------------------------------------------------------------------------------\n");
    printf("\t\t\t�Խ��: ");
    printf("( %d %d %d )������չ\n", p.M, p.C, p.B);
    for (int i = 0; i < 8; i++) {
        if (p.B == 1) {//p������ 
            q.M = p.M - boat[i].M;
            q.C = p.C - boat[i].C;
            q.B = p.B - boat[i].B;
        }
        else {//p�����Ұ�
            q.M = p.M + boat[i].M;
            q.C = p.C + boat[i].C;
            q.B = p.B + boat[i].B;
        }
        if (judge_Node(q) && !exit_open(q) && !exit_close(q)) {//������ѭ��  �Ѿ���չ���Ľ�㲻����չ
            q.g = p.g + 1;
            q.h = q.M + q.C - 2 * q.B;
            q.f = q.g + q.h;
            int pos = find(tree.begin(), tree.end(), p) - tree.begin();
            q.parent = pos;
            printf("��չ���µ��ӽ��:");
            printf("(%d,%d,%d,%d,%d,%d)\n", q.M, q.C, q.B, q.g, q.h, q.f);
            add_open(q);
            tree.push_back(q);
        }
        else {
            printf("\t------�ڵ�(%d,%d,%d)��������������չʧ��------\n", q.M, q.C, q.B);
        }
    }
    printf("\t\t=======================================================\n");
    add_close(p);
    printf("\t\t\t\t******open��״̬******\n");
    show_open();
    printf("\t\t\t\t******close��״̬******\n");

    show_close();
    printf("------------------------------------------------------------------------------------\n");
}
bool destination(Node p) {//�ж�p�Ƿ�ΪĿ��ڵ�
    if (p.M == 0 && p.C == 0 && p.B == 0) return true;
    else return false;
}
Node solve() {
    Node p{ 3, 3, 1, 0, 10, 10,-1 };
    open.push_back(p);
    tree.push_back(p);
    char c;
    Node x;
    while (open.size() != 0) {
        x = *(open.end() - 1);//��open����ȡ��һ��������չ
        if (destination(x)) return x;//�����Ŀ��״̬  �����
        out_open();//��open��ɾ��
        expand(x);//��չ�ý��
        //getchar();
    }
    //return NULL;
}
void path(Node p) {
    vector<Node> temp;
    while (p.parent != -1) {
        temp.push_back(p);
        p = tree[p.parent];
    }
    temp.push_back(p);
    vector<Node>::iterator ite1 = temp.end() - 1;
    for (; ite1 >= temp.begin(); ite1--) {
        printf("(%d,%d,%d,%d,%d,%d)\n", (*ite1).M, (*ite1).C, (*ite1).B, (*ite1).g, (*ite1).h, (*ite1).f);
        if (ite1 == temp.begin()) break;
    }
}
int main() {
    Node goal = solve();
    printf("��ô���ʿ��Ұ�˹�������״̬�ռ��һ����Ϊ��\n");
    path(goal);
}