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
	L->next = NULL; /* 指针域为空*/
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
Status Insertstu(Stulist& L)//由于选课系统无需在意顺序，插入操作直接执行到最后一个就行
{
	Stulist p;
	p = (Stulist)malloc(sizeof(StuNode));
	if (!p) exit(OVERFLOW);
	while (1) {
		cout << "请输入分别输入插入学生的学号、姓名、性别" << endl;
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
	cout << "插入成功，按任意键继续" << endl;
	_getch();
}
Status Insertcourse(Courselist& Q)//由于选课系统无需在意顺序，插入操作直接执行到最后一个就行
{
	Courselist p;
	p = (Courselist)malloc(sizeof(CourseNode));
	if (!p) exit(OVERFLOW);
	while (1) {
		cout << "请输入分别输入插入课程的课号、课程名、学分" << endl;
		cin >> p->cou.classno >> p->cou.classname >> p->cou.credit;
		if (cin.good() == 1)
			break;
		cin.clear();
		cin.ignore();
	}

	Q->next = p;
	p->cou.classstunum = 0;
	cout << "插入成功，按任意键继续" << endl;
	_getch();
}
void searchcou(Courselist& Q)
{
	cout << "请选择查找字段" << endl;
	cout << "1.课号" << endl;
	cout << "2.课程名" << endl;
	int i;
	while (1) {
		cin >> i;
		if ((i == 1 || i == 2) && cin.good() == 1)
			break;
		cout << "输入错误，请重新输入" << endl;
		cin.clear();
		cin.ignore();
	}
	int j;
	Courselist q = Q;
	switch (i)
	{
	case 1:
		long int num;
		cout << "请输入查询目标课号：" << endl;
		while (1)
		{
			cin >> num;
			if (cin.good() == 1)
				break;
			cout << "输入错误，请重新输入" << endl;
		}
		while (q != NULL)
		{
			if (q->cou.classno == num)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "查询失败！没有找到相关课程信息" << endl;
		else {
			cout << "查询成功！课程信息如下:" << endl;
			cout << "课号:" << q->cou.classno << endl;
			cout << "课程名:" << q->cou.classname << endl;
			cout << "学分" << q->cou.credit << endl;
			cout << "选课学生:" << endl;
			int m = 0;
			while (m < q->cou.classstunum)
			{
				cout << "姓名:" << q->cou.classstu[m].name << " 学号：" << q->cou.classstu[m].no << " 性别" << q->cou.classstu[m].gender << endl;
				m++;
			}
		}
		break;
	case 2:
		char cname[20];
		cout << "请输入查询目标课程名：" << endl;
		while (1)
		{
			cin >> cname;
			if (cin.good() == 1)
				break;
			cout << "输入错误，请重新输入" << endl;
		}
		while (q != NULL)
		{
			if (strcmp(q->cou.classname, cname) == 0)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "查询失败！没有找到相关课程信息" << endl;
		else {
			cout << "查询成功！课程信息如下:" << endl;
			cout << "课号:" << q->cou.classno << endl;
			cout << "课程名:" << q->cou.classname << endl;
			cout << "学分" << q->cou.credit << endl;
			cout << "选课学生:" << endl;
			int m = 0;
			while (m < q->cou.classstunum)
			{
				cout << "姓名:" << q->cou.classstu[m].name << "  学号：" << q->cou.classstu[m].no << "  性别" << q->cou.classstu[m].gender << endl;
				m++;
			}
		}
		break;

	}
	_getch();
}
void searchstu(Stulist& L)
{
	cout << "请选择查找字段" << endl;
	cout << "1.学号" << endl;
	cout << "2.姓名" << endl;
	int i;
	Stulist q = L;
	while (1) {
		cin >> i;
		if ((i == 1 || i == 2) && cin.good() == 1)
			break;
		cout << "输入错误，请重新输入" << endl;
		cin.clear();
		cin.ignore();
	}
	int j;
	switch (i)
	{
	case 1:
		long int num;
		cout << "请输入查询目标学号：" << endl;
		cin >> num;

		while (q != NULL)
		{
			if (q->stu.no == num)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "查询失败！没有找到相关学生信息" << endl;
		else {
			cout << "查询成功！学生信息如下:" << endl;
			cout << "学号:" << q->stu.no << endl;
			cout << "姓名:" << q->stu.name << endl;
			cout << "性别" << q->stu.gender << endl;
			cout << "选课列表:" << endl;
			int m = 0;
			while (m < q->stu.cournum)
			{
				cout << "课程名：" << q->stu.cour[m].classname << "  课号：" << q->stu.cour[m].classno << "  课程学分" << q->stu.cour[m].credit << endl;
				m++;
			}
		}
		break;
	case 2:
		char sname[20];
		cout << "请输入目标学生姓名" << endl;
		cin >> sname;
		while (q != NULL)
		{
			if (strcmp(q->stu.name, sname) == 0)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "查询失败！没有找到相关学生信息" << endl;
		else {
			cout << "查询成功！学生信息如下:" << endl;
			cout << "学号:" << q->stu.no << endl;
			cout << "姓名:" << q->stu.name << endl;
			cout << "性别" << q->stu.gender << endl;
			cout << "选课列表:" << endl;
			int m = 0;
			while (m < q->stu.cournum)
			{
				cout << "课程名:" << q->stu.cour[m].classname << "   课号：" << q->stu.cour[m].classno << "  课程学分" << q->stu.cour[m].credit << endl;
				m++;
			}
		}
		break;
	}
	_getch();
}
void delstu(Stulist& L)
{
	cout << "请输入想要删除学生的学号" << endl;
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
			cout << "查询不到此学生信息，请重新输入" << endl;
			continue;
		}
		else {
			q = p->next;
			cout << "您要删除的学生为" << endl;
			cout << "姓名：" << q->stu.name << " 学号：" << q->stu.no << " 性别：" << q->stu.gender << endl;
			cout << "您是否确认删除？(Y/N)";

			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				p->next = q->next;
				free(q);
				cout << " 删除成功，按任意键继续" << endl;
			}
			else if (confirm == 'N' || confirm == 'n' && cin.good() == 1)
			{
				cout << "按任意键退出" << endl;
			}
			_getch();
			break;
		}

	}

}
void delcou(Courselist& Q)
{
	cout << "请输入想要删除课程的课号" << endl;
	long int delclassnum;
	char confirm;
	Courselist p = Q, q;
	while (1)
	{
		cout << "请输入想要删除学生的学号" << endl;
		cin >> delclassnum;
		while (p->next->cou.classno != delclassnum && p->next != NULL)
			p++;
		if (p->next == NULL)
		{
			cout << "查询不到此课程信息，请重新输入" << endl;
			continue;
		}
		else {
			q = p->next;
			cout << "您要删除的课程为" << endl;
			cout << "课程名：" << q->cou.classname << " 课号：" << q->cou.classno << " 学分" << q->cou.credit << endl;
			cout << "您是否确认删除？(Y/N)";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				p->next = q->next;
				free(q);
				cout << " 删除成功，按任意键继续" << endl;
			}
			else if (confirm == 'N' || confirm == 'n' && cin.good() == 1)
			{
				cout << "按任意键退出" << endl;
			}
			_getch();
			break;
		}

	}
}
int menu()
{
	cout << "*************************************************************" << endl;
	cout << "*                      学生选课系统                         *" << endl;
	cout << "*                1.批量输入学生信息                         *" << endl;
	cout << "*                2.批量输入课程信息                         *" << endl;
	cout << "*                3.插入学生信息                             *" << endl;
	cout << "*                4.删除学生信息                             *" << endl;
	cout << "*                5.查找学生信息                             *" << endl;
	cout << "*                6.插入课程信息                             *" << endl;
	cout << "*                7.删除课程信息                             *" << endl;
	cout << "*                8.查找课程信息                             *" << endl;
	cout << "*                9.学生选课                                 *" << endl;
	cout << "*                10.显示选课名单                            *" << endl;
	cout << "*                11.显示学生课表                            *" << endl;
	cout << "*                0.退出                                     *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*************************************************************" << endl;
	int i;
	cout << "请输入要执行的操作[0-11]:";
	cin >> i;
	return i;
}
void inputstu(Stulist& L)
{
	int i;
	cout << " 请输入信息录入的学生人数：";
	cin >> i;
	cout << " 请分别输入每个学生的学号、姓名和性别" << endl;
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
			cout << "输入错误，请重新输入该学生信息" << endl;
			cin.clear();
			cin.ignore();
		}

	}
	cout << "录入成功！按任意键继续...";
	_getch();
}
void inputcourse(Courselist& Q)
{
	int i;
	cout << " 请输入信息录入的课程门数：";
	cin >> i;
	cout << " 请分别输入每节课程的课号、课程名和学分" << endl;
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
	cout << "录入成功！按任意键继续...";
	_getch();
}
void registercourse(Stulist& L, Courselist& Q)
{
	Stulist p = L;
	Courselist q = Q;
	while (1) {
		cout << "请输入需要选课的学生学号以及课程课号：";
		long int stunum, coursenum;
		cin >> stunum >> coursenum;
		while (p != NULL)
		{
			if (p->stu.no == stunum)
				break;
			p = p->next;
		}
		if (p == NULL)
			cout << "查询不到此学生信息，请重新输入" << endl;
		while (q != NULL)
		{
			if (q->cou.classno == coursenum)
				break;
			q = q->next;
		}
		if (q == NULL)
			cout << "查询不到此课程信息，请重新输入" << endl;
		if (q && p)
			break;
		cin.clear();
		cin.ignore();

	}
	p->stu.cour[p->stu.cournum] = q->cou;
	q->cou.classstu[q->cou.classstunum] = p->stu;
	p->stu.cournum++;
	q->cou.classstunum++;
	cout << "选课成功，按任意键退出" << endl;
	_getch();
}
void show_stu_list(Courselist& Q)
{
	cout << "请输入需要查询的课号" << endl;
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
		cout << "该课号不存在！按任意键退出" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < p->cou.classstunum;j++)
		{
			cout << "姓名：" << p->cou.classstu[j].name << " 学号：" << p->cou.classstu[j].no << " 性别：" << p->cou.classstu[j].gender << endl;
		}
		cout << "按任意键退出" << endl;
		_getch();
	}

}
void show_course_list(Stulist& L)
{
	cout << "请输入需要查询的学生学号" << endl;
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
		cout << "该课号不存在！按任意键退出" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < p->stu.cournum;j++)
		{
			cout << "课程名：" << p->stu.cour[j].classname << " 课号：" << p->stu.cour[j].classno << " 学分：" << p->stu.cour[j].credit << endl;
		}
		cout << "按任意键退出" << endl;
		_getch();
	}

}
//void print()
//{
//	whi
//	{
//		cout << " 姓名:" << L.stu[j].name << " 学号：" << L.stu[j].no << " 性别:" << L.stu[j].gender << endl;
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