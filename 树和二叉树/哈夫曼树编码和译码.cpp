#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;
typedef int Status;
typedef struct HTNode {
    char data;
    int weight;
    int lchild, rchild, parent;
}HTNode, * HuffTree;//节点类型定义
HuffTree HT;
char s[100000] = {};//输入的文本
int w[128] = {};//权值数组
int n = 0;
char info[128] = {};//出现的字符
typedef char** HuffmanCode;//二维数组储存每个字符的哈夫曼编码
HuffmanCode HC;
int MostMin = -1;
int SecondMin = -1;
FILE* stream1,*stream2;

int input(char s[],int mode)
{
    int i = 0;
    if(mode==1)
    while (1)
    {
        /*getchar();*/
        char ch;
        ch = getchar();
        if (ch == '\n')
            break;
        s[i] = ch;
        i++;
    }
    else {
        stream1 = fopen("input.txt", "r");
        while (1)
        {
            /*getchar();*/
            char ch;
            ch = getc(stream1);
            if (ch == EOF)
                break;
            s[i] = ch;
            i++;
        }
        fclose(stream1);
    }
    return i;//得到文本的长度
}
void getweight(int l)
{
    int flag = 0;
    for (int i = 0;i < l;i++)
    {
        flag = 0;
        for (int j = 0;j < i;j++)
        {
            if (s[i] == s[j])
            {
                flag = 1;
                w[j]++;//得到权值
                break;
            }
        }
        if (flag == 0)
        {
            w[n]++;
            info[n] = s[i];//如果没有出现过，加入info
            n++;
        }


    }
}
void getmin(HuffTree T, int k)//得到两个权值最小的节点
{
    for (int i = 0; i <= k; i++) {
        if (T[i].weight != 0 && T[i].parent == 0)
        {
            if (MostMin == -1) {
                MostMin = i;
            }
            else if (SecondMin == -1) {
                SecondMin = i;
                if (T[MostMin].weight > T[SecondMin].weight) {
                    swap(SecondMin, MostMin);
                }
            }
            else {
                if (T[i].weight < T[MostMin].weight)
                {
                    SecondMin = MostMin;
                    MostMin = i;
                }
                else if (T[i].weight < T[SecondMin].weight) {
                    SecondMin = i;
                }
            }
        }
    }
}
void CreateHuffTree(HuffTree& HT, HuffmanCode& HC, int* w, int n, int l,int mode)
{
    if (n <= 1)
        return;
    int m = 2 * n - 1;
    HT = (HuffTree)malloc((m+1) * sizeof(HTNode));
    int i;
    HuffTree p;
    for (p = HT, i = 0; i < n; ++i, ++p, ++w)
        //初始化1—n的元素（字符）
    {
        p->weight = *w; p->parent = 0; p->lchild = 0;p->rchild = 0;p->data = info[i];
    }
    for (; i <= m;++i, ++p)//初始化n—m的元素（空）
    {
        p->weight = 0; p->parent = 0; p->lchild = 0; p->rchild = 0;
    }
    for (i = n; i < m;++i)
    {
        getmin(HT, i - 1);
        HT[MostMin].parent = i; HT[SecondMin].parent = i;
        HT[i].lchild = MostMin; HT[i].rchild = SecondMin;
        HT[i].weight = HT[MostMin].weight + HT[SecondMin].weight;//将新节点依次放入n—m个位置中
        MostMin = -1;
        SecondMin = -1;
    }
    HC = (HuffmanCode)malloc((n+1) * sizeof(char *));
    char* cd = (char*)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    cout << "各字符的编码为：" << endl;
    for (i = 0;i < n;++i)
    {
        int start = n - 1;
        for (int c = i, f = HT[c].parent; f != 0; c = f, f = HT[f].parent)//从叶子向根逆向求编码
            if (HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
        HC[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy_s(HC[i], sizeof(&cd[start]), &cd[start]);
        if(mode==1)
        cout << info[i] << ":" << HC[i] << endl;
        else {
            fprintf(stream2, "%c:%s", info[i], HC[i]);
        }
    }
    if (mode == 1)
    {
        cout << endl;
        cout << "转换得到的Huffman编码为：" << endl;
        for (int i = 0;i < l;i++)
        {
            int j = 0;
            while (1)
            {
                if (s[i] == info[j])
                {
                    cout << HC[j];
                    break;
                }
                j++;
            }
        }
    }
    else {
        fputs("转换得到的Huffman编码为：\n", stream2);
        for (int i = 0;i < l;i++)
        {
            int j = 0;
            while (1)
            {
                if (s[i] == info[j])
                {
                    fprintf(stream2, "%s" ,HC[i]);
                    break;
                }
                j++;
            }
        }
    }
    
    free(cd);
}
void decode_Huff(string s, HuffTree &HT, int n,int mode) {
    int i = 0, j = 0, p = 2 * n - 2;
    char a[1000000] = {};
    while (s[i] != '\0') {
        if (s[i] == '0') {
            p = HT[p].lchild;
        }
        else if (s[i] == '1') {
            p = HT[p].rchild;
        }                //判断p是否为叶子结点，是则将对应数据储存进a
        if (HT[p].lchild == 0 && HT[p].rchild == 0) {
            a[j] = HT[p].data; j++;
            p = 2 * n - 2;
        }
        else if (s[i + 1] == '\0' && HT[p].lchild != 0 && HT[p].rchild != 0) {
            cout << "译码失败！" << endl;
            return;
        }
        i++;
    }
    if (mode == 1)
    {
        int k = 0;
        while (a[k] != 0) cout << a[k++];
        cout << endl;
    }
    else {
        int k = 0;
        while (a[k] != 0) 
        fprintf(stream2, "%c", a[k++]);
        fputs("\n", stream2);
    }
    
}

int main()
{
    
    stream2 = fopen("output.txt", "w+");
    cout << "********************" << endl;
    cout << "1.编码" << endl;
    cout << "2.译码" << endl;
    cout << "3.选择编码译码模式(默认为键盘输入)" << endl;
    cout << "0.退出" << endl;
    cout << "********************" << endl;
    int mode = 1;
    while (1)
    {
        cout << "请输入执行的功能编号：" << endl;
        int m;
        cin >> m;
        getchar();
        switch (m)
        {
        case 1: {
              cout << "请输入需要转化的文本:" << endl;
              int l = input(s,mode);
              getweight(l);
              cout << endl;
              CreateHuffTree(HT, HC, w, n, l,mode);
              cout << endl;
              
        }
              break;
        case 2: {string s;
            cout << "请输入需要解压的Huffman编码" << endl;
            cin >> s;
            decode_Huff(s, HT, n,mode);
            cout << endl;
            break;}
        case 3:
            cout << "请输入选择编码模式（1代表键盘输入，2代表文件读写）" << endl;
            cin >> mode;
            break;
        case 0:
            return 0;
            break;

        }
    }
    fclose(stream2);
    
  
    return 0;
}