// func.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
using std::string;
using std::vector;

void add(initializer_list<int>i) 
{
	int sum = 0;
    for (const auto &j : i)
		sum +=j;
	cout<<"sum is " << sum<<endl;
}

bool str_subrange(const string &str1, const string &str2)
{
	if (str1.size() == str2.size()) return str1 == str2;
	auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();
	for (decltype(size) i = 0; i != size; ++i)
	{
		if (str1[i] != str2[i]) return 0;
	}
	return 1;
}

//6.32
int& get(int *arry, int index)
{
	return arry[index];
}

//6.33
int process(vector<string>::iterator beg,vector<string>::iterator end)
{
#ifndef NDEBUG
	cerr << __func__ << " size is " << end - beg << endl;
#endif 
	auto it = beg;
	if (it != end)
	{ 
		cout << *it << ' ';
		string s = *it;
		return process(++beg, end);
	}
	 return 0;
}
//6.37,6.38
/*int(*funct(int i)) [10]
{
	;
}
int a[10] = { 0 };
decltype(a)&arrptr(int i) {}*/
//6.42
string make_plural (size_t ctr,const string &word,const string &end="s")
{
	return(ctr > 1) ? word + end : word;
}
//6.44
/*bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
	//constexpr 错误，参见std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size用法;
}*/
//6.51&6.53
/*void f() { cout << "1"; }
void f(int) { cout << "2"; }
void f(int, int) { cout << '3'; }
void f(double, double) { cout << '4'; }
void f(int&, int&) { ; }
void f(const int&, const int &) { ; }
void f(char *, char *) { cout << "char *"; }
void f(const char *, const char*) {cout<<"const char *" ; }
*/
//6.54
//typedef int nouse(int a, int b);
//vector<nouse> ok;
//6.55
int plu(int a, int b) { return a + b; }
int minu(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int devide(int a, int b) { return a / b; }
typedef int (*fun)(int a, int b);
vector<fun> funcs ={plu,minu,mul,devide};


int main()
{/*//6.32
	initializer_list<int> a{ 1,2,3,4,5,6,7,8,9,10};
	add(a);//调用add函数求和
	string str1, str2;
	cout << "Enter 2 strings:" << endl;
	cin >> str1 >> str2;
	if (str_subrange(str1, str2)) cout << "str1=str2 or str1 is subset of str2" << endl;
	else cout << "str1!=str2" << endl;
	int ia[10];
	for (int i = 0; i != 10; ++i)
	{
		get(ia, i) = i;
		cout << ia[i] <<"  ";
	}*/
	/*string s;
	vector<string>str;
	cout << "Input an string vector:" << endl;
	while (cin >> s)
		str.push_back(s);
	auto b = str.begin(), e = str.end();
	process(b, e);
	/*
	//6.42
	vector<string> word;
	string w,u,v;
	while (cin >> w&&w!="end")  word.push_back(w);
	auto b = word.begin(), e = word.end();
	int ctr = 1;
	string curr = *b;
	for (auto it=b; it!=e; ++it)
	{
		if (it== b)
			continue;
		string temp =*it;
		if (curr == temp)
		{
			++ctr;
			if (it == e - 1)
			{
			string str = make_plural(ctr, curr);
			cout << str << " " << ctr << "times  " << endl;
			}
			continue;
		}
		if(curr!=temp)
		{
			string str = make_plural(ctr, curr);
			cout <<str<<" "<< ctr << "times  "<< endl;
			curr = temp;
			ctr = 1;
			continue;
		}
	}*/
	/*cout << "Please input string u and v:" << endl;
	cin >> u >> v;
	cout<<isShorter(u, v);*/
	//6.55
	for(int i=0;i<4;++i) 
	{
		int a, b;
		cout << "input a,b: ";
		cin >> a >> b;
		cout << funcs[i](a, b)<<endl;
	}
	system("pause");
    return 0;
}