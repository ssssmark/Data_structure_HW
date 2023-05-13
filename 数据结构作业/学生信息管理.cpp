/*******************************************************************************************
本题 定义一个包含学生信息（学号，姓名）的的 顺序表，使其具有如下功能：(1) 根据指定学生个数，逐个输入学生信息；
(2) 给定一个学生信息，插入到表中指定的位置；(3) 删除指定位置的学生记录；
4) 分别根据姓名和学号进行查找，返回此学生的信息；(5) 统计表中学生个数。
输入输出要求
第1行是学生总数n
接下来n行是对学生信息的描述，每行是一名学生的学号、姓名，用空格分割；(学号、姓名均用字符串表示)
接下来是若干行对顺序表的操作：(每行内容之间用空格分隔)
insert i 学号 姓名: 表示在第i个位置插入学生信息, 若i位置不合法，输出-1，否则输出0
remove j:表示删除第j个元素，若元素位置不合适，输出-1，否则输出0
check name 姓名y：查找姓名y在顺序表中是否存在，若存在，输出其位置序号及学号、姓名，若不存在，输出-1。
check no 学号x：查找学号x在顺序表中是否存在，若存在，输出其位置序号及学号、姓名，若不存在，输出-1。
end: 操作结束，输出学生总人数，退出程序。

 注：全部数值 <= 10000，元素位置从1开始。 学生信息有重复数据（输入时未做检查），查找时只需返回找到的第一个。
 每个操作都在上一个操作的基础上完成。
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