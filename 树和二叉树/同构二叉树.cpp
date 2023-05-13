/**********************************************************************
* 给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。

现给定两棵树，请你判断它们是否是同构的。并计算每棵树的深度。
输入:
第一行是一个非负整数N1，表示第1棵树的结点数；
随后N行，依次对应二叉树的N个结点（假设结点从0到N?1编号），每行有三项，分别是1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。
接着一行是一个非负整数N2，表示第2棵树的结点数；
随后N行同上描述一样，依次对应二叉树的N个结点。
对于20%的数据，有0<N1=N2<=10
对于40%的数据，有0<=N1=N2<=100
对于100%的数据，有0<=N1,N2<=10100
注意：题目不保证每个结点中存储的字母是不同的。
输出:
共三行。
第一行，如果两棵树是同构的，输出“Yes”，否则输出“No”。
后面两行分别是两棵树的深度。
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
            check[i] = 1;  //初始化
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
        //判断是不是根节点，根节点没有双亲结点
        for (i = 0; i < N; i++)
        {
            if (check[i] == 1)
            {
                return i;  //返回根结点的编号
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
    m = depth1(T1[T.lt]); //递归计算左子树的深度记为m
    n = depth1(T1[T.rt]); //递归计算右子树的深度记为n
    if (m > n)
        return (m + 1); //二叉树的深度为m 与n的较大者加1
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
    m = depth2(T2[T.lt]); //递归计算左子树的深度记为m
    n = depth2(T2[T.rt]); //递归计算右子树的深度记为n
    if (m > n)
        return (m + 1); //二叉树的深度为m 与n的较大者加1
    else
        return (n + 1);

}
//int tonggou(int R1, int R2)
//{
//    if ((R1 == -1) && (R2 == -1))
//    {
//        return 1;  // 两棵树都为空，同构
//    }
//    else if (((R1 == -1) && (R2 != -1)) || ((R1 != -1) && (R2 == -1)))
//    {
//        return 0;//其中一个为空，不同构
//    }
//    else if (T1[R1].data != T2[R2].data)
//    {
//        return 0; //根数据不同,不同构
//    }
//    else if ((T1[R1].lt == -1) && (T2[R2].lt == -1))
//    {
//        return tonggou(T1[R1].rt, T2[R2].rt);  //左子树为空，则判断右子树
//    }
//
//    else if (((T1[R1].lt != -1) && (T2[R2].lt != -1)) && ((T1[T1[R1].lt].data) == (T2[T2[R2].lt].data)))
//    {
//        //两树左子树皆不为空，且值相等
//        //判断其子树
//        return (tonggou(T1[R1].lt, T2[R2].lt) & tonggou(T1[R1].rt, T2[R2].rt));
//    }
//    else//两树左子树有一个空  或者  皆不为空但值不相等
//    {
//        return (tonggou(T1[R1].lt, T2[R2].rt) & tonggou(T1[R1].rt, T2[R2].lt));
//    }
//}

int tonggou(int x, int y)
{
    if (x == -1 && y == -1)
    {//如果两个都恰好是空节点则其实是相同的
        return 1;
    }
    else if ((x != -1 && y == -1) || (x == -1 && y != -1))
    {//两边一个有子节点，一个没有子节点
        return 0;
    }
    else if (T1[x].data != T2[y].data)
    {//两个位置的数值不相等，则判定为直接为不一样的
        return 0;
    }
    else if (tonggou(T1[x].lt, T2[y].lt) && tonggou(T1[x].rt, T2[y].rt))
    {//如果左边的等于左边的且右边的等于右边的
        return 1;
    }
    else if (tonggou(T1[x].lt, T2[y].rt) && tonggou(T1[x].lt, T2[y].rt))
    {//左边的等于右边的，右边的等于左边的
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