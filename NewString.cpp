// NewString.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>
#include "String.h"

using namespace std;
using std::vector;

int main()
{
	const char *a = "Hello World!";
	String s1("Hello");
	String s2(a);
	String s3;
	vector<String> s;
	s.push_back(s1);//没有cout
	s.push_back(s2);//没有cout
	s.push_back(s3);//cout默认构造函数
	//当多次push_back的时候会执行移动构造
	system("pause");
    return 0;
}

