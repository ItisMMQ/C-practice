// FOO.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "F.h"

using namespace std;
using std::vector;

int main()
{
	Foo f;
	f.push_back(1);
	f.push_back(3);
	f.push_back(4);
	f.push_back(2);
	f.sorted().print();//这个是右值吗
	vector <int>v = { 1,4,2,3 };
	sort(v.begin(), v.end());
	for (auto vv : v)
		cout << vv << ' ';
	system("pause");
    return 0;
}

