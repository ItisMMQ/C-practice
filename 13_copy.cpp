// 13_copy.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include<algorithm>
#include "hcopy.h"

using namespace std;
using std::string;

/* print(Employee &e)
{
	std::cout << e.id() << std::endl;
}
int Employee::I_D = 0;//静态成员类外定义//这句话若出现在头文件中则无法正常运行
*/
int main()
{
	/*int a = 3;
	string st = "abc";
	int *b = &a;
	X x1(1,st, b);
	X x2(x1);
	cout << x2.i <<' '<< x2.s<<' ' << *x2.p;
	//numbered n1,n2=n1,n3=n2;
	//cout << n1.mysn << ' ' << n2.mysn << ' ' << n3.mysn << endl;*/

	//13.17
	/*A a, b = a, c = b;
	void show3(const A& a);
	show3(a);//这里的调用不需要拷贝构造运算符
	show3(b);
	show3(c);*/
	//13.18
	/*void print(Employee&);
	Employee a("Danna"), b, c=a;
	print(a);
	print(b);
	print(c);*/
	//13.22
	//StrBlob datum1, datum2 = datum1;
	//13.30
	HasPtr a(3), b("you"),c(1);
	//swap(a, b);
	//13.30
	vector<HasPtr> V;
	V.push_back(a);
	V.push_back(b);
	V.push_back(c);
	sort(V.begin(),V.end());
	show(V);
	system("pause");
	return 0;
}