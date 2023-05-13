/*************************************************************
����һ��n*m��0 1����1��ʾ��λ���ж�����0��ʾ��λ��û�ж�����������������ͨ��1����һ�����򣬽��ھ����Ե��ͨ�Ĳ����������������������㷨��ϸ�������ϻᾭ���õ���

�����������ݣ�0<=n,m<=1000

���ر��벢����p44.cpp���������������

����
��1��2��������n��m, ��ʾҪ����ľ�������������
��2��n+1��Ϊn*m�ľ���ÿ��Ԫ�ص�ֵΪ0��1��
���
1�У�����������
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

int X[] = { 0,0,1,-1 };        //������������
int Y[] = { 1,-1,0,0 };
int Map[1000][1000];

bool inq[1000][1000] = { false };                //�ж�Ԫ���Ƿ����

bool judge(int x, int y, int m, int n)
{
    if (x >= m || x < 0 || y >= n || y < 0) return false;
    if (inq[x][y] == true || Map[x][y] == 0) return false;
    //������������� ������
    return true;
}

void bfs(int x, int y, int m, int n)
{
    queue<nod>q;        //nod�Ͷ���
    node.x = x, node.y = y;    //ʵ�δ���
    q.push(node);
    inq[x][y] = true;
    while (!q.empty())
    {
        nod top = q.front();        //ȡ��ջ��
        q.pop();                    //ջ����ջ
        for (int i = 0; i < 4; i++)    //�ĸ�����
        {
            int newx = top.x + X[i];
            int newy = top.y + Y[i];
            if (judge(newx, newy, m, n))        //���˵�������������Ҫ����
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
    int ans = 0;        //��ſ���
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