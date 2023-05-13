#include<iostream>
#include<iomanip>
using namespace std;
int sum = 0;
#define inf 99999
typedef int AdjMatrix[100][100];
typedef struct  {
	int vex[100];
	AdjMatrix arcs;
	int vexnum, arcnum;
}MGraph;
MGraph G;
 struct {
	int is_visit;
	int lowcost;
}closedge[100];
void input()
{
	cin >> G.vexnum;
	for (int i = 0;i < G.vexnum;i++)
		G.vex[i] = i+1;
	for (int i=0;i < G.vexnum;i++)
	{
		for (int j = 0;j < G.vexnum;j++)
			cin >> G.arcs[i][j];
	}
	cin >> G.arcnum;
	for (int i = 0;i < G.arcnum;i++)
	{
		int t1, t2;
		cin >> t1 >> t2;
		G.arcs[t1 - 1][t2 - 1] = 0;
		G.arcs[t2 - 1][t1 - 1] = 0;
	}
}
void MST_PRIM(MGraph& G)
{
	int u;
	for (int i = 0;i < G.vexnum;i++)
	{
		closedge[i].is_visit = 0;
		closedge[i].lowcost = G.arcs[0][i];
	}

	closedge[0].is_visit = 1;
	for (int i = 0;i < G.vexnum-1;i++)
	{
		int min = inf;
		
		for (int j = 0;j < G.vexnum;j++)
		{
			if (closedge[j].is_visit == 0 && min > closedge[j].lowcost)
			{
				min = closedge[j].lowcost;
				u = j;
			}
		}
		closedge[u].is_visit = 1;
		sum += closedge[u].lowcost;
		for (int m = 0;m < G.vexnum;m++)
		{
			if (closedge[m].is_visit == 0 && closedge[m].lowcost > G.arcs[u][m])
			{
				closedge[m].lowcost = G.arcs[u][m];
			}
		}
	}
	
}
int main()
{
	input();
	MST_PRIM(G);
	cout << sum;
	return 0;
}