/*******************************************************************************************
���� ����һ������ѧ����Ϣ��ѧ�ţ��������ĵ� ˳���ʹ��������¹��ܣ�(1) ����ָ��ѧ���������������ѧ����Ϣ��
(2) ����һ��ѧ����Ϣ�����뵽����ָ����λ�ã�(3) ɾ��ָ��λ�õ�ѧ����¼��
4) �ֱ����������ѧ�Ž��в��ң����ش�ѧ������Ϣ��(5) ͳ�Ʊ���ѧ��������
�������Ҫ��
��1����ѧ������n
������n���Ƕ�ѧ����Ϣ��������ÿ����һ��ѧ����ѧ�š��������ÿո�ָ(ѧ�š����������ַ�����ʾ)
�������������ж�˳���Ĳ�����(ÿ������֮���ÿո�ָ�)
insert i ѧ�� ����: ��ʾ�ڵ�i��λ�ò���ѧ����Ϣ, ��iλ�ò��Ϸ������-1���������0
remove j:��ʾɾ����j��Ԫ�أ���Ԫ��λ�ò����ʣ����-1���������0
check name ����y����������y��˳������Ƿ���ڣ������ڣ������λ����ż�ѧ�š��������������ڣ����-1��
check no ѧ��x������ѧ��x��˳������Ƿ���ڣ������ڣ������λ����ż�ѧ�š��������������ڣ����-1��
end: �������������ѧ�����������˳�����

 ע��ȫ����ֵ <= 10000��Ԫ��λ�ô�1��ʼ�� ѧ����Ϣ���ظ����ݣ�����ʱδ����飩������ʱֻ�践���ҵ��ĵ�һ����
 ÿ������������һ�������Ļ�������ɡ�
 *********************************************************************************************/
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<string>
#define MAX_SIZE 500
#define OK 1
#define ERROR 0
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
typedef int Status;
typedef struct {
    char name[10];
    char no[10];
}student;
typedef struct {
    student* elem;
    int length;
    int listsize;
}sqlist;
sqlist L;
Status Initlist(sqlist& L, int initsize)
{
    L.elem = (student*)malloc(MAX_SIZE * sizeof(student));
    L.length = initsize;
    L.listsize = MAX_SIZE;
    return OK;
}
int insert(sqlist& L, int i)
{
    int a = 0;

    if (i <= 0 || (i > L.length + 1))
    {

        cout << -1 << endl;
        return 0;
    }
    else cout << 0 << endl;
    if (i == L.length + 1)
    {
        L.length++;
        cin >> L.elem[i - 1].no;
        cin >> L.elem[i - 1].name;
    }
    else {
        for (int j = L.length - 1;j >= i - 1;j--)
        {
            L.elem[j + 1] = L.elem[j];
        }
        cin >> L.elem[i - 1].no;
        cin >> L.elem[i - 1].name;
        ++L.length;
    }
    return a;

}
int remove(sqlist& L, int j)
{

    if (j <= 0 || j > L.length)
    {
        cout << -1 << endl;
        return 0;
    }
    else cout << 0 << endl;
    for (int i = j - 1;i < L.length - 1;i++)
    {
        L.elem[i] = L.elem[i + 1];
    }
    --L.length;
    return 0;
}
void checkname(sqlist& L)
{
    int i;
    char name[10];
    cin >> name;
    for (i = 0;i < L.length;i++)
    {
        if (L.length == 0)
        {
            cout << -1 << endl;
            return;
        }
        if (strcmp(L.elem[i].name, name) == 0)
        {
            break;
        }
    }

    if (L.length != 0)
    {

        cout << i + 1 << " " << L.elem[i].no << " " << L.elem[i].name << endl;
    }
    else
        cout << -1 << endl;

}
void checkno(sqlist& L)
{
    int i;
    char no[10];
    cin >> no;
    for (i = 0;i < L.length;i++)
    {
        if (L.length == 0)
        {
            cout << -1 << endl;
            return;
        }
        if (strcmp(L.elem[i].no, no) == 0)
        {
            break;
        }
    }
    if (L.length == 0)
    {
        cout << -1 << endl;
        return;
    }
    if (strcmp(L.elem[i].no, no) == 0)
    {

        cout << i + 1 << " " << L.elem[i].no << " " << L.elem[i].name << endl;
    }
    else
        cout << -1 << endl;
}
void print()
{
    for (int i = 0;i < L.length;i++)
    {
        cout << L.elem[i].no << " " << L.elem[i].name << endl;
    }
}
int main()
{
    int n;
    string s, a;
    string no, name, x, y;
    int locate;
    cin >> n;
    Initlist(L, n);
    for (int i = 0;i < n;i++)
    {
        cin >> L.elem[i].no >> L.elem[i].name;
    }
    do
    {

        cin >> s;
        if (s == "insert")
        {
            cin >> locate;
            insert(L, locate);
        }
        if (s == "remove")
        {
            int j;
            cin >> j;
            remove(L, j);
        }
        if (s == "check")
        {
            cin >> a;
            if (a == "name")
            {
                checkname(L);
            }
            if (a == "no")
            {
                checkno(L);
            }
        }

    } while (s != "end");
    cout << L.length << endl;

    return 0;
}