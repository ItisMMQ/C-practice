// exp.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
//#include "cctype" 不用这个头文件也可使用字符处理函数
#include <vector>

using namespace std;
using std::string;
using std::vector;

int main()
{
	//exp of string
	/*string s;
	getline(cin, s);
	//auto len = s.size();
	//cout << len << endl;
	for (auto index = 0; index < s.size(); index++)
	{
		if (ispunct(s[index])) continue;
		if (!s.empty())
			cout << s[index];
	}
	vector<string> v5;
	vector<string> v6{ 10 ,"hi" };
	vector<string>sss(10,"null");
	*/
	//3.16
	/*vector<int> num;
	int n;
	while (cin>>n)
	{
		num.push_back(n);
	}
	for (auto &i : num) i*=i;
	for (decltype(size(num)) index = 0;index<num.size();index++)
	{
		cout << num[index] << " ";
	}
	cout << endl;

	//3.17
	vector<string> str;
	string s;
	cout << "Please enter string: ";
	while (cin >> s)
	{
		str.push_back(s);
	}
	for (decltype(size(str)) index = 0;index<str.size();index++)
	{
		auto &t = str[index];
		for (auto &i:str[index])
		{
			i = toupper(i);
			cout << i << endl;
		}
	}
	*/
	//3.20
	vector<int> num;
	int n;
	cout << "Please enter an array of numbers: ";
	while(cin >>n)
	{
		num.push_back(n);
	}
	cout << "The original vector is: " <<endl;
	for( decltype(size(num)) index = 0;index<num.size();index++)
	{
		cout << num[index] << " ";
	}
	cout << endl;
	auto lenth=num.size()-1;
	for (int i=0,j=lenth;i<=j ;i++,j--)
	{
		int sum=0;
		sum = num[i] + num[j];
		cout << sum << " ";
	}
	system("pause");
	return 0;
}
