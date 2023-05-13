#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode {
	int data;
	ArcNode* firstarc;
}VNode,Adjlist[10000];
typedef struct {
	Adjlist vertices;
	int vexnum, arcnum;
}ALGraph;
ALGraph G;
int visit[10000] = { 0 };
queue<int> Q;
int cnt = 0;
int locateVex(ALGraph G, int a)
{
	int i;
	for ( i = 0;i < G.vexnum;i++)
	{
		if (a == G.vertices[i].data)
			return i;
	}
	if (i == G.vexnum)
	{
		cout << "ERROR!";
		exit(1);
	}
	return 0;
}
void input_createadjlist(ALGraph& G)
{
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0;i < G.vexnum;i++)
	{
		G.vertices[i].data = i;
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0;k < G.arcnum;k++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		ArcNode* t1, *t2;
		ArcNode* p;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = v2;
		p->nextarc = NULL;
		t1 = G.vertices[v1].firstarc;
		if (t1 == NULL)
		{
			G.vertices[v1].firstarc = p;
		}
		else
		{
			while (t1->nextarc != NULL)
			{
				t1 = t1->nextarc;
			}
			t1->nextarc = p;
		}
		ArcNode* q;
		q= (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = v1;
		q->nextarc = NULL;
		t2 = G.vertices[v2].firstarc;
		if (t2 == NULL)
		{
			G.vertices[v2].firstarc = q;
		}
		else
		{
			while (t2->nextarc != NULL)
			{
				t2 = t2->nextarc;
			}
			t2->nextarc = q;
		}
		
		
	}
	return;
}
void dfs(ALGraph& G,int x)
{
	ArcNode* p;
	if(cnt==0)
	cout << G.vertices[x].data;
	else cout << " "<<G.vertices[x].data;
	cnt++;
	visit[x] = 1;
	p = G.vertices[x].firstarc;
	 /*if (p != NULL)
		cout << " ";*/
	while (p)
	{
		if (visit[p->adjvex] == 0)
		{
			dfs(G, p->adjvex);
		}
		p = p->nextarc;
	}
}
void DFStraverse(ALGraph G)
{
	int num=0;
	cout << "{";
	for (int i = 0;i < G.vexnum;i++)
	{
		visit[i] = 0;
	}
	for (int i = 0;i < G.vexnum;i++)
	{
		if (visit[i] == 0)
		{
			if (num >= 1)
			{
				cout<<"}{";
			}
			num++;
			dfs(G, i);
		}
		cnt = 0;
	}
	cout  << "}";
}
void bfs(ALGraph &G,int v)
{
	Q.push(v);
	visit[v] = 1;
	while (Q.empty() != 1)
	{
		v = Q.front();
		Q.pop();
		cout << G.vertices[v].data;
		ArcNode* p = G.vertices[v].firstarc;
		
		while (p)
		{
			if (visit[p->adjvex] == 0)
			{
				Q.push(p->adjvex);
				visit[p->adjvex] = 1;
			}
			p = p->nextarc;
		}
		queue<int> T = Q;
		int flag = 0;
		while (T.empty() == 0)
		{
			ArcNode* t = G.vertices[T.front()].firstarc;
			if (t != NULL)
				flag = 1;
			T.pop();
		}
		if (flag != 0)
			cout << " ";
	}
}
void  BFSTraverse(ALGraph& G)
{
	cout << "{";
	int num=0;
	for (int i = 0;i < G.vexnum;i++)
	{
		if (visit[i] == 0)
		{
			if (num >= 1)
				cout << "}{";
			bfs(G, i);
			num++;
		}
		
			
	}
	cout << "}";
}
int main()
{
	input_createadjlist(G);
	DFStraverse(G);
	for (int i = 0;i < G.vexnum;i++)
	{
		visit[i] = 0;
	}
	cout << endl;
	BFSTraverse(G);
	cout << endl;
	return 0;
}