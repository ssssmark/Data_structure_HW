#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void Init();
int isEmpty();//队空
int isFull();//判断队满
void left_insert(int);//左边插入、left-- 
void right_insert(int);//右边插入、right++ 
void left_delete();//左边删除、left++ 
void right_delete();//右边删除、right-- 

/*全局变量*/
int* queue;//指针数组
int maxSize;//数组的容量
int Size;//当前元素的个数
int Left;//左指针，用于左进、左出 
int Right;//右指针，由于右进、右出 
int main()
{
	//左插右删 右插左删（队列） 左插左删 右插右删（栈）

	Init();
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
			int x;
			cin >> x;
			left_insert(x);
			break;
		case 2:
			int y;
			cin >> y;
			right_insert(y);
			break;
		case 3:
			cout << queue[Left] << endl;
			break;
		case 4:
			cout << queue[Right] << endl;
			break;
		case 5:
			left_delete();
			break;
		case 6:
			right_delete();
			break;
		}
	}
	return 0;
}


void Init()
{
	queue = (int*)malloc(1000000 * sizeof(int));
	maxSize = 1000000;
	Size = 0;
}

int isEmpty()
{
	if (Size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int isFull()
{
	if (Size == maxSize)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void left_insert(int key)
{
	if (isFull())
	{
		printf("队满\n");
	}
	else
	{
		//如果队列此时为空 插入第一个元素在第一个位置0处
		if (isEmpty())
		{
			Left = Right = 0;
			queue[Left] = key;
		}
		//如果不是插入第一个元素，就要从最右边开始
		//第一次插入后，指针仍指向0，需要移动到最右边，然后左指针左减
		else
		{
			if (Left == 0)
			{
				Left = maxSize;
			}
			queue[--Left] = key;
		}
		Size++;
	}
}
void right_insert(int key)
{
	if (isFull())
	{
		printf("队满\n");
	}
	else
	{
		//如果队列此时为空 插入第一个元素在第一个位置0处
		if (isEmpty())
		{
			Left = Right = 0;
			queue[Right] = key;
		}
		//如果不是插入第一个元素，就要从最第2个位置开始，然后右指针右移
		//如果插入到最右边了，就代表插满了
		else
		{
			if (Right == maxSize - 1)
			{
				Right = -1;
			}
			queue[++Right] = key;

		}
		Size++;
	}
}

void left_delete()
{
	if (isEmpty())
	{
		printf("队列空\n");
	}
	else
	{
		//如果删除到最右边元素了，就要再删除最后一个存放在位置0处的元素
		if (Left == maxSize - 1)
		{
			
			Left = 0;
			Size--;
		}
		//如果不是最右边的元素，左指针右移
		else
		{
			
			Left++;
			Size--;
		}
	}
}

void right_delete()
{
	if (isEmpty())
	{
		printf("队列空\n");
	}
	else
	{
		//如果删除到最左边元素了，删除后右指针又移动到最右边
		if (right == 0)
		{
			
			Right = maxSize - 1;
			Size--;
		}
		//如果没有删除到最左边元素，右指针左移
		else
		{
			
			Right--;
			Size--;
		}
	}
}
