#include<iostream>
#include<string>
#include<stack>
using namespace std;
int map[6][6] =
{ 
	{0,0,0,0,0,0},
    {0,0,1,1,0,1},
    {0,1,0,1,0,1},
    {0,1,1,0,1,1},
    {0,0,0,1,0,1},
    {0,1,1,1,1,0},
};
int cop[6][6];
int ans[9] = { 0 };
int cnt = 0;
stack<int> T;
void Hierholzer(int i)
{
    int j;
    for ( j = 1;j <= 5;j++)
    {
        if (cop[i][j] == 1)
        {
            cop[i][j] = 0;
            cop[j][i] = 0; 
            Hierholzer(j);
            T.push(j);
        }
    }
    
}
int main()
{
   
    for (int i = 0;i < 6;i++)
    {
        for (int j = 0;j < 6;j++)
        {
            cop[i][j] = map[i][j];
        }
    }
    for (int n = 1;n <= 5;n++)
    {
        Hierholzer(n);
        cout << n;
        while (T.empty() == 0)
        {
            cout << T.top();
            T.pop();
        }
        cout << endl;
        for (int i = 0;i < 6;i++)
        {
            for (int j = 0;j < 6;j++)
            {
                cop[i][j] = map[i][j];
            }
        }
        memset(ans, 0, sizeof(ans));
    }
    return 0;
    
}

