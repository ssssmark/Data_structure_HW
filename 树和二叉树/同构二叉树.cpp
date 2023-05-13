/**********************************************************************
* ����������T1��T2�����T1����ͨ�����ɴ����Һ��ӻ������T2�������ǳ��������ǡ�ͬ�����ġ�����ͼ1����������������ͬ���ģ���Ϊ���ǰ�����һ�����Ľ��A��B��G�����Һ��ӻ����󣬾͵õ�����һ��������ͼ2�Ͳ���ͬ���ġ�

�ָ����������������ж������Ƿ���ͬ���ġ�������ÿ��������ȡ�
����:
��һ����һ���Ǹ�����N1����ʾ��1�����Ľ������
���N�У����ζ�Ӧ��������N����㣨�������0��N?1��ţ���ÿ��������ֱ���1��Ӣ�Ĵ�д��ĸ�������ӽ��ı�š��Һ��ӽ��ı�š�������ӽ��Ϊ�գ�������Ӧλ���ϸ�����-�������������ݼ���һ���ո�ָ���
����һ����һ���Ǹ�����N2����ʾ��2�����Ľ������
���N��ͬ������һ�������ζ�Ӧ��������N����㡣
����20%�����ݣ���0<N1=N2<=10
����40%�����ݣ���0<=N1=N2<=100
����100%�����ݣ���0<=N1,N2<=10100
ע�⣺��Ŀ����֤ÿ������д洢����ĸ�ǲ�ͬ�ġ�
���:
�����С�
��һ�У������������ͬ���ģ������Yes�������������No����
�������зֱ�������������ȡ�
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#define MaxTree 10100
struct TreeNode
{
    char data;
    int lt;
    int rt;
    /*TreeNode(char val = '#', int l = -1, int r = -1) {
        data = val;
        lt = l;
        rt = r;
    }*/
};//T1[MaxTree], T2[MaxTree];

TreeNode* T1 = new TreeNode[MaxTree];
TreeNode* T2 = new TreeNode[MaxTree];

int BuildTree(struct TreeNode* T, int N)
{
    int i;
    string cl, cr;
    int check[10500];
    if (N)
    {
        for (i = 0; i < N; i++)
        {
            check[i] = 1;  //��ʼ��
        }
        for (i = 0; i < N; i++)
        {
            cin >> T[i].data >> cl >> cr;
            if (cl != "-")
            {
                T[i].lt = atoi(cl.c_str());
                check[T[i].lt] = -1;
            }
            else
            {

                T[i].lt = -1;
            }

            if (cr != "-")
            {
                T[i].rt = atoi(cr.c_str());
                check[T[i].rt] = -1;
            }
            else
            {
                T[i].rt = -1;
            }
        }
        //�ж��ǲ��Ǹ��ڵ㣬���ڵ�û��˫�׽��
        for (i = 0; i < N; i++)
        {
            if (check[i] == 1)
            {
                return i;  //���ظ����ı��
            }
        }
        return -1;
    }
    return -1;
}
int depth1(struct TreeNode  T)
{
    int m, n;
    if (T.lt != -1 && T.rt == -1)
    {
        m = depth1(T1[T.lt]);
        return m + 1;
    }
    if (T.lt == -1 && T.rt != -1)
    {
        n = depth1(T1[T.rt]);
        return n + 1;
    }
    if (T.lt == -1 && T.rt == -1)
        return 1;
    m = depth1(T1[T.lt]); //�ݹ��������������ȼ�Ϊm
    n = depth1(T1[T.rt]); //�ݹ��������������ȼ�Ϊn
    if (m > n)
        return (m + 1); //�����������Ϊm ��n�Ľϴ��߼�1
    else
        return (n + 1);

}
int depth2(struct TreeNode  T)
{
    int m, n;
    if (T.lt != -1 && T.rt == -1)
    {
        m = depth2(T2[T.lt]);
        return m + 1;
    }
    if (T.lt == -1 && T.rt != -1)
    {
        n = depth2(T2[T.rt]);
        return n + 1;
    }
    if (T.lt == -1 && T.rt == -1)
        return 1;
    m = depth2(T2[T.lt]); //�ݹ��������������ȼ�Ϊm
    n = depth2(T2[T.rt]); //�ݹ��������������ȼ�Ϊn
    if (m > n)
        return (m + 1); //�����������Ϊm ��n�Ľϴ��߼�1
    else
        return (n + 1);

}
//int tonggou(int R1, int R2)
//{
//    if ((R1 == -1) && (R2 == -1))
//    {
//        return 1;  // ��������Ϊ�գ�ͬ��
//    }
//    else if (((R1 == -1) && (R2 != -1)) || ((R1 != -1) && (R2 == -1)))
//    {
//        return 0;//����һ��Ϊ�գ���ͬ��
//    }
//    else if (T1[R1].data != T2[R2].data)
//    {
//        return 0; //�����ݲ�ͬ,��ͬ��
//    }
//    else if ((T1[R1].lt == -1) && (T2[R2].lt == -1))
//    {
//        return tonggou(T1[R1].rt, T2[R2].rt);  //������Ϊ�գ����ж�������
//    }
//
//    else if (((T1[R1].lt != -1) && (T2[R2].lt != -1)) && ((T1[T1[R1].lt].data) == (T2[T2[R2].lt].data)))
//    {
//        //�����������Բ�Ϊ�գ���ֵ���
//        //�ж�������
//        return (tonggou(T1[R1].lt, T2[R2].lt) & tonggou(T1[R1].rt, T2[R2].rt));
//    }
//    else//������������һ����  ����  �Բ�Ϊ�յ�ֵ�����
//    {
//        return (tonggou(T1[R1].lt, T2[R2].rt) & tonggou(T1[R1].rt, T2[R2].lt));
//    }
//}

int tonggou(int x, int y)
{
    if (x == -1 && y == -1)
    {//���������ǡ���ǿսڵ�����ʵ����ͬ��
        return 1;
    }
    else if ((x != -1 && y == -1) || (x == -1 && y != -1))
    {//����һ�����ӽڵ㣬һ��û���ӽڵ�
        return 0;
    }
    else if (T1[x].data != T2[y].data)
    {//����λ�õ���ֵ����ȣ����ж�Ϊֱ��Ϊ��һ����
        return 0;
    }
    else if (tonggou(T1[x].lt, T2[y].lt) && tonggou(T1[x].rt, T2[y].rt))
    {//�����ߵĵ�����ߵ����ұߵĵ����ұߵ�
        return 1;
    }
    else if (tonggou(T1[x].lt, T2[y].rt) && tonggou(T1[x].lt, T2[y].rt))
    {//��ߵĵ����ұߵģ��ұߵĵ�����ߵ�
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    int R1, R2;
    int N1, N2;
    cin >> N1;
    R1 = BuildTree(T1, N1);
    cin >> N2;
    R2 = BuildTree(T2, N2);
    if (tonggou(R1, R2))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    cout << depth1(T1[R1]) << endl << depth2(T2[R2]);
    return 0;
}