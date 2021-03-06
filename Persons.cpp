// Persons.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;

struct person
{
	string name;
	char gender;
	int age;	
	string addr;
	void input();
	void print();
	char job;
	union position
	{
		string pst="unknown";//工作的填职级
		string grade;//学生填年级
	}category;
	person &combine(const person &p);//一个没用的成员函数
	string address() const { return addr;}
	//person() {};//C++union类型不提供默认构造函数，也无法自行构造
};
//P234,定义外部函数read，print和add
istream &read(istream &is, person &p)
{
	is >> p.name >> p.gender >>p.age>>p.addr>>p.job;
	if (p.job == 's') { cout << "年级："; cin >>p.category.grade; }
	if (p.job == 'w') { cout << "职级："; cin >> p.category.pst; }
	return is;
}//***感觉没有成员函数input简单***
ostream &print(ostream &os, const person &p)
{
	os << p.name<< " " << p.gender << " " << p.addr<< " " <<endl;
	return os;
}//***same as above***
person add(const person &lhs, const person &rhs)
{
	person sum = lhs;
	sum.combine(rhs);
	return sum;
}
int main()
{
	vector<person> id;
	person t_id;
	string se;
	cout << "Start entering ID? " << endl;
	cin >> se;
	if (se == "Y" || se == "y") cout << "name:\taddr:\tgender:\tcontinue?" << endl;
	while (se=="Y"||se=="y")
	{
		//t_id.input();
		read(cin, t_id);
		id.push_back(t_id);
		cin >> se;
	}
	for (auto &pers : id)
	{
		pers.print();
	}
	system("pause");
    return 0;
}

void person::input()
{
	cin >> name >> addr >> gender;
}

void person::print()
{
	cout << "name: " << name << " gender: " << gender << " address: " << addr<<endl;
}

person & person::combine(const person & p)
{
	addr += p.addr;
	return *this;
}
