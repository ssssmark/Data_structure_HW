#include<iostream>
#include<string.h>
#include<conio.h>
#include<iomanip>
#include<math.h>
using namespace std;
#define OVERFLOW 3
#define OK 1
#define ERROR -1
#define STU_INIT_SIZE 40000
#define COURSE_INIT_SIZE 3000
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
typedef struct {
	student* stu;
	int listsize;
	int length;
}Stulist;
typedef struct {
	course* cou;
	int listsize;
	int length;
}Courselist;
Stulist L;
Courselist Q;
Status Initliststu(Stulist& L)
{
	L.stu = (student*)malloc(STU_INIT_SIZE
		* sizeof(student));
	L.stu->cour = (course*)malloc(COURSE_INIT_SIZE * sizeof(course));
	if (!L.stu) exit(OVERFLOW);
	L.length = 0;
	L.listsize = STU_INIT_SIZE;
	L.stu->cournum = 0;
	return OK;
}
Status Initlistcourse(Courselist& Q)
{
	Q.cou = (course*)malloc(COURSE_INIT_SIZE
		* sizeof(course));
	if (!Q.cou) exit(OVERFLOW);
	L.length = 0;
	L.listsize = STU_INIT_SIZE;
	Q.cou->classstunum = 0;
	return OK;
}
Status Insertstu(Stulist& L)//����ѡ��ϵͳ��������˳�򣬲������ֱ��ִ�е����һ������
{
	student a;
	while (1) {
		cout << "������ֱ��������ѧ����ѧ�š��������Ա�" << endl;
		cin >> a.no >> a.name >> a.gender;
		if (cin.good() == 1 && (a.gender == 'm' || a.gender == 'M' || a.gender == 'f' || a.gender == 'F'))
			break;
		cin.clear();
		cin.ignore();
	}

	if (L.length + 1 >= L.listsize)
		L.stu = (student*)realloc(L.stu, 100 * sizeof(student));
	if (!L.stu) exit(OVERFLOW);
	L.length++;
	L.stu[L.length - 1] = a;
	L.stu[L.length - 1].cournum = 0;
	L.stu[L.length - 1].cour = (course*)malloc(COURSE_INIT_SIZE * sizeof(course));
	cout << "����ɹ��������������" << endl;
	_getch();
}
Status Insertcourse(Courselist& Q)//����ѡ��ϵͳ��������˳�򣬲������ֱ��ִ�е����һ������
{
	course c;
	while (1) {
		cout << "������ֱ��������γ̵Ŀκš��γ�����ѧ��" << endl;
		cin >> c.classno >> c.classname
			>> c.credit;
		if (cin.good() == 1)
			break;
		cin.clear();
		cin.ignore();
	}

	if (Q.length + 1 >= Q.listsize)
		Q.cou = (course*)realloc(Q.cou, 100 * sizeof(course));
	if (!Q.cou) exit(OVERFLOW);
	Q.length++;
	Q.cou[Q.length - 1] = c;
	Q.cou[Q.length - 1].classstunum = 0;
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
		for (j = 0;j < Q.length;j++)
		{
			if (Q.cou[j].classno == num)
				break;
		}
		if (i == Q.length)
			cout << "��ѯʧ�ܣ�û���ҵ���ؿγ���Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ����γ���Ϣ����:" << endl;
			cout << "�κ�:" << Q.cou[j].classno << endl;
			cout << "�γ���:" << Q.cou[j].classname << endl;
			cout << "ѧ��" << Q.cou[j].credit << endl;
			cout << "ѡ��ѧ��:" << endl;
			int m = 0;
			while (m < Q.cou->classstunum)
			{
				cout << "����:" << Q.cou->classstu[m].name << " ѧ�ţ�" << Q.cou->classstu[m].no << " �Ա�" << Q.cou->classstu[m].gender << endl;
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
		for (j = 0;j < Q.length;j++)
		{
			if (strcmp(Q.cou[j].classname, cname) == 0)
				break;
		}
		if (j == Q.length)
			cout << "��ѯʧ�ܣ�û���ҵ���ؿγ���Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ����γ���Ϣ����:" << endl;
			cout << "�κ�:" << Q.cou[j].classno << endl;
			cout << "�γ���:" << Q.cou[j].classname << endl;
			cout << "ѧ��" << Q.cou[j].credit << endl;
			cout << "ѡ��ѧ��:" << endl;
			int m = 0;
			while (m < Q.cou->classstunum)
			{
				cout << "����:" << Q.cou->classstu[m].name << "  ѧ�ţ�" << Q.cou->classstu[m].no << "  �Ա�" << Q.cou->classstu[m].gender << endl;
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

		for (j = 0;j < L.length;j++)
		{
			if (L.stu[j].no == num)
				break;
		}
		if (j == L.length)
			cout << "��ѯʧ�ܣ�û���ҵ����ѧ����Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ���ѧ����Ϣ����:" << endl;
			cout << "ѧ��:" << L.stu[j].no << endl;
			cout << "����:" << L.stu[j].name << endl;
			cout << "�Ա�" << L.stu[j].gender << endl;
			cout << "ѡ���б�:" << endl;
			int m = 0;
			while (m < L.stu->cournum)
			{
				cout << "�γ�����" << L.stu->cour[m].classname << "  �κţ�" << L.stu->cour[m].classno << "  �γ�ѧ��" << L.stu->cour[m].credit << endl;
				m++;
			}
		}
		break;
	case 2:
		char sname[20];
		cout << "������Ŀ��ѧ������" << endl;
		cin >> sname;
		for (j = 0;j < L.length;j++)
		{
			if (strcmp(L.stu[j].name, sname) == 0)
				break;
		}
		if (j == L.length)
			cout << "��ѯʧ�ܣ�û���ҵ����ѧ����Ϣ" << endl;
		else {
			cout << "��ѯ�ɹ���ѧ����Ϣ����:" << endl;
			cout << "ѧ��:" << L.stu[j].no << endl;
			cout << "����:" << L.stu[j].name << endl;
			cout << "�Ա�" << L.stu[j].gender << endl;
			cout << "ѡ���б�:" << endl;
			int m = 0;
			while (m < L.stu->cournum)
			{
				cout << "�γ���:" << L.stu->cour[m].classname << "   �κţ�" << L.stu->cour[m].classno << "  �γ�ѧ��" << L.stu->cour[m].credit << endl;
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
		student* p = L.stu;
		while (p->no != delnum && p != NULL)
			p++;
		if (p == NULL)
		{
			cout << "��ѯ������ѧ����Ϣ������������" << endl;
			continue;
		}
		else {
			cout << "��Ҫɾ����ѧ��Ϊ" << endl;
			cout << "������" << p->name << " ѧ�ţ�" << p->no << " �Ա�" << p->gender << endl;
			cout << "���Ƿ�ȷ��ɾ����(Y/N)";

			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				student* q = L.stu + L.length - 1;
				for (p;p <= q;p++)
					*p = *(p + 1);
				L.length--;
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
	while (1)
	{
		cout << "��������Ҫɾ��ѧ����ѧ��" << endl;
		cin >> delclassnum;
		course* p = Q.cou;
		while (p->classno != delclassnum && p != NULL)
			p++;
		if (p == NULL)
		{
			cout << "��ѯ�����˿γ���Ϣ������������" << endl;
			continue;
		}
		else {
			cout << "��Ҫɾ���Ŀγ�Ϊ" << endl;
			cout << "�γ�����" << p->classname << " �κţ�" << p->classno << " ѧ��" << p->credit << endl;
			cout << "���Ƿ�ȷ��ɾ����(Y/N)";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				course* q = Q.cou + Q.length - 1;
				for (p;p <= q;p++)
					*p = *(p + 1);
				Q.length--;
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
			cin >> L.stu[j].no >> L.stu[j].name >> L.stu[j].gender;
			L.stu[j].cournum = 0;
			L.stu[j].cour = (course*)malloc(COURSE_INIT_SIZE * sizeof(course));
			if (cin.good() == 1 && (L.stu[j].gender == 'm' || L.stu[j].gender == 'M' || L.stu[j].gender == 'f' || L.stu[j].gender == 'F'))
				break;
			cout << "������������������ѧ����Ϣ" << endl;
			cin.clear();
			cin.ignore();
		}


	}
	L.length += i;
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
			cin >> Q.cou[j].classno >> Q.cou[j].classname >> Q.cou[j].credit;
			Q.cou[j].classstunum = 0;
			if (cin.good() == 1)
				break;
			cin.clear();
			cin.ignore();
		}
	}

	Q.length += i;
	cout << "¼��ɹ��������������...";
	_getch();
}
void registercourse(Stulist& L, Courselist& Q)
{
	int i = 0;
	int j = 0;
	while (1) {
		j = 0;
		i = 0;
		cout << "��������Ҫѡ�ε�ѧ��ѧ���Լ��γ̿κţ�";
		long int stunum, coursenum;
		cin >> stunum >> coursenum;
		while (i < L.length)
		{
			if (L.stu[i].no == stunum)
				break;
			i++;
		}
		if (i == L.length)
			cout << "��ѯ������ѧ����Ϣ������������" << endl;
		while (j < Q.length)
		{
			if (Q.cou[j].classno == coursenum)
				break;
			j++;
		}
		if (j == Q.length)
			cout << "��ѯ�����˿γ���Ϣ������������" << endl;
		if (i < L.length && j < Q.length)
			break;
		cin.clear();
		cin.ignore();

	}
	L.stu[i].cour[L.stu[i].cournum] = Q.cou[j];
	Q.cou[j].classstu[Q.cou[j].classstunum] = L.stu[i];
	L.stu[i].cournum++;
	Q.cou[j].classstunum++;
	cout << "ѡ�γɹ�����������˳�" << endl;
	_getch();
}
void show_stu_list(Courselist& Q)
{
	cout << "��������Ҫ��ѯ�Ŀκ�" << endl;
	long int num;
	int i;
	cin >> num;
	for (i = 0;i < Q.length;i++)
	{
		if (Q.cou[i].classno == num)
			break;
	}
	if (i == Q.length)
	{
		cout << "�ÿκŲ����ڣ���������˳�" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < Q.cou[i].classstunum;j++)
		{
			cout << "������" << Q.cou->classstu[j].name << " ѧ�ţ�" << Q.cou->classstu[j].no << " �Ա�" << Q.cou->classstu[j].gender << endl;
		}
		cout << "��������˳�" << endl;
		_getch();
	}

}
void show_course_list(Stulist& L)
{
	cout << "��������Ҫ��ѯ��ѧ��ѧ��" << endl;
	long int num;
	int i;
	cin >> num;
	for (i = 0;i < Q.length;i++)
	{
		if (L.stu[i].no == num)
			break;
	}
	if (i == L.length)
	{
		cout << "�ÿκŲ����ڣ���������˳�" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < L.stu[i].cournum;j++)
		{
			cout << "�γ�����" << L.stu->cour[j].classname << " �κţ�" << L.stu->cour[j].classno << " ѧ�֣�" << L.stu->cour[j].credit << endl;
		}
		cout << "��������˳�" << endl;
		_getch();
	}

}
void print()
{
	for (int j = 0;j < L.length;j++)
	{
		cout << " ����:" << L.stu[j].name << " ѧ�ţ�" << L.stu[j].no << " �Ա�:" << L.stu[j].gender << endl;
	}
	_getch();
}
int main()
{
	Initliststu(L);
	Initlistcourse(Q);
	while (1)
	{
		int ret = menu();
		if (ret == 100)
			print();
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