#include<iostream>
#include<string.h>
#include<conio.h>
using namespace std;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
typedef int Status;
typedef struct {
    int n; //函数的输入参数
    int returnAddress;
    //构造器及getter、setter
}Data;//节点类型，两个数据域
typedef struct {
    Data* base;
    Data* top;
    int stacksize;
    int stacklength;
}sqstack;
sqstack L;
Status Initstack(sqstack& L, int n)
{
    L.base = (Data*)malloc(n * sizeof(Data));
    if (!L.base)
        exit(OVERFLOW);//内存分配失败
    L.top = L.base;
    L.stacksize = n;
    return OK;
}
Status push(sqstack& L, Data a)
{
    if (L.top - L.base == L.stacksize)//如果栈已经满，则需要重新分配内存
        L.base = (Data*)realloc(L.base, 100 * sizeof(Data));
    if (!L.base)
        exit(OVERFLOW);
    L.top++;
    *L.top = a;
    return OK;
}
Status pop(sqstack& L, Data a)
{
    if (L.top == L.base)
        return ERROR;
    L.top--;
}
long long int model(sqstack& L, Data a)
{
    int num = a.n;
    while (a.n > 1)
    {
        push(L, a);
        a.n--;//只要n>1，一直进栈，模拟递归调用的过程，每一次调用n都要--
    }
    L.top->returnAddress = a.n;//最内层的函数返回值为n的末尾值1
    while (a.n < num)
    {
        Data* p = --L.top;//储存上一层的地址
        L.top++;
        p->returnAddress = L.top->n * L.top->returnAddress;//计算结果
            pop(L, a);//出栈，
        a.n++;//回溯
    }
    return L.base->returnAddress;//最后得到结果
}
int main()
{
    int n;
    Data a;
    cout << "请输入阶乘数n：" << endl;
    cin >> n;
    a.n = n;
    Initstack(L, n);
    cout << model(L, a);
}