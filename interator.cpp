// interator.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
using std::string;
using std::vector;

int main()
{
	string s;
	cout << "Please enter s:" << endl;
	getline(cin, s);
	cout << "The ordinary s: " <<s<< endl;
	for (auto it=s.begin();it !=s.end()&&!isspace(*it);it++)
	{
		*it = toupper(*it);
		cout << *it;
	}
	cout << "New s is:"<<s << endl;

	vector<int> v; int t;
	while (cin>>t)
	{
		v.push_back(t);
	}
	for (auto i = v.cbegin(); i != v.cend(); i++)
		cout << *i << " ";
	cout << endl;


	vector<int> v1; int v2;
	cout << "Input vector<int>v1(10):" << endl;
	while (cin>>v2)
	{
		v1.push_back(v2);
	}
	cout << "New v1: " ;
	//for (decltype(v1.size()) index = 0; index <10; index++)
	for(auto b=v1.begin(),e=v1.end();b<e;b++)
	{
		*b = *b * 2;
		cout << *b<< " ";
	}
	cout << endl;

	vector<int> v3;int temp;
	cout << "Please input some num to addition";
	while (cin >> temp)
	{
		v3.push_back(temp);
	}
	for(auto b = v3.begin(), e = v3.end()-1, mid = (b + v3.size() / 2);b<mid;b++,e--)
	{
		int sum = *b + *e;
		cout << sum<<" ";
	}
	*
	//scores sort
	vector<unsigned>scores(11, 0),grade;
	unsigned g;//in order to send num to grade
	cout << "Enter scores:" << endl;
	while (cin>>g)//42 65 95 100 39 67 92 77 84 72 81 98 79 92 17 10
	{
		grade.push_back(g);//gain grades
	}
	auto cite = grade.begin(), sco = scores.begin();//initiate
	for (;cite<grade.end();cite++)
	{
		++*(sco + *cite / 10);//++ must be set ahead
	}
		for (; sco < scores.end(); sco++)
			cout << *sco << " ";
	
	system("pause");
    return 0;
}
