#include<iostream>
using namespace std;
int n, m, s, t;
int arcs[10005][10005] = { 1000000 };
int dis[1000] = { 1000000 };
int visit[1000] = { 0 };
void shortestpath(int s)
{
	for (int i = 1;i <=n;i++)
	{
		dis[i] = arcs[s][i];
	}
	for (int i = 1;i < n;i++)
	{
		int mins = 1000000;
		int index = 0;
		for (int j = 1;j <=n;j++)
		{
			if (visit[j] == 0 && dis[j] < mins)
			{
				mins = dis[j];
				index = j;
			}
			visit[index] = 1;//选定距离当前集合最短路点

		}
		for (int j = 1;j <= n;j++) {
			dis[j] = min(dis[j], arcs[j][index] + dis[index]);//更新最短距离
		}
	}
	
}
int main()
{
	cin >> n >> m;
	int s, t;
	cin >> s >> t;
	for (int i = 0;i < m;i++)
	{
		int a, b;
		int v;
		cin >> a >> b>>v;
		arcs[a][b] = v;
		arcs[b][a] = v;
	}
	for (int i = 1;i <= n;i++)    //置对角线为0
		arcs[i][i] = 0;
	if (s == t)
		cout << 0;
	else
	{
		shortestpath(s);
		cout << dis[t];
	}
	
	return 0;
}