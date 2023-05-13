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
Status Insertstu(Stulist& L)//由于选课系统无需在意顺序，插入操作直接执行到最后一个就行
{
	student a;
	while (1) {
		cout << "请输入分别输入插入学生的学号、姓名、性别" << endl;
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
	cout << "插入成功，按任意键继续" << endl;
	_getch();
}
Status Insertcourse(Courselist& Q)//由于选课系统无需在意顺序，插入操作直接执行到最后一个就行
{
	course c;
	while (1) {
		cout << "请输入分别输入插入课程的课号、课程名、学分" << endl;
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
		for (j = 0;j < Q.length;j++)
		{
			if (Q.cou[j].classno == num)
				break;
		}
		if (i == Q.length)
			cout << "查询失败！没有找到相关课程信息" << endl;
		else {
			cout << "查询成功！课程信息如下:" << endl;
			cout << "课号:" << Q.cou[j].classno << endl;
			cout << "课程名:" << Q.cou[j].classname << endl;
			cout << "学分" << Q.cou[j].credit << endl;
			cout << "选课学生:" << endl;
			int m = 0;
			while (m < Q.cou->classstunum)
			{
				cout << "姓名:" << Q.cou->classstu[m].name << " 学号：" << Q.cou->classstu[m].no << " 性别" << Q.cou->classstu[m].gender << endl;
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
		for (j = 0;j < Q.length;j++)
		{
			if (strcmp(Q.cou[j].classname, cname) == 0)
				break;
		}
		if (j == Q.length)
			cout << "查询失败！没有找到相关课程信息" << endl;
		else {
			cout << "查询成功！课程信息如下:" << endl;
			cout << "课号:" << Q.cou[j].classno << endl;
			cout << "课程名:" << Q.cou[j].classname << endl;
			cout << "学分" << Q.cou[j].credit << endl;
			cout << "选课学生:" << endl;
			int m = 0;
			while (m < Q.cou->classstunum)
			{
				cout << "姓名:" << Q.cou->classstu[m].name << "  学号：" << Q.cou->classstu[m].no << "  性别" << Q.cou->classstu[m].gender << endl;
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

		for (j = 0;j < L.length;j++)
		{
			if (L.stu[j].no == num)
				break;
		}
		if (j == L.length)
			cout << "查询失败！没有找到相关学生信息" << endl;
		else {
			cout << "查询成功！学生信息如下:" << endl;
			cout << "学号:" << L.stu[j].no << endl;
			cout << "姓名:" << L.stu[j].name << endl;
			cout << "性别" << L.stu[j].gender << endl;
			cout << "选课列表:" << endl;
			int m = 0;
			while (m < L.stu->cournum)
			{
				cout << "课程名：" << L.stu->cour[m].classname << "  课号：" << L.stu->cour[m].classno << "  课程学分" << L.stu->cour[m].credit << endl;
				m++;
			}
		}
		break;
	case 2:
		char sname[20];
		cout << "请输入目标学生姓名" << endl;
		cin >> sname;
		for (j = 0;j < L.length;j++)
		{
			if (strcmp(L.stu[j].name, sname) == 0)
				break;
		}
		if (j == L.length)
			cout << "查询失败！没有找到相关学生信息" << endl;
		else {
			cout << "查询成功！学生信息如下:" << endl;
			cout << "学号:" << L.stu[j].no << endl;
			cout << "姓名:" << L.stu[j].name << endl;
			cout << "性别" << L.stu[j].gender << endl;
			cout << "选课列表:" << endl;
			int m = 0;
			while (m < L.stu->cournum)
			{
				cout << "课程名:" << L.stu->cour[m].classname << "   课号：" << L.stu->cour[m].classno << "  课程学分" << L.stu->cour[m].credit << endl;
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
		student* p = L.stu;
		while (p->no != delnum && p != NULL)
			p++;
		if (p == NULL)
		{
			cout << "查询不到此学生信息，请重新输入" << endl;
			continue;
		}
		else {
			cout << "您要删除的学生为" << endl;
			cout << "姓名：" << p->name << " 学号：" << p->no << " 性别：" << p->gender << endl;
			cout << "您是否确认删除？(Y/N)";

			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				student* q = L.stu + L.length - 1;
				for (p;p <= q;p++)
					*p = *(p + 1);
				L.length--;
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
	while (1)
	{
		cout << "请输入想要删除学生的学号" << endl;
		cin >> delclassnum;
		course* p = Q.cou;
		while (p->classno != delclassnum && p != NULL)
			p++;
		if (p == NULL)
		{
			cout << "查询不到此课程信息，请重新输入" << endl;
			continue;
		}
		else {
			cout << "您要删除的课程为" << endl;
			cout << "课程名：" << p->classname << " 课号：" << p->classno << " 学分" << p->credit << endl;
			cout << "您是否确认删除？(Y/N)";
			cin >> confirm;
			if (confirm == 'Y' || confirm == 'y')
			{
				course* q = Q.cou + Q.length - 1;
				for (p;p <= q;p++)
					*p = *(p + 1);
				Q.length--;
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
			cin >> L.stu[j].no >> L.stu[j].name >> L.stu[j].gender;
			L.stu[j].cournum = 0;
			L.stu[j].cour = (course*)malloc(COURSE_INIT_SIZE * sizeof(course));
			if (cin.good() == 1 && (L.stu[j].gender == 'm' || L.stu[j].gender == 'M' || L.stu[j].gender == 'f' || L.stu[j].gender == 'F'))
				break;
			cout << "输入错误，请重新输入该学生信息" << endl;
			cin.clear();
			cin.ignore();
		}


	}
	L.length += i;
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
			cin >> Q.cou[j].classno >> Q.cou[j].classname >> Q.cou[j].credit;
			Q.cou[j].classstunum = 0;
			if (cin.good() == 1)
				break;
			cin.clear();
			cin.ignore();
		}
	}

	Q.length += i;
	cout << "录入成功！按任意键继续...";
	_getch();
}
void registercourse(Stulist& L, Courselist& Q)
{
	int i = 0;
	int j = 0;
	while (1) {
		j = 0;
		i = 0;
		cout << "请输入需要选课的学生学号以及课程课号：";
		long int stunum, coursenum;
		cin >> stunum >> coursenum;
		while (i < L.length)
		{
			if (L.stu[i].no == stunum)
				break;
			i++;
		}
		if (i == L.length)
			cout << "查询不到此学生信息，请重新输入" << endl;
		while (j < Q.length)
		{
			if (Q.cou[j].classno == coursenum)
				break;
			j++;
		}
		if (j == Q.length)
			cout << "查询不到此课程信息，请重新输入" << endl;
		if (i < L.length && j < Q.length)
			break;
		cin.clear();
		cin.ignore();

	}
	L.stu[i].cour[L.stu[i].cournum] = Q.cou[j];
	Q.cou[j].classstu[Q.cou[j].classstunum] = L.stu[i];
	L.stu[i].cournum++;
	Q.cou[j].classstunum++;
	cout << "选课成功，按任意键退出" << endl;
	_getch();
}
void show_stu_list(Courselist& Q)
{
	cout << "请输入需要查询的课号" << endl;
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
		cout << "该课号不存在！按任意键退出" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < Q.cou[i].classstunum;j++)
		{
			cout << "姓名：" << Q.cou->classstu[j].name << " 学号：" << Q.cou->classstu[j].no << " 性别：" << Q.cou->classstu[j].gender << endl;
		}
		cout << "按任意键退出" << endl;
		_getch();
	}

}
void show_course_list(Stulist& L)
{
	cout << "请输入需要查询的学生学号" << endl;
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
		cout << "该课号不存在！按任意键退出" << endl;
		_getch();
		return;
	}
	else {
		for (int j = 0;j < L.stu[i].cournum;j++)
		{
			cout << "课程名：" << L.stu->cour[j].classname << " 课号：" << L.stu->cour[j].classno << " 学分：" << L.stu->cour[j].credit << endl;
		}
		cout << "按任意键退出" << endl;
		_getch();
	}

}
void print()
{
	for (int j = 0;j < L.length;j++)
	{
		cout << " 姓名:" << L.stu[j].name << " 学号：" << L.stu[j].no << " 性别:" << L.stu[j].gender << endl;
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