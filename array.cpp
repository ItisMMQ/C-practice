// array.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;

int main()
{
	/*int a1[10]={1,2,3,4,5,6,7,8,9,10}, a2[10]{1,2,3,4,5,6,7,8,9,10 };
	vector<int> b;
	int *p = a1;
	cout << "Length of a1:"<<sizeof(a1)<<" ,content is: ";
    for (int i = 0; i < 10; i++, p++)	cout<<*p<<" ";
	cout << endl;
	for (int i=0;i<10;i++)  b.push_back(a1[i]);
	cout << "Length of b:" << sizeof(b) << " ,content is: ";
	for (auto num : b) cout<< num<<" ";
	cout << endl;
	if(sizeof(a1)==sizeof(b))
	{ for (int n=0;n<sizeof(a1);n++)
	{ 
		if(a1[n]==b[n]) continue;
		else { cout << "Content different" << endl; break; }
	 }
	}
	else cout<< "Length different" << endl;
	string s1 = "You", s2 = "you";
	if (s1 == s2) cout << "s1= s2" << endl;
	else cout << "s1 !=s2"<<endl;
	char c1[] = { "You" }, c2[] = { "you" };
	if (strcmp(c1, c2) == 0) cout << "c1=c2" << endl;
	else cout << "c1!=c2" << endl;*/
	//int a = 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2;
	//cout << "a = " << a;
	int a,b,c,d,t;
	while (cin >> a && a != 42)
	{
		cout << a ;
		if (a % 2 == 0) cout << " is an even num." << endl;
		else cout << " is an odd num." << endl;
	}
	//if (a > b&&b > c&&c > d) cout << "a= " << a << "b= " << b << "c= " << c << "d= " << d << endl;
	//else cout << "a,b,c,d should be sorted." << endl;
	//cout << "Please enter a:" << endl;
	//cin >> a ;
	
	system("pause");
    return 0;
}

