// template.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <initializer_list>
#include <utility>
#include "head.h"

using namespace std;
using std::string;
using std::vector;

int main()
{/*
	//cout<<compare(5, 6)<<'\n';
	vector<int> v1{ 1,2,3,4,5 }, v2{6,7,8,9,0 };
	//cout << compare(v1, v2) << '\n';
    //cout << compare("hi", "dad")<<'\n';
	cout<<"index= "<<myfind(v1.cbegin(), v1.cend(), 3) << '\n';
	int a[10] = { 1,2,3,4,5,6,7,8,9,0 };
	print(a);
	Blob<string> articles = { "a","an","and" };
	Blob<int> squares = { 1,2,3,4,5,6,7,8,9,10 };
	for (size_t i = 0; i != squares.size(); ++i)
	{
		squares[i] = i * i;
		cout << squares[i]<<'\t';
	}
	//16.19
	vector <string> arti = { "a","an","and" };
	OK(arti);*/
	double *p = new double(3.1415);
	DebugDelete d;
	d(p);
	int *ip = new int(2);
	DebugDelete()(ip);
	 myptr::shared_ptr<int> p(1);
	system("pause");
    return 0;
}

