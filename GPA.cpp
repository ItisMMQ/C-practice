// GPA.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;

typedef struct 
{
	string subject;
	float score;
	int credit;
	float point;
	char level;	
}GPA;

int main()
{
	vector<GPA> gpa;
	GPA one;
	float result=0;
	cout << "Enter subject,score,credit:" << '\n';
	while (cin>>one.subject>>one.score>>one.credit)
	{
		gpa.push_back(one);
		cout << endl;
	}
/*
    grade        level    point
	90 - 100     A          4.0
	85 - 89       A -        3.7
	82 - 84       B +       3.3
	78 - 81       B          3.0
	75 - 77       B -        2.7
	71 - 74       C +       2.3
	66 - 70       C          2.0
	62 - 65       C -        1.7
	60 - 61       D          1.3
	补考60      D -        1.0
	<60            F            0
*/
	for (auto &g:gpa)
	{
		if (g.score>70)
		{
		}
		else
		{

		}

	}
	system("pause");
	return 0;
}

