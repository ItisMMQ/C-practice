// Container.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <forward_list>
#include <stack>
#include <queue>

using namespace std;
using std::vector;
using std::string;
using std::list;

//9.51
struct date
{
	unsigned year;
	unsigned month;
	unsigned day;
	//成员函数
	void display()
	{
		cout << "Data: " << year << '-' << month << '-' << day << endl;
	}
	//构造函数
	date():year(0),month(0),day(0){}
	date(string &s);
};
date::date(string & s)
{
	vector<string> num = { "1","2","3","4","5","6","7","8","9","10","11","12" };
	string n = "123456789";
	string comma = ",/";
	string y, m, d;
	string::size_type  pos=0, epos=0;
	vector<string>mon_abv = { "Jan","Feb","Mar","Apl","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	//vector<string>mon_ful = {"January","February","March","April","May","June","July","August ","September","October","November","December"};
	//月份最先
	if (s.find_first_of(n) == pos)
	{
		//月份是数字形式
		for (auto &is_num : num)
			if (s.compare(0,2,is_num) == 0)//对比获取月份
			{
				this->month = static_cast<unsigned>(stoi(is_num));
				pos = (stoi(is_num)< 10) ? 1 : 2;//确定日期的起始位置
			}
	}
	else
	{
		//月份是单词形式
		for (string::size_type i = 0; i<mon_abv.size(); ++i)
		{
			if (s.compare(0, 3, mon_abv[i]) == 0)
			{
				this->month = i + 1;
				break;
			}
		}
		pos = s.find_first_of(n);//确定日期的起始位置
	}
	//日期，月份POS之后的第一个数字
	pos = s.find_first_of(n, pos);//找到日期起始POS
	int len = 0;
	if ((epos = s.find_first_of(comma, pos)) != string::npos)
		;
	else
		epos = s.find_first_of(' ', pos);
	len = epos - pos;
	d = s.substr(pos,len);
	this->day = static_cast<unsigned>(stod(d));
	//年，最后四位数字
	pos = s.find_last_of(n);
	y = s.substr(pos - 4, pos);
	this->year = static_cast<unsigned>(stod(y));
}

int main(int argc,char *argv[])
{
	//9.51
	string da;
	cout << "Enter date: ";
	getline(cin,da);
	struct date d(da);
	d.display();
	//example_stack
	stack<int> intStack;
	for (size_t ix = 0; ix != 10; ++ix)
		intStack.push(ix);
	while (!intStack.empty())
	{
		int value = intStack.top();
		cout << value << ' ';
		intStack.pop();
	}
	cout << endl;
	//9.52
	queue<int> intque;

	//example_1
	/*vector<int>ivec;
	cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
	for (vector<int>::size_type ix = 0; ix != 24; ++ix)
	{
		ivec.push_back(ix);
	}
	cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
	ivec.reserve(50);
	cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
	while (ivec.size() != ivec.capacity())
		ivec.push_back(0);
	cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
	ivec.push_back(51);
	cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
	ivec.resize(ivec.size()+ivec.size()/2);
	cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
	//example_2
	const char *cp = "Hello World!!!";
	char noNull[] = { 'H','i' };
	string s1(cp);
	string s2(noNull, 2);
	string s3(noNull);
	string s4(cp + 6, 5);
	string s5(s1, 6, 5);
	string s6(s1, 6);
	string s7(s1, 6,20);
	string s8(s1, 16);
	//9.18,9.19
	/*deque<string> dq;
	list<string> lst;
	string buf;
	while (cin >> buf)
	{
		//deque.push_back(buf);//向标准容器中添加元素
		lst.push_back(buf);
	}
	deque<string>::iterator it1= dq.begin();
	list<string> ::iterator it2 = lst.begin();
	for (it2; it2 != lst.end();++ it2)
	{
		cout << *it2<< endl;
	}*/
	//deque<int>even, odd;
//	list<int> numlst;
	/*vector<int> v;
	int buf;
	//auto iter = v.begin();
	while (cin >> buf)
	{
		//numlst.push_back(buf);
		v.push_back(buf);
	}
	for (auto &v1 : v)
		cout << v1 << ' ';
	cout << endl;*/
	/*for (auto it = numlst.begin(); it != numlst.end(); ++it)
	{
		cout << *it << ' ';
		if (*it % 2 == 0)
			even.push_back(*it);
		else
			odd.push_back(*it);
	}
	cout << endl;
	for (auto &a : odd)
		cout << "odd:" << a<<' ';
	cout << endl;
	for (auto &a : even)
		cout << "even:" << a<<' ';
	cout << endl;
	*/
	//9.22
	/*
	vector <int> iv;
	int i;
	while (cin >> i)
		iv.push_back(i);
	auto iter = iv.begin(), mid = iv.begin() + iv.size() / 2;
	for (int j = 1; iter != mid;++j)
	{
		if (*iter == 2)
		{
			iv.insert(iter, 4);
			auto iter = iv.begin()+j, mid = iv.begin() + iv.size() / 2;//于事无补
		}
		else
			++iter;
	}
	for (auto &n : iv)
		cout << n << ' ';
		*/
	//9.24
	//vector<int> v1;
	//cout << *v1.begin();//运行失败
	//cout << v1.front();//运行失败
	//cout << v1[0];//运行失败
	//cout << v1.at(0);//会抛出下标越界异常
	/*int ai[] = { 0,1,1,2,3,4,5,8,13,21,55,89};
	vector<int> v;
	list<int>l;
	for (auto &a : ai)
	{
		v.push_back(a);
		l.push_back(a);
	}
	auto iv = v.begin();
	while (iv != v.end())
	{
		if (*iv % 2)
			iv = v.erase(iv);
		else
			++iv;
	}
	auto il=l.begin();
	while (il!= l.end())
	{
		if (!(*il % 2))
			il = l.erase(il);
		else
			++il;
	}
	for (auto &vv : v)
		cout << vv<<' ';
	cout << endl;
	for (auto &ll : l)
		cout << ll<<' ';*/
	//9.27
	/*forward_list<int> flst = { 0,1,2,3,4,5,6,7,8,9 };
	auto prev = flst.before_begin();
	auto curr = flst.begin();
	while (curr != flst.end())
	{
		if (*curr % 2)
		{
			cout << *curr << " is an odd,it will be erased." << endl;
			curr = flst.erase_after(prev);
		}
		else
		{
			prev = curr;
			++curr;
		}
	}
	for (auto &fl : flst)
		cout << fl << ' ';
	cout << endl;*/
	//9.28
	/*forward_list<string>sfl;
	string buf, str1="he", str2="she";
	while (cin >> buf)
		sfl.push_front(buf);	
	void insert_str(forward_list<string> &sfl, string str1, string str2);
	insert_str( sfl, str1, str2);
	for (auto &s : sfl)
		cout << s <<' ';*/ 
 //9.41
/*
	vector<char>vc={ 'I',' ','a','m',' ','h','a','p','p','y','!' };
	string str(12,0);
	for (int i = 0; i < vc.size(); ++i)
		str[i]=vc[i];
	string substr(vc.begin(), vc.end());
	cout << "str: " <<str << endl <<"substr:"<<substr<< endl;
	//9.43
	string s, oldVal, newVal;
	s = "Go thr it.";
	oldVal = "thr";
	newVal = "through";
	void chgstr_1(string &s, string s1, string s2);
	chgstr_1(s, oldVal, newVal);
	cout << "new s: " << s<<endl;
	//9.44
	s = "He rejected,tho,he will help you still.";
	oldVal = "tho";
	newVal = "though";
	void chgstr_2(string &s, string s1, string s2);
	chgstr_2(s, oldVal, newVal);
	cout << "new s: " << s << endl;
	//9.45
	string name, gender;
	int age;
	cout << "Please enter name , gender and age: "<<endl;
	cin >> name>>gender>>age;
	void namefix1(string& name, string gender, int age);
	namefix1(name, gender, age);
	cout << "Fixed name: " << name << endl;
	//9.46
	cout << "Please enter new name , gender and age: "<<endl;
	cin >> name >> gender >> age;
	void namefix2(string& name, string gender, int age);
	namefix2(name, gender, age); 
	cout << "Fixed name: " << name << endl;
    //9.47
    string a = "ab2c3d7R4E6";
	string num = "1234567890";
	//string alp = "abcdRE";
	string::size_type pos = 0;
	while ((pos = a.find_first_of(num, pos)) != string::npos)
	{
		cout << "Found number   at index: " << pos << " element is: " << a[pos] << endl;
		++pos;
	}
	pos = 0;
	while ((pos = a.find_first_not_of(num , pos)) != string::npos)
	{
		cout << "Found alphabet at index: " << pos << " element is: " << a[pos] << endl;
		++pos;
	}*/
	//9.49
    //程序失败，文件打不开
	/*string scender = "bdfghijklpqty";
	ifstream inf(argv[1]);
	if (!inf)//检查文件的读取是否成功
	{
		cerr << "cannot open this file: " << argv[1]<< endl;
		inf.close();//关闭文件]
		system("pause");
		exit(1);
	}
	string rs;
	while (inf>>rs)
	{
		cout << "here"<<endl;
		cout << rs << ' ';
		string::size_type pos1 = 0, pos2, pos3;
		unsigned length = 0;
		while ((pos1 = rs.find_first_not_of(scender, pos1)) != string::npos)
		{
			pos2 = pos1;
			if ((pos2 = rs.find_first_of(scender, pos2)) != string::npos)
			{
				length > (pos2 - pos1) ? length : pos2 - pos1;
				pos3 = pos1;
			}
			++pos1;
		}
		//string sub_rs = rs.substr(pos3, length);
		//cout << "longest no scender word: " <<sub_rs<<endl;
	}
	inf.close();*/
    //9.50
  /* vector <string> vs;
	string s;
	while (cin >> s)//有些s可以设为小数
		vs.push_back(s);
	int sum_i=0;
	for (auto &i : vs)
	{
		sum_i+=stoi(i);
	}
	cout << "Sum is: " << sum_i << endl;
	double sum_d = 0.0;
	for (auto &d : vs)
	{
		sum_d += stod(d);
	}
	cout << "Sum is: " << sum_d << endl;*/
	system("pause");
    return 0;
}

void insert_str(forward_list<string>&sfl, string str1,string  str2)//对list对象进行引用，以防修改内容无法回传给主函数。可尝试去掉&看看效果。
{
	bool flag = false;
	auto p = sfl.before_begin(),c = sfl.begin();
	for(;c!=sfl.end();	p=c++)
	{
		if (*c == str1)
		{
			sfl.insert_after(c, str2);
			flag = true;
		}
	}
	if (!flag)
		sfl.insert_after(p, str2);
}

void chgstr_1(string &s, string s1, string s2)
{
	auto b = s.begin(), e = s.end();
	auto b2 = s2.begin(), e2 = s2.end();
	for (int i=0;i<s.size();++i)
	{
		if (s.substr(i, s1.size()) == s1)
		{
			s.erase(b + i, b+i+ s1.size());
			s.insert(b + i, b2,e2);
			return ;
		}
	}
	return;
}

void chgstr_2(string &s, string s1, string s2)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (s.substr(i, s1.size ()) == s1)
		{
			s.replace(i, s1.size(), s2);
			return;
		}
	}
	return;
}

void namefix1(string& name, string gender, int age)
{
	string prefix1="Mr.", prefix2="Ms.", suffix=" Jr";
	if (gender == "m" || gender == "M" || gender == "male" || gender == "Male")
		name.insert(name.begin(),prefix1.begin (), prefix1.end());
	else
		name.insert(name.begin(), prefix2.begin(), prefix2.end());
	if (age < 18)
		name.append(suffix);
	return;
}

void namefix2(string& name, string gender, int age)
{
	string prefix1 = "Mr.", prefix2 = "Ms.", suffix = " Jr";
	if (gender == "m" || gender == "M" || gender == "male" || gender == "Male")
		name.insert(0, prefix1);
	else
		name.insert(0, prefix2);
	if (age < 18)
		name.insert(name.size(),suffix);
	return;
}
