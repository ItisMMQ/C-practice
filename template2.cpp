// template2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "t2head.h"
#include <iostream>
#include <string>

using namespace std;
using std::string;

int main()
{
	//16.47
	int a = 5;
	/*void f(int v1, int &v2);
	flip(f, a, 42);
	cout << "a=" << a << endl;*/
	//P615
	/*string s("hello");
	cout << debug_rep(s) << endl;//第一个版本
	cout << debug_rep(&s) << endl;//第二个版本
	const string *sp = &s;
	cout << debug_rep(sp) << endl;//特例化版本，即第二个版本
	cout << debug_rep(s) << endl;//选择非模板版本，即特例化版本
	int i = 42, *p = &i;
	const int ci = 0, *p2 = &ci;
	//16.49
	g(42);//调用g(T t)
	g(p);//调用g(T *t)
	g(ci);//调用g(T t)
	g(p2);//调用g(T *t)
	f(42);
	f(p);
	f(ci);
	f(p2);
	//16.50
	//cout << debug_rep("Linda,17,female") << endl;
	//16.51
	double d1= 3.14,d2=6.28,d3=7.85; string ss = "how now brown cow";
	foo(i, s, 42, d1,d2,d3);//Args与rest数目总是一样的，即使参数有相同类型
	//16.53
	print(cout, i, s, d1, 7);*/
	//16.65
	cout << debug_rep("Linda,17,female") << endl;
	system("pause");
    return 0;
}

void f(int v1, int &v2)
{
	std::cout << v1 << " " << ++v2 << std::endl;
}