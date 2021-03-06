// Allocation.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <string.h>
#include <memory>
#include <initializer_list>
#include "StrBlob.h"

using namespace std;
using std::vector;
using std::string;

typedef vector<string>::size_type size_type;
//************************************main*函*数************************************//
int main()
{
	//12.6
	/*vector<int> *p(new vector<int>);
	void read(istream& in,vector<int>*p);
	void print(vector<int>*p);
	read(cin, p);
	print(p);
	delete p;
	p = nullptr;
	//12.7
	void read(shared_ptr<vector<int>> q);
	void print(shared_ptr<vector<int>> q);
	auto q=make_shared<vector<int>>() ;
	read(q);
	print(q);*/
	//12.10---exp
	/*shared_ptr<int> ptr(new int(42));
	void process(shared_ptr<int>ptr);
	process(ptr);
	process(shared_ptr<int>(ptr));
	//12.16
	unique_ptr<int> i(new int (42));
	//unique_ptr<int>j(i);//查看报错信息
	unique_ptr<int>k;*/
	//12.20
	/*ifstream in("blob.txt");
	string s;
	StrBlob blob;
	while (getline(in, s))
	{
		blob.push_back(s);
	}
	StrBlobPtr b(blob.begin()),e(blob.end());
	for (size_type i = 0; i < blob.size(); ++i)
	{
		cout << b.deref() << endl;
		b.incr();
	}*/
	//12.23
	/*
	string s1 ="Bad whether, ";
	string s2 = "bad mood.";
	char c1[] = "Bad whether,";
	char c2[]= "bad mood.";
	size_t sz1 = s1.length(),sz2=s2.length();
	size_t szc1 = strlen(c1), szc2 = strlen(c2);
	//s1 += s2;
	char* p=new char[szc1+szc2+1];
	int i = 0;
	strcpy(p, c1);
	strcat(p, c2);
	cout << p << endl;
	char* q=new char[sz1 + sz2];
	//c_str()函数返回一个指向正规C字符串的指针常量, 内容与本string串相同. 
	strcpy(q, (s1 + s2).c_str());
	cout<< q << endl;
	delete[] p;
	delete[] q;*/
	//12.24
	/*int getsize(istream& in,string& s);
	string s;
	char* ptr=new char[2];//动态数组，可以自动分配空间 
	strcpy(ptr, s.c_str());
	cout << ptr << endl;
	delete[] ptr;
	cout << s << endl;*/
	//12.26
	/*string s;
	allocator<string>alloc;
	const int n = 10;
	auto p = alloc.allocate(n);
	auto q = p;
	while (cin >> s && q != p + n)
		alloc.construct(q++, s);
	while (q != p)
	{
		cout << *(--q) << endl;
		alloc.destroy(q);
	}
	alloc.deallocate(p, 10);*/
	

	system("pause");
    return 0;
}

void read(istream& in, vector<int>*p)
{
	int t;
	cout << "Enter vector<int>:" << endl;
	while ((in >> t) && (t != 000))
		p->push_back(t);
}
void read(shared_ptr<vector<int>> q)
{
	int t;
	cout << "Enter vector<int>:" << endl;
	while ((cin >> t) && (t != 000))
		q->push_back(t);
}
void print(vector<int>*p)
{
	for (auto &pp : *p)
		cout << pp << ' ';
	cout << endl;
}
void print(shared_ptr<vector<int>> q)
{
	for (auto &qq : *q)
		cout << qq << ' ';
	cout << endl;
}
void process(shared_ptr<int> ptr)
{
	cout << *ptr << endl;
	return;
}
int getsize(istream &in, string &s)
{
	cout << "Input s: " << endl;
	getline(in, s);
	return s.length();
}