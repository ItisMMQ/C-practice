// enum.cpp: 定义控制台应用程序的入口点。
//
#include <stdlib.h>
#include "stdafx.h"
#include <stdio.h>
#include "iostream"
using namespace std;

int main()
{
	enum Color {red,yellow,blue,white,black};
	enum Color i, j, k, pri;
	int n=0, loop;
	//cout << red<<endl;
    for (i=red;i<=black;i++)
     {
		if(i!=j)
		{
			for (j = red; j <= black; j++)
			{
				if (k!=i&&k!=j)
				{
					n += 1;
					cout << n << endl;
					for (loop=1;loop<=3;loop++)
					{
						switch (loop)
						{
						 case 1:pri = i; break;
						 case 2:pri = j;break;
						 case 3:pri = k;break;
						 default:break;
						}
						switch (pri)
						{
						case red:cout << "red";break;
						case yellow:cout << "yellow"; break;
						case blue:cout << "blue"; break;
						case white:cout << "white"; break;
						case black:cout << "black"; break;
						default: break;	
						}
					}
					cout << endl;
				}
			}
			cout << "total:" << n << endl;
		}
	}
	system("pause");
    return 0;
}

