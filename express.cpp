// express.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include<vector>
#include <string>
using namespace std;
using std::string;

int main()
{
	/*int score;
	cout << "Please enter score:" << endl;
	cin >> score;
	cout << ((score > 90) ? "great" : (score > 75) ? "good" : (score > 60) ? "pass" : "fail") << endl;
	vector<int> v; int t;
	vector<string> s;string c;
    cout << "Input vector<int>:" << endl;
	while (cin >> t) v.push_back(t);
	cout << "Input vector<string>:" << endl;
	while (getline(cin, c))	s.push_back(c);
	cout <<"size of v<int>"<< sizeof(v) << endl;
	cout << "size of v<string>" << sizeof(s) << endl;
	//cout << "int " << sizeof(int) << " double " << sizeof(double) << endl;
	//输出和预想完全不同，是因为默认字符对齐还是所谓的固定部分大小?
	*/
	constexpr int size = 5;
	int ia[size] = { 1,2,3,4,5 };
	for (int *ptr=ia,ix=0;ix!=size&&ptr!=ia+size;++ix,++ptr)
	{
		cout << *ptr;
	}
	cout << endl;
	const int a = 97;
	char b = static_cast<char> (a);
	cout << "a is " << a << " b is " << b << endl;
	static_cast <char>(a);
	cout << "static_cast a will be " << a << endl;
	system("pause");
    return 0;
}

