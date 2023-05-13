#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void Init();
int isEmpty();//�ӿ�
int isFull();//�ж϶���
void left_insert(int);//��߲��롢left-- 
void right_insert(int);//�ұ߲��롢right++ 
void left_delete();//���ɾ����left++ 
void right_delete();//�ұ�ɾ����right-- 

/*ȫ�ֱ���*/
int* queue;//ָ������
int maxSize;//���������
int Size;//��ǰԪ�صĸ���
int Left;//��ָ�룬������������ 
int Right;//��ָ�룬�����ҽ����ҳ� 
int main()
{
	//�����ɾ �Ҳ���ɾ�����У� �����ɾ �Ҳ���ɾ��ջ��

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
		printf("����\n");
	}
	else
	{
		//������д�ʱΪ�� �����һ��Ԫ���ڵ�һ��λ��0��
		if (isEmpty())
		{
			Left = Right = 0;
			queue[Left] = key;
		}
		//������ǲ����һ��Ԫ�أ���Ҫ�����ұ߿�ʼ
		//��һ�β����ָ����ָ��0����Ҫ�ƶ������ұߣ�Ȼ����ָ�����
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
		printf("����\n");
	}
	else
	{
		//������д�ʱΪ�� �����һ��Ԫ���ڵ�һ��λ��0��
		if (isEmpty())
		{
			Left = Right = 0;
			queue[Right] = key;
		}
		//������ǲ����һ��Ԫ�أ���Ҫ�����2��λ�ÿ�ʼ��Ȼ����ָ������
		//������뵽���ұ��ˣ��ʹ��������
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
		printf("���п�\n");
	}
	else
	{
		//���ɾ�������ұ�Ԫ���ˣ���Ҫ��ɾ�����һ�������λ��0����Ԫ��
		if (Left == maxSize - 1)
		{
			
			Left = 0;
			Size--;
		}
		//����������ұߵ�Ԫ�أ���ָ������
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
		printf("���п�\n");
	}
	else
	{
		//���ɾ���������Ԫ���ˣ�ɾ������ָ�����ƶ������ұ�
		if (right == 0)
		{
			
			Right = maxSize - 1;
			Size--;
		}
		//���û��ɾ���������Ԫ�أ���ָ������
		else
		{
			
			Right--;
			Size--;
		}
	}
}
