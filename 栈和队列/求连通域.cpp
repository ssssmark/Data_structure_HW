/*************************************************************
输入一个n*m的0 1矩阵，1表示该位置有东西，0表示该位置没有东西。所有四邻域联通的1算作一个区域，仅在矩阵边缘联通的不算作区域。求区域数。此算法在细胞计数上会经常用到。

对于所有数据，0<=n,m<=1000

下载编译并运行p44.cpp生成随机测试数据

输入
第1行2个正整数n，m, 表示要输入的矩阵行数和列数
第2—n+1行为n*m的矩阵，每个元素的值为0或1。
输出
1行，代表区域数
*********************************************/
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include <iostream>
#include<string>
#include<queue>
using namespace std;
struct nod
{
    int x, y;
}node;

int X[] = { 0,0,1,-1 };        //方向增量数组
int Y[] = { 1,-1,0,0 };
int Map[1000][1000];

bool inq[1000][1000] = { false };                //判断元素是否入队

bool judge(int x, int y, int m, int n)
{
    if (x >= m || x < 0 || y >= n || y < 0) return false;
    if (inq[x][y] == true || Map[x][y] == 0) return false;
    //都不符合情况， 返回真
    return true;
}

void bfs(int x, int y, int m, int n)
{
    queue<nod>q;        //nod型队列
    node.x = x, node.y = y;    //实参传递
    q.push(node);
    inq[x][y] = true;
    while (!q.empty())
    {
        nod top = q.front();        //取出栈顶
        q.pop();                    //栈顶出栈
        for (int i = 0; i < 4; i++)    //四个方向
        {
            int newx = top.x + X[i];
            int newy = top.y + Y[i];
            if (judge(newx, newy, m, n))        //如果说遍历的这个点需要访问
            {
                node.x = newx, node.y = newy;
                q.push(node);
                inq[newx][newy] = true;
            }
        }
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    for (int i = 0;i < m;i++)
    {
        for (int j = 0;j < n;j++)
            cin >> Map[i][j];
    }
    int ans = 0;        //存放块数
    for (int i = 1; i < m - 1; i++)
        for (int j = 1; j < n - 1; j++)
        {
            if (Map[i][j] == 1 && inq[i][j] == false)
            {
                ans++;
                bfs(i, j, m, n);
            }
        }
    cout << ans;
    return 0;
}