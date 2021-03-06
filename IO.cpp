// IO.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;
using std::string;
using std::vector;

struct Person_Info
{
	string name;
	vector<string> phones;
};

int main(int argc,char *argv[])
{
	//f(cin);//8.1&8.9
	//tryit(cin);//8.2
	//8.10 &8.13
	cout << "Enter file name: ";
	string name;
	cin >> name;//s.txt,num.txt
	//vector<string> f_txt;
	//read_line(name,f_txt);
	//8.11
	ifstream file_cin(name);
	string line, word;
	vector<Person_Info> people;
	istringstream record;
	//while (getline(cin, line))
	while (getline(file_cin, line))
	{
		record.str(line);
		Person_Info info;
		record >> info.name;
		while (record >> word)
			info.phones.push_back(word);
	//	people.push_back(info);
		
		record.clear();//由于record是函数外部变量，所以每完成一次while循环都得人工刷新record状态
	}
	/*for (auto &p : people)
	{
		cout<<p.name<<' ';
		for (auto &ph : p.phones)
			cout << ph << ' ';
		cout << endl;
	}*/ //用于测试8.11结果
	//8.13
	for(const auto &entry:people)
	{
		ostringstream format, badNums;
		for(const auto &nums:entry.phones)
		{
			if (nums.size()==8||nums.size()==11)
			{
				format<< nums<<" ";
			}
			else 	badNums<< nums <<" ";	
		}		
		if (badNums.str().empty())
			cout << entry.name << " " << format.str() << endl;
		else cerr << "Input error " << entry.name << " invalid number(s): " << badNums.str() << endl;
	}
	system("pause");
	return 0;
}

//8.1
istream &f(istream &is)
{
	string s, outs;
	while (getline(is, s))//必须加载sstream头文件，否则无法完成传送
		if (is.eof()) break;
	istringstream strm(s);
	while (strm >> outs)
		cout << outs << endl;
	is.clear();
	return is;
}

//8.2
void tryit(istream &cin)//IO操作的函数通常以引用方式传递，若不加&函数将调用失败
{
	string s;
	cout << "Please entering";
	cin >> s;
	cout << s << endl;
	return;
}
//8.4
void fread(string s)
{
	vector<string> str1, str2;
	ifstream in(s);
	if (in)//检查打开是否成功
	{
		string temp;
		while (getline(in, temp))//这里的in和cin其实是一样的
			str1.push_back(temp);
		//8.5
		in >> temp;
		str2.push_back(temp);
	}
	else
	{
		cout << "Can not open file " << s << endl;
	}
	for (auto &ss : str1)
		cout << ss << endl;
	in.close();
}
//8.10
void read_line(string f_name, vector<string> f_txt)
{
	string t_s, word;
	ifstream fstrm(f_name);
	if (fstrm)
	{
		istringstream strm;
		while (getline(fstrm, t_s))
		{
			f_txt.push_back(t_s);
		}
		for (auto &ss : f_txt)
		{
			istringstream sstrm(ss);
			while (sstrm >> word)
				cout << word << ' ';
			cout << endl;
		}
	}
	else cerr << "Can't open file " << f_name;
	fstrm.close();
}
