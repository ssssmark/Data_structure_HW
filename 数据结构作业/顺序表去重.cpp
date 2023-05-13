/****************************************************************************
顺序表的去重
描述
完成顺序表的去重运算，即将顺序表中所有重复的元素只保留第一个，其他均删除。

输入
第1行1个正整数n, 表示创建的顺序表的元素个数。
第2行n个正整数ai，表示表中元素。 

其中，ai 32位int范围内, n <= 50,000
下载编译并运行p5_data.cpp以生成随机测试数据
输出
1行,去重后的所有元素。
*****************************************************************************/
#include<iostream>
#include<malloc.h>
#include<stdlib.h>
#include<limits.h>
using namespace std;

#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 50000
typedef int ElemType;
typedef int Status;
typedef struct {
    ElemType* elem;
    int length;
    int listsize;
}sqlist;
sqlist L;
Status Initlist(sqlist& L, int Initsize)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * (sizeof(ElemType)));
    L.length = Initsize;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
Status del(sqlist& L, int i)
{
    ElemType* p;
    int* q = L.elem + L.length - 1;
    p = &(L.elem[i]);
    for (++p;p <= q;p++)
        *(p - 1) = *p;
    L.length--;
    if (L.length <= 0)
        return ERROR;
    return OK;
}
void quchong(sqlist& L)
{
    int i, j;
    i = 0, j = 0;
    for (i = 0;i < L.length - 1;i++)
    {
        for (j = i + 1;j < L.length;j++)
            if (L.elem[j] == L.elem[i])
            {
                del(L, j);
                j--;
            }
    }
}
void print(sqlist& L)
{
    for (int i = 0;i < L.length;i++)
        cout << L.elem[i] << " ";
}
int main()
{
    int n;
    cin >> n;
    Initlist(L, n);
    for (int i = 0;i < n;i++)
    {
        cin >> L.elem[i];
        if (L.elem[i] >= INT_MAX)
            return ERROR;
    }
    quchong(L);
    print(L);
    return 0;
}