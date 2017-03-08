#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;
class student
{
public:
	student(int n=0, string na='\0', float C=0, float M=0, float E=0) :
		num(n), name(na), Chinese_score(C), Maths_score(M), English_score(E), next(NULL) {}

	//studentread_lianbiao.cpp
	friend student* student_read();
	friend void flashfile(student*head);

	//GUI.cpp
	static void display(student*);
	friend void GUI_0();
	friend void GUI_1();

	//member
	int num;
	string name;
	float Chinese_score;
	float Maths_score;
	float English_score;
	student *next;
};

//1.student_maintenance.cpp
class student_maintenance :public student
{
public:
	friend void Creat(student *);
	friend student*Delete(student *);
	friend void Update(student *);
};

//2.student_search.cpp
class student_search :public student
{
public:
	friend void StudentSch(student*);
};

//3.student_statistic.cpp
class student_statistic :public student
{
public:
	friend void StudentStatistic(student*);
};

//4.student_line.cpp
class student_line :public student
{
public:
	friend void StudentLine(student*);
};
void student::display(student *p)
{
	cout << " 姓名" << "     " << "学号" << "   " << "语文" << "    " << "数学" << "    " << "英语" << endl;
	while(true)
	{
		if ((*p).next == NULL)
		{
			cout.width(2);
			cout.fill('0');
			cout << (*p).num << "    ";
			cout.width(6);
			cout.fill(' ');
			cout << (*p).name << "    ";
			cout << (*p).Chinese_score << "    " << (*p).Maths_score << "    " << (*p).English_score << endl;
			break;
		}
		cout.width(2);
		cout.fill('0');
		cout << (*p).num << "    ";
		cout.width(6);
		cout.fill(' ');
		cout << (*p).name << "    ";
		cout << (*p).Chinese_score << "    " << (*p).Maths_score << "    " << (*p).English_score << endl;
		p = (*p).next;
	}
}
student* student_read()
{
	fstream file("student_message.dat", ios::in);
	file.seekg(ios::beg);
	int line(fstream&);
	student *head, *p, *q;
	//计算行数
	int l = line(file);
	//构建链表
	string str1, str2;
	float a[4];
	stringstream ex;
	getline(file, str1, '-');
	for (int m = 0;m < 3;m++)
	{
		getline(file, str2, '-');
		ex << str2;
		ex >> a[m];
		ex.clear();
	}
	getline(file, str2, '\n');
	ex << str2;
	ex >> a[3];
	ex.clear();
	p = head = new student(int(a[0]), str1, a[1], a[2], a[3]);
	for (int m = 0;m < l-1;m++)
	{
		getline(file, str1, '-');
		for (int m = 0;m < 3;m++)
		{
			getline(file, str2, '-');
			ex << str2;
			ex >> a[m];
			ex.clear();
		}
		getline(file, str2, '\n');
		ex << str2;
		ex >> a[3];
		ex.clear();
		q = new student(int(a[0]), str1, a[1], a[2], a[3]);
		(*p).next = q;
		p = q;
	}
	file.close();
	return head;
}

int line(fstream&t)
{
	char c;
	int s = 0;
	c = t.get();
	while (c != '#')
	{
		if (c == '\n')
			s++;
		c = t.get();
	}
	t.seekg(ios::beg);
	return s;
}

void flashfile(student*head)
{
	student *p;
	p = head;
	ofstream ostu("student_message.dat", ios::out);
	while (true)
	{
		if ((*p).next == NULL)
		{
			ostu << (*p).name << '-';
			ostu.width(2);
			ostu.fill('0');
			ostu << (*p).num << '-';
			ostu << (*p).Chinese_score << '-' << (*p).Maths_score << '-' << (*p).English_score;
			ostu << '\n';
			break;
		}
		ostu << (*p).name << '-';
		ostu.width(2);
		ostu.fill('0');
		ostu << (*p).num << '-';
		ostu << (*p).Chinese_score << '-' << (*p).Maths_score << '-' << (*p).English_score;
		ostu << '\n';
		p = (*p).next;
	}
	ostu << '#';
	ostu.close();
}

void GUI_0()
{
	cout << "-----学生信息管理系统-----" << endl;
	cout << "     1.信息维护           " << endl;
	cout << "     2.信息查询           " << endl;
	cout << "     3.成绩统计           " << endl;
	cout << "     4.成绩排序           " << endl;
	cout << "     5.退出           " << endl;
	cout << "请选择：";
}

void GUI_1()
{
	cout << "---------信息维护---------" << endl;
	cout << "      1.增加学生信息      " << endl;
	cout << "      2.删除学生信息      " << endl;
	cout << "      3.修改学生信息      " << endl;
	cout << "      4.返回上一级        " << endl;
	cout << "请选择：";
}

void LineOut(student*p[],int);
int LineS(student*);
void StudentLine(student*head)
{
	void Line_C(student*);
	void Line_M(student*);
	void Line_E(student*);
	while (true)
	{
		cout << "请选择要排序的科目（输入0返回上一级）：" << endl;
		cout << "A.语文   B.数学   C.英语" << endl;
		cout << "请选择：";
		char choice;
		cin >> choice;
		if (choice == '0')
		{
			cout << endl;
			break;
		}
		else if (choice == 'A')
		{
			Line_C(head);
			cout << endl;
		}
		else if (choice == 'B')
		{
			Line_M(head);
			cout << endl;
		}
		else if (choice == 'C')
		{
			Line_E(head);
			cout << endl;
		}
		else
			cout << "输入错误，请重新输入：";
	}
}

void LineOut(student*p[],int a)
{
	for (int m = 0;m < a;m++)
	{
		cout.width(2);
		cout.fill('0');
		cout << (*p[m]).num << "    ";
		cout.width(6);
		cout.fill(' ');
		cout << (*p[m]).name << "    ";
		cout << (*p[m]).Chinese_score << "    " << (*p[m]).Maths_score << "    " << (*p[m]).English_score << endl;
	}
}

int LineS(student*head)
{
	student*p = head;
	int s = 0;
	while (true)
	{
		if ((*p).next != NULL)
		{
			s++;
			p = (*p).next;
		}
		else if ((*p).next == NULL)
		{
			s++;
			break;
		}
	}
	return s;
}

void Line_C(student*head)
{
	student*p = head;
	int s = LineS(head);
	student**m = new student*[s];
	for (int n = 0;n < s;n++)
	{
		*(m + n) = p;
		p = (*p).next;
	}
	for (int k = 0;k < s - 1;k++)
	{
		float C = (*(*(m + k))).Chinese_score;
		int e;
		for (int l = k + 1;l < s;l++)
		{
			if (C <= (*(*(m + l))).Chinese_score)
			{
				C = (*(*(m + l))).Chinese_score;
				e = l;
			}
		}
		student*ex = *(m + k);
		*(m + k) = *(m + e);
		*(m + e) = ex;
	}
	LineOut(m, s);
}

void Line_M(student*head)
{
	student*p = head;
	int s = LineS(head);
	student**m = new student*[s];
	for (int n = 0;n < s;n++)
	{
		*(m + n) = p;
		p = (*p).next;
	}
	for (int k = 0;k < s - 1;k++)
	{
		for (int l = 0;l < s - 1;l++)
		{
			if ((*(*(m + l))).Maths_score <= (*(*(m + l + 1))).Maths_score)
			{
				student*ex = *(m + k);
				*(m + k) = *(m + l);
				*(m + l) = ex;
			}
		}
	}
	LineOut(m, s);
}

void Line_E(student*head)
{

	student*p = head;
	int s = LineS(head);
	student**m = new student*[s];
	for (int n = 0;n < s;n++)
	{
		*(m + n) = p;
		p = (*p).next;
	}
	int gap;
	for (gap = 3; gap >0; gap--)
	{
		for (int i = 0; i<gap; i++)
		{
			for (int j = i; j<s - gap; j = j + gap)
			{
				float C = (*(*(m + j))).Chinese_score;
				int e;
				for (int k = j + gap;k < s;k = k + gap)
				{
					if (C <= (*(*(m + k))).Chinese_score)
					{
						C = (*(*(m + k))).Chinese_score;
						e = k;
					}
				}
				student*ex = *(m + j);
				*(m + j) = *(m + e);cout << "1" << endl;
				*(m + e) = ex;
			}
		}
	}
	LineOut(m, s);
}
void StatisticOut(student*);
void StudentStatistic(student *head)
{
	while (true)
	{
		void Sta_C(student*, int, int);
		void Sta_M(student*, int, int);
		void Sta_E(student*, int, int);
		cout << "请选择要统计的科目（输入0返回上一级）：" << endl;
		cout << "A.语文   B.数学   C.英语" << endl;
		cout << "请选择：";
		char choice;
		cin >> choice;
		if (choice == '0')
		{
			cout << endl;
			break;
		}
		else if(choice == 'A' || choice == 'B' || choice == 'C')
		{
			cout << "请输入要统计的分数段（用空格隔开）：";
			int m1, m2;
			cin >> m1 >> m2;
			if (choice == 'A')
			{
				Sta_C(head, m1, m2);
				cout << endl;
			}
			else if (choice == 'B')
			{
				Sta_M(head, m1, m2);
				cout << endl;
			}
			else if (choice == 'C')
			{
				Sta_E(head, m1, m2);
				cout << endl;
			}
		}
		else
		{
			cout << "输入错误，请重新输入！" << endl << endl;
		}
	}
}

void StatisticOut(student*p)
{
	cout.width(2);
	cout.fill('0');
	cout << (*p).num << "    ";
	cout.width(6);
	cout.fill(' ');
	cout << (*p).name << "    ";
	cout << (*p).Chinese_score << "    " << (*p).Maths_score << "    " << (*p).English_score << endl;
}

void Sta_C(student*head, int m1, int m2)
{
	student *p = head;
	while (true)
	{
		if ((*p).next == NULL)
		{
			if (m1 >= m2)
			{
				if ((*p).Chinese_score >= m2 && (*p).Chinese_score <= m1)
				{
					StatisticOut(p);
					p = (*p).next;
					break;
				}
				else break;
			}
			else if (m1 < m2)
			{
				if ((*p).Chinese_score <= m2 && (*p).Chinese_score >= m1)
				{
					StatisticOut(p);
					p = (*p).next;
					break;
				}
				else break;
			}
		}
		if (m1 >= m2)
		{
			if ((*p).Chinese_score >= m2 && (*p).Chinese_score <= m1)
			{
				StatisticOut(p);
				p = (*p).next;
			}
			else
				p = (*p).next;
		}
		else if (m1 < m2)
		{
			if ((*p).Chinese_score <= m2 && (*p).Chinese_score >= m1)
			{
				StatisticOut(p);
				p = (*p).next;
			}
			else
				p = (*p).next;
		}
	}
}

void Sta_M(student*head, int m1, int m2)
{
	student *p = head;
	while (true)
	{
		if ((*p).next == NULL)
		{
			if (m1 >= m2)
			{
				if ((*p).Maths_score >= m2 && (*p).Maths_score <= m1)
				{
					StatisticOut(p);
					p = (*p).next;
					break;
				}
				else break;
			}
			else if (m1 < m2)
			{
				if ((*p).Maths_score <= m2 && (*p).Maths_score >= m1)
				{
					StatisticOut(p);
					p = (*p).next;
					break;
				}
				else break;
			}
		}
		if (m1 >= m2)
		{
			if ((*p).Maths_score >= m2 && (*p).Maths_score <= m1)
			{
				StatisticOut(p);
				p = (*p).next;
			}
			else
				p = (*p).next;
		}
		else if (m1 < m2)
		{
			if ((*p).Maths_score <= m2 && (*p).Maths_score >= m1)
			{
				StatisticOut(p);
				p = (*p).next;
			}
			else
				p = (*p).next;
		}
	}
}


void Sta_E(student*head, int m1, int m2)
{
	student *p = head;
	while (true)
	{
		if ((*p).next == NULL)
		{
			if (m1 >= m2)
			{
				if ((*p).English_score >= m2 && (*p).English_score <= m1)
				{
					StatisticOut(p);
					p = (*p).next;
					break;
				}
				else break;
			}
			else if (m1 < m2)
			{
				if ((*p).English_score <= m2 && (*p).English_score >= m1)
				{
					StatisticOut(p);
					p = (*p).next;
					break;
				}
				else break;
			}
		}
		if (m1 >= m2)
		{
			if ((*p).English_score >= m2 && (*p).English_score <= m1)
			{
				StatisticOut(p);
				p = (*p).next;
			}
			else
				p = (*p).next;
		}
		else if (m1 < m2)
		{
			if ((*p).English_score <= m2 && (*p).English_score >= m1)
			{
				StatisticOut(p);
				p = (*p).next;
			}
			else
				p = (*p).next;
		}
	}
}
void StudentSch(student*head)
{
	char choice;
	while (true)
	{
		student*NameSch(string, student*);
		student*NumSch(int, student*);
		cout << "请选择根据学号查找或根据姓名查找（输入0返回上一级）：" << endl;
		cout << "A.学号  B.姓名" << endl;
		string Name;
		int Num;
		student*Sch;
		cout << "请选择：";
		cin >> choice;
		if (choice == 'A')
		{
			cout << "请输入学号：";
			cin >> Num;
			Sch = NumSch(Num, head);
			if (Sch == NULL)
				cout << "未找到该条信息" << endl;
			else if (Sch != NULL)
			{
				cout.width(2);
				cout.fill('0');
				cout << (*Sch).num << "    ";
				cout.width(6);
				cout.fill(' ');
				cout << (*Sch).name << "    ";
				cout << (*Sch).Chinese_score << "    " << (*Sch).Maths_score << "    " << (*Sch).English_score << endl;
			}
		}
		else if (choice == 'B')
		{
			cout << "请输入姓名：";
			cin >> Name;
			Sch = NameSch(Name, head);
			if (Sch == NULL)
				cout << "未找到该条信息" << endl;
			else if (Sch != NULL)
			{
				cout.width(2);
				cout.fill('0');
				cout << (*Sch).num << "    ";
				cout.width(6);
				cout.fill(' ');
				cout << (*Sch).name << "    ";
				cout << (*Sch).Chinese_score << "    " << (*Sch).Maths_score << "    " << (*Sch).English_score << endl;
			}
		}
		else if (choice == '0')
			break;
		else
			cout << "输入错误，请重新输入！" << endl << endl;
	}
}

student*NumSch(int del, student*head)
{
	student *m;
	m = head;
	while (true)
	{
		if ((*m).num == del)
			return m;
		else if ((*m).next == NULL)
			return NULL;
		else if ((*m).num != del)
			m = (*m).next;
	}
}

student*NameSch(string del, student*head)
{
	student *m;
	m = head;
	while (true)
	{
		if ((*m).name == del)
			return m;
		else if ((*m).next == NULL)
			return NULL;
		else if ((*m).name != del)
			m = (*m).next;
	}
}
void Creat(student *head)
{
	student *p, *q;
	q = p = head;
	while (true)
	{
		p = (*p).next;
		if ((*p).next == NULL)
			break;
	}
	int a;
	float b, c, d;
	string str;
	cout << "每条学生信息各项内容用空格分隔，例如：张明明 01 67 78 82" << endl;
	cout << "请输入将录入的学生信息个数：";
	int n, s;
	cin >> n;
	cout << "请依次输入姓名、学号、语文成绩、数学成绩、英语成绩，每个学生信息占一行：" << endl;
	for (int m = 0;m < n;m++)
	{
		cin >> str >> a >> b >> c >> d;
		q = head;
		while (true)
		{
			s = 0;
			if ((*q).num == a)
			{
				s++;
				break;
			}
			else if ((*q).next == NULL)
				break;
			else if ((*q).num != a)
				q = (*q).next;
		}
		if (s == 0)
		{
			q = new student(a, str, b, c, d);
			(*p).next = q;
			p = q;
		}
		else if (s == 1)
			cout << "学号重复，错误！" << endl;
	}
}

//删除信息函数
student*Delete(student*a)
{
	student*NameDel(string,student*);
	student*NumDel(int,student*);
	student*Del(student*, student*);
	cout << "请选择根据学号删除或根据姓名删除:" << endl;
	cout << "A.学号  B.姓名" << endl;
	char choice;
	string Name;
	int Num;
	student*del;
	cin >> choice;
	if (choice == 'A')
	{
		cout << "请输入学号：";
		cin >> Num;
		del = NumDel(Num, a);
		if (del == NULL)
			cout << "未找到该条信息" << endl;
		else if (del != NULL)
		{
			a = Del(del, a);
			cout << "已删除" << endl;
		}
	}
	else if (choice == 'B')
	{
		cout << "请输入姓名：";
		cin >> Name;
		del = NameDel(Name,a);
		if (del == NULL)
			cout << "未找到该条信息" << endl;
		else if (del != NULL)
		{
			a = Del(del, a);
			cout << "已删除" << endl;
		}
	}
	return a;
}

student*NumDel(int del,student*head)
{
	student *m;
	m = head;
	while (true)
	{
		if ((*m).num == del)
			return m;
		else if ((*m).next == NULL)
			return NULL;
		else if ((*m).num != del)
			m = (*m).next;
	}
}

student*NameDel(string del,student*head)
{
	student *m;
	m = head;
	while (true)
	{
		if ((*m).name == del)
			return m;
		else if ((*m).next == NULL)
			return NULL;
		else if ((*m).name != del)
			m = (*m).next;
	}
}

student*Del(student*del,student*head)
{
	student *m, *n;
	m = head;
	if (m == del)
	{
		head = (*head).next;
		delete m;
	}
	else if (m != del)
	{
		while (true)
		{
			if ((*m).next == del)
			{
				n = (*m).next;
				(*m).next = (*n).next;
				delete n;
				break;
			}
			else if ((*m).next != del)
				m = (*m).next;
		}
	}
	return head;
}

//更新信息函数
void Update(student *head)
{
	student*Find(string, student*);
	student*Find(int, student*);
	void newdata(char, student*);
	cout << "请选择根据学号删除或根据姓名更新:" << endl;
	cout << "A.学号  B.姓名" << endl;
	char choice;
	string Name;
	int Num;
	student*aim = NULL;
	cin >> choice;
	if (choice == 'A')
	{
		cout << "请输入学号：";
		cin >> Num;
		aim = Find(Num, head);
	}
	else if(choice=='B')
	{
		cout << "请输入姓名：";
		cin >> Name;
		aim = Find(Name, head);
	}
	cout << "请输入改动的项目：" << endl;
	cout << "A.姓名  B.学号  C.语文成绩  D.数学成绩  E.英语成绩" << endl;
	cin >> choice;
	newdata(choice, aim);
	student::display(head);
}

student*Find(int a, student*head)
{
	student *m;
	m = head;
	while (true)
	{
		if ((*m).num == a)
			return m;
		else if ((*m).next == NULL)
			return NULL;
		else if ((*m).num != a)
			m = (*m).next;
	}
}

student*Find(string a, student*head)
{
	student *m;
	m = head;
	while (true)
	{
		if ((*m).name == a)
			return m;
		else if ((*m).next == NULL)
			return NULL;
		else if ((*m).name != a)
			m = (*m).next;
	}
}

void newdata(char t,student *a)
{
	string name;
	int num;
	float score;
	if (t == 'A')
	{
		cout << "请输入新的姓名：";
		cin >> name;
		(*a).name = name;
	}
	else if (t == 'B')
	{
		cout << "请输入新的学号：";
		cin >> num;
		(*a).num = num;
	}
	else if (t == 'C')
	{
		cout << "请输入新的语文成绩：";
		cin >> score;
		(*a).Chinese_score = score;
	}
	else if (t == 'D')
	{
		cout << "请输入新的数学成绩：";
		cin >> score;
		(*a).Maths_score = score;
	}
	else if (t == 'E')
	{
		cout << "请输入新的英语成绩：";
		cin >> score;
		(*a).English_score = score;
	}
}

int main()
{
	ifstream file("student_message.dat", ios::in );
	student *head;
	head = student_read();
	file.close();
	int G, S = 0;
	while (true)
	{
		GUI_0();
		cin >> G;
		if (G == 1)
		{
			while (true)
			{
				GUI_1();
				cin >> S;
				if (S == 1)
					Creat(head);
				else if (S == 2)
					head = Delete(head);
				else if (S == 3)
					Update(head);
				else if (S == 4)
					break;
			}
		}
		else if (G == 2)
		{
			StudentSch(head);
		}
		else if (G == 3)
		{
			StudentStatistic(head);
		}
		else if (G == 4)
		{
			StudentLine(head);
		}
		else if (G > 5)
			cout << "无此选项请重新选择！" << endl << endl;
		else if (G == 5)
			break;
	}
	flashfile(head);
	return 0;
}
