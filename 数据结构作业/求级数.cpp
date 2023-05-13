
/****************************************
* 若干行，在每一行中给出整数N和A的值，（1<=N<=150，0<=A<=15）

对于20%的数据，有 1<=N<=12，0<=A<=5

对于40%的数据，有1<=N<=18，0<=A<=9

对于100%的数据，有1<=N<=150，0<=A<=15

从右上方下载p95.py并运行以生成随机测试数据

输出：

对于每一行，在一行中输出级数A+2A2+3A3+。。。+NAN =的整数值
*****************************************/
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
typedef int Status;
string add(string str1, string str2)//高精度加法
{
    string str;
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 < len2)
    {
        for (int i = 1;i <= len2 - len1;i++)
            str1 = "0" + str1;
    }
    else
    {
        for (int i = 1;i <= len1 - len2;i++)
            str2 = "0" + str2;
    }
    len1 = str1.length();
    int jinwei = 0;
    int temp;
    for (int i = len1 - 1;i >= 0;i--)
    {
        temp = str1[i] - '0' + str2[i] - '0' + jinwei;
        jinwei = temp / 10;
        temp %= 10;
        str = char(temp + '0') + str;
    }
    if (jinwei != 0)  str = char(jinwei + '0') + str;
    return str;
}
string mul(string str1, string str2)
{
    string str;
    int len1 = str1.length();
    int len2 = str2.length();
    string tempstr;
    for (int i = len2 - 1;i >= 0;i--)
    {
        tempstr = "";
        int temp = str2[i] - '0';
        int t = 0;
        int cf = 0;
        if (temp != 0)
        {
            for (int j = 1;j <= len2 - 1 - i;j++)
                tempstr += "0";
            for (int j = len1 - 1;j >= 0;j--)
            {
                t = (temp * (str1[j] - '0') + cf) % 10;
                cf = (temp * (str1[j] - '0') + cf) / 10;
                tempstr = char(t + '0') + tempstr;
            }
            if (cf != 0) tempstr = char(cf + '0') + tempstr;
        }
        str = add(str, tempstr);
    }
    str.erase(0, str.find_first_not_of('0'));
    return str;
}
int main()
{

    int i, j, N, A;
    cin >> N >> A;
    string s = "0", s1, s2, result = "0";

    for (int i = 1;i <= N;i++)
    {
        s1 = to_string(A);
        s = s1;
        for (int j = 1;j < i;j++)
        {
            s = mul(s, s1);
        }
        s2 = to_string(i);
        s2 = mul(s2, s);
        result = add(s2, result);

    }
    cout << result;
    return 0;

}