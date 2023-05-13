#include <iostream>
#include <cstring>
#include <queue>
#include <iomanip>

using namespace std;

const int maxn = 2000;
typedef struct ArcNode {
    int adjvex;
    struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode {
    int data;
    ArcNode* firstarc;
}VNode, Adjlist[10000];
typedef struct {
    Adjlist vertices;
    int vexnum, arcnum;
}ALGraph;
ALGraph G;
int visit[10000] = { 0 };
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
        ArcNode* t1, * t2;
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
        q = (ArcNode*)malloc(sizeof(ArcNode));
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
int BFS(int i)
{
    queue <int> q; 
    visit[i] = 1;
    q.push(i);
    int count1 = 1;
    int level = 0;
    int last = i;
    int tail;
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        ArcNode* p = G.vertices[t].firstarc;
        ArcNode* m = p;
        while (p)
        {
           
            if (visit[p->adjvex] == 0)
            {
                q.push(p->adjvex);
                visit[p->adjvex] = 1;
                count1++;
                tail = p->adjvex;
            }
            p = p->nextarc;
        }
        if (t == last)
        {
            level++;
            last = tail;
        }
        if (level == 6)
            break;

    }
    return count1;
}
int main()
{
    input_createadjlist(G);

    int ans = 1;
    for (int i = 1;i <= G.vexnum;i++)
    {
        for (int j = 0;j <= G.vexnum;j++)
            visit[j] = 0;
        ans = BFS(i);
        cout << i << ": " << setiosflags(ios::fixed) << setprecision(2) << (ans * 100.00) /G.vexnum << "%" << endl;
    }

    return 0;
}