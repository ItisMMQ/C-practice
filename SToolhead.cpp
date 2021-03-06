// STools.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <exception>
#include <new>
#include <memory>
#include <cstdlib>
#include <typeinfo>
#include "head.hpp"   //19.3
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

/*enum Tokens { INLINE = 11, VIRTUAL = 12 };
//19.2
void *operator new(size_t size)
{
	cout << "new(size_t), size= "<<size<< endl;
	if (void *mem = malloc(size))
		return mem;
	else
		throw bad_alloc();
}
void operator delete(void *mem) noexcept 
{
	cout << "delete(void*)" << endl;
	free(mem); 
}*/

int main()
{
	//19.2
	/*int* a = new int(20);
	cout << a << " " << *a << endl;
	delete a;
	double* b = new double(3.14);
	cout << b << ' ' << *b << endl;
	delete b;*/
	//19.3
	/*A *pa1= new C;
	if (B *pb1 = dynamic_cast<B*>(pa1))
		cout << "1"<<endl;
	else
		cout << "11" << endl;
	delete pa1;
	B *pb2 = new B;
	if (C *pc2= dynamic_cast<C*>(pb2))
		cout << "2" << endl;
	else
		cout << "22" << endl;
	delete pb2;
	A *pa3= new D;
	if (B *pb3 = dynamic_cast<B*>(pa3))
		cout << '3' << endl;
	else
		cout << "33" << endl;
	delete pa3;
	//19.9
	int arr[10];
	string s;
	Derived d;
	Base *b=&d;
	cout << typeid(42).name() << '\n'
		<< typeid(arr).name() << '\n'
		<< typeid(s).name() << '\n'
		<< typeid(b).name() << '\n'
		<<typeid(*b).name()<<endl;
	//19.10
	A *pa = new C;
	cout << typeid(pa).name() << endl;
	C cobj;
	A& ra = cobj;
	cout << typeid(&ra).name() << endl;
	B *px = new B;
	A& rra = *px;
	cout << typeid(rra).name() << endl;
	//P737
	enum color{red,yellow,green};
	enum class peppers{red,yellow,green};
	color eyes = green;
	peppers pop = peppers::green;
	enum class intType
	{
		charTyp = 8, shortTyp = 16, intTyp = 16,
		longTyp = 32, long_longTyp = 64
	};
	//P739
	void ff(Tokens);
	void ff(int);
	Tokens curTok = INLINE;
	ff(13);
	ff(INLINE);
	ff(curTok);*/
	//P739
	/*const string Screen::*pdata;     
	pdata = Screen::data();
	Screen myScreen, *pScreen = &myScreen;
	auto s = myScreen.*pdata;
	s = pScreen->*pdata;
	//19.12
	const string::size_type Screen::*curs;
	curs = Screen::cs();
	auto c=myScreen.*curs;
	//P741
	auto pmf = &Screen::get_cursor;//auto = char (Screen::*pmf)() const
	char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
	pmf2 = &Screen::get;
	char c1 = (pScreen->*pmf)();
	char c2 = (myScreen.*pmf2)(0, 0);*/
	/*using Action = char (Screen::*)(Screen::pos, Screen::pos) const;//成员指针的类型别名
	Action get = &Screen::get;
	Screen & action(Screen&, Action = &Screen::get);*/
	/*auto pmf3 = &Screen::get_cursor;
	pmf3 = &Screen::get;*/
	//将成员函数用作可调用对象
	/*vector<string> svec={ "empty","null","","nill","","nought","zero","fool you"};
	//vector<string*> pvec;
	function<bool(const string*)>fp = &string::empty;//指针形式
	function<bool(const string&)>fr = &string::empty;//引用形式
   // find_if(pvec.begin(), pvec.end(), fp);
	find_if(svec.begin(), svec.end(), mem_fn(&string::empty));
	auto f = mem_fn(&string::empty);
	f(*svec.begin());
	f(&svec[0]);
	auto it = find_if(svec.begin(), svec.end(), bind(&string::empty, _1));//_1需用using namespace std::placeholders，声明占位符
	auto f2 = bind(&string::empty, _1);
	f2(*svec.begin());
	f2(&svec[0]);
    //19.18
	cout << "There are " << count_if(svec.begin(), svec.end(), fr)<< " null strings in svec. " <<'\n'<< endl;
	//Nested class---19.20
	ifstream input("1.txt");
	ofstream output("2.txt");
	if (input&&output)
		runQueries(input);
	else
		cerr << "Couldn't open files.";
	input.close();
	output.close();/**/
	system("pause");
    return 0;
}

/*//P739
void ff(Tokens){	cout << "ff(Tokens)" << endl;}
void ff(int) {cout << "ff(int)" << endl; }*/