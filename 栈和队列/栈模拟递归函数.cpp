#include<iostream>
#include<string.h>
#include<conio.h>
using namespace std;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
typedef int Status;
typedef struct {
    int n; //�������������
    int returnAddress;
    //��������getter��setter
}Data;//�ڵ����ͣ�����������
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
        exit(OVERFLOW);//�ڴ����ʧ��
    L.top = L.base;
    L.stacksize = n;
    return OK;
}
Status push(sqstack& L, Data a)
{
    if (L.top - L.base == L.stacksize)//���ջ�Ѿ���������Ҫ���·����ڴ�
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
        a.n--;//ֻҪn>1��һֱ��ջ��ģ��ݹ���õĹ��̣�ÿһ�ε���n��Ҫ--
    }
    L.top->returnAddress = a.n;//���ڲ�ĺ�������ֵΪn��ĩβֵ1
    while (a.n < num)
    {
        Data* p = --L.top;//������һ��ĵ�ַ
        L.top++;
        p->returnAddress = L.top->n * L.top->returnAddress;//������
            pop(L, a);//��ջ��
        a.n++;//����
    }
    return L.base->returnAddress;//���õ����
}
int main()
{
    int n;
    Data a;
    cout << "������׳���n��" << endl;
    cin >> n;
    a.n = n;
    Initstack(L, n);
    cout << model(L, a);
}