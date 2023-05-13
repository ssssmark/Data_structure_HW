#include<iostream>
#include<stack>
using namespace std;
using namespace std;
typedef struct ArcNode {
	int adjvex;
	int time;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode {
	int data;
	int indegree;
	int time;
	ArcNode* firstarc;
}VNode, Adjlist[101];
typedef struct {
	Adjlist vertices;
	int vexnum, arcnum;
}ALGraph;
ALGraph G;
int ve[100], vl[100];
int e[100], l[100];
stack<int> L;
stack<int> T;
void input(ALGraph& G)
{
	cin >> G.vexnum;
	for (int i = 1;i <= G.vexnum;i++)
	{
		G.vertices[i].data= i;
		G.vertices[i].indegree = 0;
		G.vertices[i].firstarc = NULL;
	}
	for (int i = 1;i <=G.vexnum;i++)
	{
		cin >> G.vertices[i].time;
		int num;
		cin >> num;
		for (int j = 1;j <=num;j++)
		{
			int start;
			cin >> start;
			ArcNode* p, * t;
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			p->nextarc = NULL;
			p->time = 0;
			t = G.vertices[start].firstarc;
			if (t == NULL)
			{
				G.vertices[start].firstarc = p;
			}
			else
			{
				while (t->nextarc != NULL)
				{
					t = t->nextarc;
				}
				t->nextarc = p;
			}
			G.vertices[i].indegree++;
		}
	}
	for (int i = 1;i <= G.vexnum;i++)
	{
		ArcNode* p = G.vertices[i].firstarc;
		while (p)
		{
			p->time = G.vertices[p->adjvex].time;
			p = p->nextarc;
		}
	}
}
int TopologicalOrder(ALGraph& G)
{
	for (int i = 1;i <= G.vexnum;i++)
	{
		ve[i] = G.vertices[i].time;
	}
	for (int i = 1;i <= G.vexnum;i++)
	{
		if (G.vertices[i].indegree == 0)
			L.push(i);
	}
	int count = 0;
	while (L.empty() == 0)
	{
		int x = L.top();
		L.pop();
		T.push(x);
		count++;
		for (ArcNode* p = G.vertices[x].firstarc;p;p = p->nextarc)
		{
			int k;
			k = p->adjvex;
			G.vertices[k].indegree--;
			if (G.vertices[k].indegree == 0)
				L.push(k);
			if (ve[x] + p->time > ve[k])
				ve[k] = ve[x]+p->time;
		}
	}
	if (count < G.vexnum) return 0;
	return 1;
}
int criticalevent(ALGraph& G)
{
	if (!TopologicalOrder(G)) return 0;
	int max = 0;
	for (int i = 1;i <= G.vexnum;i++)
	{
		if(max<ve[i])
			max=ve[i];
		
	}
	for (int i = 1;i <= G.vexnum;i++)
	{
		vl[i] = max;
	}
	while (T.empty() == 0)
	{
		int j = T.top();
		T.pop();
		ArcNode* p = G.vertices[j].firstarc;
		if (p == NULL)
		{
			vl[j] = max;
		}
		else
		for ( p = G.vertices[j].firstarc;p;p = p->nextarc)
		{
			int k = p->adjvex;
			int dut = p->time;
			if (vl[k] - dut < vl[j]) 
				vl[j] = vl[k] - dut;
		}
		
	}
	for (int j = 1;j <= G.vexnum;++j)
	{
		cout << ve[j] << " ";
		ArcNode* p=G.vertices[j].firstarc;
		if (p == NULL)
		{
			if (ve[j] == max)
				cout << "1" << endl;
			else cout << "0" << endl;
		}
		else
		{
			int flag = 0;
			for (p = G.vertices[j].firstarc;p;p = p->nextarc)
			{
				int k = p->adjvex;
				int dut = p->time;
				int ee = ve[j];
				int el = vl[k] - dut;
				if (ee == el)
				{
					cout << 1 <</*" "<<ee <<" " << el <<*/ endl;
					break;
				}
				
			}
			if (p == NULL)
				cout << 0 << endl;
		}
	}
	return 0;
}
int main()
{
	input(G);
	criticalevent(G);
	return 0;
}