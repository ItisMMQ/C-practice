// error.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

using namespace std;
using std::string;

int main()
{
	//P177--5.24
	string s;
	float a, b;
	cout << "Please enter a and b:" << endl;
	while(cin>>a>>b)
	{
		try
		{
			if (b == 0)
				throw runtime_error("b can not be 0!");
			cout << "a/b= " << a / b << endl << "Keep going?" << endl;
			cin >> s;
			if (s == "n" || s == "N") break;
			else 
			{
				cout << "Please enter new a and b:" << endl;
				continue;
			}
		}
		catch(runtime_error err)
		{
			cout << err.what()<<" Continue?"<<endl;
			cin>> s;
			if (s != "n" && s != "N") 
			{
				cout << "Please re-enter a and b:" << endl; 
				continue; 
			}
		}
	}
	system("pause");
    return 0;
}

