// statement.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include<vector>

using namespace std;
using std::string;
using std::vector;

int main()
{//将分数变为等级
	/*
	const vector<string> scores = { "F","D","C","B","A" ,"A++"};
	string lettergrade;
	int score,num=0;
	cin >> score;
	score < 60 ? lettergrade = scores[0] : lettergrade = scores[(score - 50) / 10];
	//if (score < 60) lettergrade = scores[0];
	//else lettergrade = scores[(score - 50) / 10];
	if (score != 100)
	{ 
		(score % 10 >= 7) ? (lettergrade += '+') : (score % 10 <= 3) ? (lettergrade += '-') : lettergrade;
	}
	//if (score % 10 >= 7) lettergrade += '+';
	//if (score!=100&&score % 10 <= 3) lettergrade += '-';
	cout << score << " " << lettergrade << endl;
	//记录一段话中重复的元音个数
	string a;
	int aCnt=0, eCnt=0,iCnt=0,oCnt=0, uCnt=0,index=0,am=0,is=0,are=0;
	cout << "Enter a:" << endl;
	while(cin>>a)
	{
		for (auto &r : a)
		{
			//if (r == 'a' || r== 'e' || r == 'i' || r == 'o'|| r == 'u') ++num;
			//if (r == 'A' || r == 'E' || r == 'I' || r == 'O' || r == 'U') ++num;
			switch (r)
			{
			case 'a':case'A':++aCnt; break;
			case 'e':case'E':++eCnt; break;
			case'i':case 'I':++iCnt; break;
			case'o':case'O':++oCnt; break;
			case'u':case'U':++uCnt; break;
			}
			if (index!=0) 
			{
				if (a[index-1] =='a'&& a[index] == 'm') ++am;
				if (a[index-1] == 'i'&& a[index+1] == 's')  ++is;
				if (index>1&&(a[index] == 'a'&&a[index +1] == 'r'&&a[index+2] == 'e')) ++are;
			}
	++index;
	}
	}
	cout << "a  e  i  o  u:" << endl;
	cout << aCnt << "  " << eCnt << "  " << iCnt << "  " << oCnt << "  " << uCnt << endl;
	cout << "am   is  are:"<<endl;
	cout << am << "  "<<is << "  " << are << endl;*/
	//记录连续重复字符的次数
	/*vector<string> str;
	string s,cur;
	int cnt = 0;
	if(cin >> cur)
	{
		str.push_back(s);
		cnt = 1;
		while (cin >> s)
		{
			str.push_back(s);
			if (s == cur) ++cnt;
			else 
			{
				cout << cur << " occurs " << cnt << " times " << endl;
				cur = s; 
				cnt = 1;
			}
		}
	}
	for (auto &a : str)
	{
		cout << a << endl;
	}*/
	//判断一串数字是否是另一串的前缀
	/*vector<int> v1, v2;
	int t1, t2,i,j;
	cout << "Please input v1:" << endl;
	while (cin >> t1)  v1.push_back(t1);
	cin.clear();
	cout << "Please intput v2:" << endl;
	while (cin >> t2) v2.push_back(t2);
	decltype(v1.size()) i1 =v1.size(); decltype(v2.size()) i2 = v2.size();
	if (i1 <= i2) i = i1;
	else i = i2;
	for (j= 0; j < i; j++)
	{
		if (v1[j] == v2[j]) continue;
		else cout << "False";
	}
	//if (j == i) cout << "True*/
	/*string rsp;
	do
	{
		cout << "Please ener 2 values: ";
		int val1 = 0, val2 = 0;
		cin >> val1 >> val2;
		cout << val1 + val2 << endl << "Continue?" << endl;
		cin >> rsp;
	} while (!rsp.empty()&&rsp!="N");
	string c;
	cout << "Please enter a and b:" << endl;
	do 
	{
		string a = {}, b = {};
		cin >> a >> b;
		if (a.length() < b.length()) cout << a<<endl;
		else cout << b<<endl;
		cout << "Continue?Y or N: ";
		cin >> c;
	} while (!c.empty()&&c[0]!='N');*/
	int count=1;
	vector<string> str;
	string s,t;
	if (cin >> t)
	{
		while (cin >> s)
		{
			if (s == t)
			{
				if (count < 2) 
				{
					t[0] = toupper(t[0]);
					str.push_back(t);
					t[0] = tolower(t[0]);
					s[0] = toupper(s[0]);
					str.push_back(s);
					++count;
					continue;
				}
				else
				{
					s[0] = toupper(s[0]);
					str.push_back(s);
					++count;
				}
			}
			else
			{
				str.push_back(s);
				cout << t << " occurs " << count << " times" << endl;
				t = s;
				count= 1;
			}
		}
	}
	int sz;
	while (cin >> sz)
	{
		if (sz <= 0) continue;
		else break;
	}
	system("pause");
    return 0;
}
