#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
typedef int Status;
#define N 512
struct index{
    char name;
    int val;
};

struct Bitree {
    char val;
    Bitree* lchild;
    Bitree* rchild;
    Bitree() : val(0), lchild(NULL), rchild(NULL) {};
    Bitree(char ch) : val(ch), lchild(NULL), rchild(NULL) {};
};

int pri(char ch)
{
    if (ch == '(')
        return 1;
    if (ch == '*' || ch == '/')
        return 3;
    return 2;
}

string trans(string t)
{
    string s = "";
    int i = 0, l = t.length(), top = -1;
    char stack[N];
    while (i < l)
    {
        if (t[i] != '+' && t[i] != '-' && t[i] != '*' && t[i] != '/' && t[i] != '(' && t[i] != ')')
            s += t[i];
        else
        {
            if (t[i] == '(')
                stack[++top] = t[i];
            else if (t[i] == ')')
            {
                while (stack[top] != '(')
                {
                    s += stack[top];
                    top--;
                }
                top--;
            }
            else
            {
                if (top == -1)
                    stack[++top] = t[i];
                else
                {
                    while (top > -1 && pri(stack[top]) >= pri(t[i]))
                    {
                        s += stack[top];
                        top--;
                    }
                    stack[++top] = t[i];
                }
            }
        }
        i++;
    }
    while (top > -1)
    {
        s += stack[top];
        top--;
    }
    return s;
}

Bitree* post_to_tree(string t)
{
    Bitree* p;
    int i, l = t.length(), top = -1;
    Bitree* stack[N];
    for (i = 0; i < l; i++)
    {
        p = new Bitree(t[i]);
        if (t[i] != '+' && t[i] != '-' && t[i] != '*' && t[i] != '/')
            stack[++top] = p;
        else
        {
            p->lchild = stack[top - 1];
            p->rchild = stack[top];
            top--;
            stack[top] = p;
        }
    }
    return stack[0];
}

int depth(Bitree* r)
{
    if (!r)
        return 0;
    int left = depth(r->lchild);
    int right = depth(r->rchild);
    return max(left, right) + 1;
}

void print(int n, char ch)
{
    while (n--)
        cout << ch;
}

void printtree(Bitree* root)
{
    int n = depth(root);

    char* r[6];
    Bitree* tmp = root, * queue[N], * p;
    int head = 0, tail = 0, i, t, h, j = 0;
    queue[tail] = root;
    tail++;
    while (j < n)
    {
        r[j] = new char[256];
        for (i = head; i < tail; i++)
            r[j][i - head] = queue[i]->val;
        r[j][i - head] = '\0';
        t = tail;
        h = head;
        head = tail;
        for (i = h; i < t; i++)
        {
            if (queue[i]->lchild)
                queue[tail++] = queue[i]->lchild;
            else
            {
                p = new Bitree(' ');
                queue[tail++] = p;
            }
            if (queue[i]->rchild)
                queue[tail++] = queue[i]->rchild;
            else
            {
                p = new Bitree(' ');
                queue[tail++] = p;
            }
        }
        j++;
    }

    int div = 1, k, _n = 1;
    for (k = 0; k < n; k++)
        _n *= 2;
    for (i = 0; i < n; i++)
    {
        div *= 2;
        for (j = 0; r[i][j] != '\0'; j++)
        {
            print(j == 0 ? _n / div - 1 : _n * 2 / div - 1, ' ');
            cout << r[i][j];
        }
        cout << endl;
        if (i < n - 1)
        {
            for (j = 0; r[i][j] != '\0'; j++)
            {
                print(j == 0 ? _n / div - 2 : _n * 2 / div - 3, ' ');
                if (r[i + 1][2 * j] != ' ' && r[i + 1][2 * j + 1] != ' ')
                    cout << "/ \\";
                else
                    cout << "   ";
            }
            cout << endl;
        }
    }
}

int cal(string s, index p[], int num)
{
    int re[10], i, top = -1, j;
    char tmp;
    for (i = 0; i < s.length(); i++)
    {
        tmp = s[i];
        if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/')
        {
            if (tmp == '+')
                re[top - 1] += re[top];
            else if (tmp == '-')
                re[top - 1] -= re[top];
            else if (tmp == '*')
                re[top - 1] *= re[top];
            else
                re[top - 1] /= re[top];
            top--;
        }
        else
        {
            for (j = 0; j < num; j++)
                if (p[j].name == tmp)
                {
                    re[++top] = p[j].val;
                    break;
                }
        }
        tmp = '\0';
    }
    return re[0];
}

void _delete(Bitree* root)
{
    int top = -1;
    Bitree* tmp[100], * t;
    if (!root)
        return;
    tmp[++top] = root;
    while (top > -1)
    {
        t = tmp[top];
        top--;
        if (t->lchild)
            tmp[++top] = t->lchild;
        if (t->rchild)
            tmp[++top] = t->rchild;
        delete t;
    }
}

int main()
{
    string t, s;
    int num, i;
    index* p;
    cin >> t >> num;
    p = new index[num];
    for (i = 0; i < num; i++)
        cin >> p[i].name >> p[i].val;
    Bitree* root;
    s = trans(t);
    root = post_to_tree(s);
    cout << s << endl;
    printtree(root);
    cout << cal(s, p, num) << endl;
    _delete(root);
    delete[] p;
    return 0;
}