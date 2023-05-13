#include<iostream>
#include<string.h>
#include<conio.h>
#include<iomanip>
#include<math.h>
using namespace std;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
typedef int Status;
struct course;
struct student {
	char name[20];
	long int no;
	char gender;
	course* cour;
	int cournum = 0;
};
struct course {
	char classname[20];
	long int classno;
	float credit;
	student classstu[200];
	int classstunum = 0;
};
typedef struct StuNode {
	student stu;
	struct StuNode* next;
}StuNode, * Stulist;
typedef struct CourseNode {
	course cou;
	struct CourseNode* next;
}CourseNode, * Courselist;
Stulist L;
Courselist Q;
Status Initliststu(Stulist& L)
{
	L = (Stulist)malloc(sizeof(StuNode));
	if (!L)
		exit(OVERFLOW);
	L->next = NULL; /* ָ����Ϊ��*/
	L->stu.cour = (course*)malloc(200 * sizeof(course));
	if (!L->stu.cour) exit(OVERFLOW);
	L->stu.cournum = 0;
	return OK;
}
Status Initlistcourse(Courselist& Q)
{
	Q = (Courselist)malloc(sizeof(CourseNode));
	if (!Q) exit(OVERFLOW);
	Q->next = NULL;
	Q->cou.classstunum = 0;
	return OK;
}
Status Insertstu(Stulist& L)//����ѡ��ϵͳ��������˳�򣬲������ֱ��ִ�е����һ������
{
	Stulist p;
	p = (Stulist)malloc(sizeof(StuNode));
	if (!p) exit(OVERFLOW);
	while (1) {
		cout << "������ֱ��������ѧ����ѧ�š��������Ա�" << endl;
		cin >> p->stu.no >> p->stu.name >> p->stu.gender;
		if (cin.good() == 1 && (p->stu.gender == 'm' || p->stu.gender == 'M' || p->stu.gender == 'f' || p->stu.gender == 'F'))
			break;
		cin.clear();
		cin.ignore();
	}
	L->next = p;
	p->next = NULL;
	p->stu.cournum = 0;
	p->stu.cour = (course*)malloc(3000 * sizeof(course));
	cout << "����ɹ��������������" << endl;
	_getch();
}
Status Insertcourse(Courselist& Q)//����ѡ��ϵͳ��������˳�򣬲������ֱ��ִ�е����һ������
{
	Courselist p;
	p = (Courselist)malloc(sizeof(CourseNode));
	if (!p) exit(OVERFLOW);
	while (1) {
		cout << "������ֱ��������γ̵Ŀκš��γ�����ѧ��" << endl;
		cin >> p->cou.classno >> p->cou.classname >> p->cou.credit;
		if (cin.good() == 1)
			break;
		cin.clear();
		cin.ignore();
	}

	Q->next = p;
	p->cou.classstunum = 0;
	cout << "����ɹ��������������" << endl;
	_getch();
}
void searchcou(Courselist& Q)
{
	cout << "��ѡ������ֶ�" << endl;
	cout << "1.�κ�" << endl;
	cout << "2.�γ���" << endl;
	int i;
	while (1) {
		cin >> i;
		if ((i == 1 || i == 2) && cin.good() == 1)
			break;
		cout << "�����������������" << endl;
		cin.clear();
		cin.ignore();
	}
	int j;
	Courselist q = Q;
	switch (i)
	{
	case 1:
		long int num;
		cout << "�������ѯĿ��κţ�" << endl;
		while (1)
		{
			cin >> num;
			if (cin.good() == 1)
				break;
			cout << "�����������������" << endl;
		}
		while (q != NULL)
		{
			if (q->cou.classno == num)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "��ѯʧ�ܣ�û���ҵ���ؿγ���Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ����γ���Ϣ����:" << endl;
			cout << "�κ�:" << q->cou.classno << endl;
			cout << "�γ���:" << q->cou.classname << endl;
			cout << "ѧ��" << q->cou.credit << endl;
			cout << "ѡ��ѧ��:" << endl;
			int m = 0;
			while (m < q->cou.classstunum)
			{
				cout << "����:" << q->cou.classstu[m].name << " ѧ�ţ�" << q->cou.classstu[m].no << " �Ա�" << q->cou.classstu[m].gender << endl;
				m++;
			}
		}
		break;
	case 2:
		char cname[20];
		cout << "�������ѯĿ��γ�����" << endl;
		while (1)
		{
			cin >> cname;
			if (cin.good() == 1)
				break;
			cout << "�����������������" << endl;
		}
		while (q != NULL)
		{
			if (strcmp(q->cou.classname, cname) == 0)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "��ѯʧ�ܣ�û���ҵ���ؿγ���Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ����γ���Ϣ����:" << endl;
			cout << "�κ�:" << q->cou.classno << endl;
			cout << "�γ���:" << q->cou.classname << endl;
			cout << "ѧ��" << q->cou.credit << endl;
			cout << "ѡ��ѧ��:" << endl;
			int m = 0;
			while (m < q->cou.classstunum)
			{
				cout << "����:" << q->cou.classstu[m].name << "  ѧ�ţ�" << q->cou.classstu[m].no << "  �Ա�" << q->cou.classstu[m].gender << endl;
				m++;
			}
		}
		break;

	}
	_getch();
}
void searchstu(Stulist& L)
{
	cout << "��ѡ������ֶ�" << endl;
	cout << "1.ѧ��" << endl;
	cout << "2.����" << endl;
	int i;
	Stulist q = L;
	while (1) {
		cin >> i;
		if ((i == 1 || i == 2) && cin.good() == 1)
			break;
		cout << "�����������������" << endl;
		cin.clear();
		cin.ignore();
	}
	int j;
	switch (i)
	{
	case 1:
		long int num;
		cout << "�������ѯĿ��ѧ�ţ�" << endl;
		cin >> num;

		while (q != NULL)
		{
			if (q->stu.no == num)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "��ѯʧ�ܣ�û���ҵ����ѧ����Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ���ѧ����Ϣ����:" << endl;
			cout << "ѧ��:" << q->stu.no << endl;
			cout << "����:" << q->stu.name << endl;
			cout << "�Ա�" << q->stu.gender << endl;
			cout << "ѡ���б�:" << endl;
			int m = 0;
			while (m < q->stu.cournum)
			{
				cout << "�γ�����" << q->stu.cour[m].classname << "  �κţ�" << q->stu.cour[m].classno << "  �γ�ѧ��" << q->stu.cour[m].credit << endl;
				m++;
			}
		}
		break;
	case 2:
		char sname[20];
		cout << "������Ŀ��ѧ������" << endl;
		cin >> sname;
		while (q != NULL)
		{
			if (strcmp(q->stu.name, sname) == 0)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "��ѯʧ�ܣ�û���ҵ����ѧ����Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ���ѧ����Ϣ����:" << endl;
			cout << "ѧ��:" << q->stu.no << endl;
			cout << "����:" << q->stu.name << endl;
			cout << "�Ա�" << q->stu.gender << endl;
			cout << "ѡ���б�:" << endl;
			int m = 0;
			while (m < q->stu.cournum)
			{
				cout << "�γ���:" << q->stu.cour[m].classname << "   �κţ�" << q->stu.cour[m].classno << "  �γ�ѧ��" << q->stu.cour[m].credit << endl;
				m++;
			}
		}
		break;
	}
	_getch();
}
void delstu(Stulist& L)
{
	cout << "��������Ҫɾ��ѧ����ѧ��" << endl;
	long int delnum;
	char confirm;
	while (1)
	{
		cin >> delnum;
		Stulist p = L, q;
		while (p->next->stu.no != delnum && p->next != NULL)
			p++;
		if (p->next == NULL)
		{
			cout << "��ѯ������ѧ����Ϣ������������" << endl;
			continue;
		}
		else {
			q = p->next;
			cout << "��Ҫɾ����ѧ��Ϊ" << endl;
			cout << "������" << q->stu.name << " ѧ�ţ�" << q->stu.no << " �Ա�" << q->stu.gender << endl;
			cout << "���Ƿ�ȷ��ɾ����(Y/N)";

			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				p->next = q->next;
				free(q);
				cout << " ɾ���ɹ��������������" << endl;
			}
			else if (confirm == 'N' || confirm == 'n' && cin.good() == 1)
			{
				cout << "��������˳�" << endl;
			}
			_getch();
			break;
		}

	}

}
void delcou(Courselist& Q)
{
	cout << "��������Ҫɾ���γ̵Ŀκ�" << endl;
	long int delclassnum;
	char confirm;
	Courselist p = Q, q;
	while (1)
	{
		cout << "��������Ҫɾ��ѧ����ѧ��" << endl;
		cin >> delclassnum;
		while (p->next->cou.classno != delclassnum && p->next != NULL)
			p++;
		if (p->next == NULL)
		{
			cout << "��ѯ�����˿γ���Ϣ������������" << endl;
			continue;
		}
		else {
			q = p->next;
			cout << "��Ҫɾ���Ŀγ�Ϊ" << endl;
			cout << "�γ�����" << q->cou.classname << " �κţ�" << q->cou.classno << " ѧ��" << q->cou.credit << endl;
			cout << "���Ƿ�ȷ��ɾ����(Y/N)";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				p->next = q->next;
				free(q);
				cout << " ɾ���ɹ��������������" << endl;
			}
			else if (confirm == 'N' || confirm == 'n' && cin.good() == 1)
			{
				cout << "��������˳�" << endl;
			}
			_getch();
			break;
		}

	}
}
int menu()
{
	cout << "*************************************************************" << endl;
	cout << "*                      ѧ��ѡ��ϵͳ                         *" << endl;
	cout << "*                1.��������ѧ����Ϣ                         *" << endl;
	cout << "*                2.��������γ���Ϣ                         *" << endl;
	cout << "*                3.����ѧ����Ϣ                             *" << endl;
	cout << "*                4.ɾ��ѧ����Ϣ                             *" << endl;
	cout << "*                5.����ѧ����Ϣ                             *" << endl;
	cout << "*                6.����γ���Ϣ                             *" << endl;
	cout << "*                7.ɾ���γ���Ϣ                             *" << endl;
	cout << "*                8.���ҿγ���Ϣ                             *" << endl;
	cout << "*                9.ѧ��ѡ��                                 *" << endl;
	cout << "*                10.��ʾѡ������                            *" << endl;
	cout << "*                11.��ʾѧ���α�                            *" << endl;
	cout << "*                0.�˳�                                     *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*************************************************************" << endl;
	int i;
	cout << "������Ҫִ�еĲ���[0-11]:";
	cin >> i;
	return i;
}
void inputstu(Stulist& L)
{
	int i;
	cout << " ��������Ϣ¼���ѧ��������";
	cin >> i;
	cout << " ��ֱ�����ÿ��ѧ����ѧ�š��������Ա�" << endl;
	for (int j = 0;j < i;j++)
	{
		while (1)
		{
			Stulist p;
			p = (Stulist)malloc(sizeof(StuNode));
			p->next = L->next;
			L->next = p;
			cin >> p->stu.no >> p->stu.name >> p->stu.gender;
			p->stu.cournum = 0;
			p->stu.cour = (course*)malloc(100 * sizeof(course));
			if (cin.good() == 1 && (p->stu.gender == 'm' || p->stu.gender == 'M' || p->stu.gender == 'f' || p->stu.gender == 'F'))
				break;
			cout << "������������������ѧ����Ϣ" << endl;
			cin.clear();
			cin.ignore();
		}

	}
	cout << "¼��ɹ��������������...";
	_getch();
}
void inputcourse(Courselist& Q)
{
	int i;
	cout << " ��������Ϣ¼��Ŀγ�������";
	cin >> i;
	cout << " ��ֱ�����ÿ�ڿγ̵Ŀκš��γ�����ѧ��" << endl;
	for (int j = 0;j < i;j++)
	{
		while (1)
		{
			Courselist p;
			p = (Courselist)malloc(sizeof(CourseNode));
			p->next = Q->next;
			Q->next = p;
			cin >> p->cou.classno >> p->cou.classname >> p->cou.credit;
			p->cou.classstunum = 0;
			if (cin.good() == 1)
				break;
			cin.clear();
			cin.ignore();
		}
	}
	cout << "¼��ɹ��������������...";
	_getch();
}
void registercourse(Stulist& L, Courselist& Q)
{
	Stulist p = L;
	Courselist q = Q;
	while (1) {
		cout << "��������Ҫѡ�ε�ѧ��ѧ���Լ��γ̿κţ�";
		long int stunum, coursenum;
		cin >> stunum >> coursenum;
		while (p != NULL)
		{
			if (p->stu.no == stunum)
				break;
			p = p->next;
		}
		if (p == NULL)
			cout << "��ѯ������ѧ����Ϣ������������" << endl;
		while (q != NULL)
		{
			if (q->cou.classno == coursenum)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "��ѯ�����˿γ���Ϣ������������" << endl;
		if (q && p)
			break;
		cin.clear();
		cin.ignore();

	}
	p->stu.cour[p->stu.cournum] = q->cou;
	q->cou.classstu[q->cou.classstunum] = p->stu;
	p->stu.cournum++;
	q->cou.classstunum++;
	cout << "ѡ�γɹ�����������˳�" << endl;
	_getch();
}
void show_stu_list(Courselist& Q)
{
	cout << "��������Ҫ��ѯ�Ŀκ�" << endl;
	long int num;
	cin >> num;
	Courselist p = Q;
	while (p != NULL)
	{
		if (p->cou.classno == num)
			break;
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "�ÿκŲ����ڣ���������˳�" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < p->cou.classstunum;j++)
		{
			cout << "������" << p->cou.classstu[j].name << " ѧ�ţ�" << p->cou.classstu[j].no << " �Ա�" << p->cou.classstu[j].gender << endl;
		}
		cout << "��������˳�" << endl;
		_getch();
	}

}
void show_course_list(Stulist& L)
{
	cout << "��������Ҫ��ѯ��ѧ��ѧ��" << endl;
	long int num;
	Stulist p = L;
	cin >> num;
	while (p != NULL)
	{
		if (p->stu.no == num)
			break;
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "�ÿκŲ����ڣ���������˳�" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < p->stu.cournum;j++)
		{
			cout << "�γ�����" << p->stu.cour[j].classname << " �κţ�" << p->stu.cour[j].classno << " ѧ�֣�" << p->stu.cour[j].credit << endl;
		}
		cout << "��������˳�" << endl;
		_getch();
	}

}
//void print()
//{
//	whi
//	{
//		cout << " ����:" << L.stu[j].name << " ѧ�ţ�" << L.stu[j].no << " �Ա�:" << L.stu[j].gender << endl;
//	}
//	_getch();
//}
int main()
{
	Initliststu(L);
	Initlistcourse(Q);
	while (1)
	{
		int ret = menu();
		/*if (ret == 100)
			print();*/
		if (ret == 0)
			break;
		if (ret == 1)
		{
			inputstu(L);
		}
		else if (ret == 2)
		{
			inputcourse(Q);
		}
		else if (ret == 3)
		{
			Insertstu(L);
		}
		else if (ret == 4)
		{
			delstu(L);
		}
		else if (ret == 5)
		{
			searchstu(L);
		}
		else if (ret == 6)
		{
			Insertcourse(Q);
		}
		else if (ret == 7)
		{
			delcou(Q);

		}
		else if (ret == 8)
		{
			searchcou(Q);
		}
		else if (ret == 9)
		{
			registercourse(L, Q);
		}
		else if (ret == 10)
		{
			show_stu_list(Q);
		}
		else if (ret == 11)
		{
			show_course_list(L);
		}
		system("cls");
	}

	return 0;
}