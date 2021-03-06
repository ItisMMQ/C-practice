// function.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
//#include "Chapter6.h"
#include <math.h>

using namespace std;
using std::string;
using std::vector;

int fact(int a) //求n!
{
	int res=1;
	while (a > 1) res *= a--;
	static int b = 0;//静态局部变量
	cout << "static local vaiable b = " << b << endl;
	++b;
	return res;
}

int UI()//人机交互，输入要求n!的数 
{
	cout << "Please enter a number:" << endl;
	int a;
	cin >> a;
	return a;
}
//形参为引用类型
void reset1 (int &a, int &b)//交换a,b的值
{
	int t= a;
	a = b;
	b = t;
}

void reset2(int *a, int *b) //6.22
{
	int t = *a;
	*a = *b;
	*b = t;
}

bool isUPcase(const string &s)//判断该字符串中是否有大写字母
{
	bool flag = 0;
	for(const char &a:s)
	{
		if (isupper(a))
		{
			flag = true; 
			break;
		}
	}
	return flag;
}
//形参是对数组的引用
/*void compare(const int(&a)[3][3],const int(&b)[3][3])//比较行列式a,b的大小
{
	;
}*/
//6.24
void print(const int a[10])
{
	for (size_t i = 0; i != 10; ++i)
		cout << a[i] << ' ';
	cout << endl;
}

int main()
{
	int m, n;
	int *a =& m, *b =& n;
	int **q =& a, **p = &b;//利用指针的指针来改变int *a和int *b的地址
	cin >> m >> n;
	reset2(*q, *p);//*q和*p是a和b的地址
	cout << *a<<' '<<*b<<endl;
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	print(arr);
	initializer_list<int> f{ 1,2,3,4,5,6,7,8,9,0 }, g;
	g = f;
	/*int num, sum;
	string s,str;
	cout << "Get the n! " << endl<<"Press y to start.";
	cin >> s;
	if (s == "y" || s == "Y")
	{
		do
		{
			num = UI();//数据输入
			if (num < 0) num = -num;
			sum = fact(num);//求n!
			cout << "num!= " << sum << endl << "Continue?" << endl;
			cin >> s;
		} while (s != "n"&&s != "N");
	}
	int a, b, c[][3] = { 1,2,3,4,5,6,7,8,9 }, d[][3] = { 9,8,7,6,5,4,3,2,1 };
	cout << "Enter 2 nums to switch:" << endl;
	cin >> a >> b;
	reset1(a,b);//a,b交换
	cout << "Now a=" << a << ", b=" << b << endl;
	cout << "Is uppercase:" << endl;
		cin >> str;
	if (isUPcase(str) == 1) cout << "there is uppercase!" << endl;//判断该字符串中是否有大写字母
	//compare(c, d);比较行列式a,b大小*/
	system("pause");
    return 0;
}

