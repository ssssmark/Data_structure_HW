#include<iostream>
#include<iomanip>
#include<stack>
using namespace std;
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode {
	int data;
	int indegree;
	ArcNode* firstarc;
}VNode, Adjlist[500];
typedef struct {
	Adjlist vertices;
	int vexnum, arcnum;
}ALGraph;
ALGraph Row,Col;
int k;
int rowconditions[10000][2]={0};
int colconditions[10000][2]={0};
int result[500][500]={0};
stack<int> L;
void input()
{
	cin >> k >> Row.arcnum >> Col.arcnum;
	Row.vexnum = Col.vexnum = k;
	for (int i = 1;i <= Row.vexnum;i++)
	{
		Row.vertices[i].data = i;
		Row.vertices[i].firstarc = NULL;
		Row.vertices[i].indegree = 0;
	}
	for (int i = 1;i <= Col.vexnum;i++)
	{
		Col.vertices[i].data = i;
		Col.vertices[i].firstarc = NULL;
		Col.vertices[i].indegree = 0;
	}
	for (int i = 0;i < Row.arcnum;i++)
	{
		cin >> rowconditions[i][0];
		cin >> rowconditions[i][1];
	}
	for (int j = 0;j < Col.arcnum;j++)
	{
		cin >> colconditions[j][0];
		cin >> colconditions[j][1];
	}
	for (int i = 0;i < Row.arcnum;i++)
	{
		ArcNode* p,*t;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = rowconditions[i][1];
		p->nextarc = NULL;
		t = Row.vertices[rowconditions[i][0]].firstarc;
		if (t == NULL)
		{
			Row.vertices[rowconditions[i][0]].firstarc = p;
			
		}
		else
		{
			while (t->nextarc != NULL)
			{
				t = t->nextarc;
			}
			t->nextarc = p;
			
		}
		Row.vertices[rowconditions[i][1]].indegree++;
	}
	for (int i = 0;i < Col.arcnum;i++)
	{
		ArcNode* p, * t;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p)
			return ;
		else
		p->adjvex = colconditions[i][1];
		p->nextarc = NULL;
		t = Col.vertices[colconditions[i][0]].firstarc;
		if (t == NULL)
		{
			Col.vertices[colconditions[i][0]].firstarc = p;
		}
		else
		{
			while (t->nextarc != NULL)
			{
				t = t->nextarc;
			}
			t->nextarc = p;
		}
		Col.vertices[colconditions[i][1]].indegree++;
	}
}
int topologicalsort(ALGraph& G,bool rl)
{
	for (int i = 0;i < G.vexnum;i++)
	{
		if (G.vertices[i].indegree == 0)
		{
			L.push(i);
		}
	}
	int count = 0;
	while (L.empty() == 0)
	{
		int x = L.top();
		L.pop();
		if(rl==0)
		*(result[count]+G.vexnum-1) = x;
		else if (rl == 1)
		{
			int n;
			for ( n = 0;n < G.vexnum;n++)
			{
				if (result[n][G.vexnum - 1] == x)
				{
					result[n][G.vexnum - 1] = 0;
					break;
				}
					
			}
			result[n][count] = x;
		}
		count++;
		ArcNode* p;
		for (p = G.vertices[x].firstarc;p != NULL;p=p->nextarc)
		{
			int k = p->adjvex;
			G.vertices[k].indegree--;
			if (G.vertices[k].indegree == 0)
				L.push(k);
		}
	}
	if (count < G.vexnum)
		return -1;
	else return 0;
}
int main()
{
	
	input();
	if (topologicalsort(Row, 0) == -1)
	{
		cout << -1;
		return 0;
	}
	if (topologicalsort(Col, 1) == -1)
	{
		cout << -1;
		return 0;
	}
	for (int i = 0;i < Row.vexnum;i++)
	{
		for (int j = 0;j < Row.vexnum;j++)
			cout << result[i][j] << " ";
		cout << endl;
	}
	return 0;
}