/****************************************************************************
˳����ȥ��
����
���˳����ȥ�����㣬����˳����������ظ���Ԫ��ֻ������һ����������ɾ����

����
��1��1��������n, ��ʾ������˳����Ԫ�ظ�����
��2��n��������ai����ʾ����Ԫ�ء� 

���У�ai 32λint��Χ��, n <= 50,000
���ر��벢����p5_data.cpp�����������������
���
1��,ȥ�غ������Ԫ�ء�
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