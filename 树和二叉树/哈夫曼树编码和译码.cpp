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
}HTNode, * HuffTree;//�ڵ����Ͷ���
HuffTree HT;
char s[100000] = {};//������ı�
int w[128] = {};//Ȩֵ����
int n = 0;
char info[128] = {};//���ֵ��ַ�
typedef char** HuffmanCode;//��ά���鴢��ÿ���ַ��Ĺ���������
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
    return i;//�õ��ı��ĳ���
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
                w[j]++;//�õ�Ȩֵ
                break;
            }
        }
        if (flag == 0)
        {
            w[n]++;
            info[n] = s[i];//���û�г��ֹ�������info
            n++;
        }


    }
}
void getmin(HuffTree T, int k)//�õ�����Ȩֵ��С�Ľڵ�
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
        //��ʼ��1��n��Ԫ�أ��ַ���
    {
        p->weight = *w; p->parent = 0; p->lchild = 0;p->rchild = 0;p->data = info[i];
    }
    for (; i <= m;++i, ++p)//��ʼ��n��m��Ԫ�أ��գ�
    {
        p->weight = 0; p->parent = 0; p->lchild = 0; p->rchild = 0;
    }
    for (i = n; i < m;++i)
    {
        getmin(HT, i - 1);
        HT[MostMin].parent = i; HT[SecondMin].parent = i;
        HT[i].lchild = MostMin; HT[i].rchild = SecondMin;
        HT[i].weight = HT[MostMin].weight + HT[SecondMin].weight;//���½ڵ����η���n��m��λ����
        MostMin = -1;
        SecondMin = -1;
    }
    HC = (HuffmanCode)malloc((n+1) * sizeof(char *));
    char* cd = (char*)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    cout << "���ַ��ı���Ϊ��" << endl;
    for (i = 0;i < n;++i)
    {
        int start = n - 1;
        for (int c = i, f = HT[c].parent; f != 0; c = f, f = HT[f].parent)//��Ҷ��������������
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
        cout << "ת���õ���Huffman����Ϊ��" << endl;
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
        fputs("ת���õ���Huffman����Ϊ��\n", stream2);
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
        }                //�ж�p�Ƿ�ΪҶ�ӽ�㣬���򽫶�Ӧ���ݴ����a
        if (HT[p].lchild == 0 && HT[p].rchild == 0) {
            a[j] = HT[p].data; j++;
            p = 2 * n - 2;
        }
        else if (s[i + 1] == '\0' && HT[p].lchild != 0 && HT[p].rchild != 0) {
            cout << "����ʧ�ܣ�" << endl;
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
    cout << "1.����" << endl;
    cout << "2.����" << endl;
    cout << "3.ѡ���������ģʽ(Ĭ��Ϊ��������)" << endl;
    cout << "0.�˳�" << endl;
    cout << "********************" << endl;
    int mode = 1;
    while (1)
    {
        cout << "������ִ�еĹ��ܱ�ţ�" << endl;
        int m;
        cin >> m;
        getchar();
        switch (m)
        {
        case 1: {
              cout << "��������Ҫת�����ı�:" << endl;
              int l = input(s,mode);
              getweight(l);
              cout << endl;
              CreateHuffTree(HT, HC, w, n, l,mode);
              cout << endl;
              
        }
              break;
        case 2: {string s;
            cout << "��������Ҫ��ѹ��Huffman����" << endl;
            cin >> s;
            decode_Huff(s, HT, n,mode);
            cout << endl;
            break;}
        case 3:
            cout << "������ѡ�����ģʽ��1����������룬2�����ļ���д��" << endl;
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