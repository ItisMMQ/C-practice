// template3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "head3.h"
//#include "Sales_data.hpp"
#include <iostream>
#include <string>
#include <unordered_set>


using namespace std;
using std::string;
using std::unordered_set;

int main()
{
	//16.62
	/*sales_data testdata("C primer", 5, 20);
	unordered_set<sales_data> myrp;
	myrp.emplace(testdata);
	cout << "the hash code of " << testdata.ISBN()<< ":\n0x" << std::hex << std::hash<sales_data>()(testdata)<< "\n";*/
	//16.63
	string s = "hello";
	vector<string> vs = { "1234","hello","maybe","oops" ,"hello"};
	vector<int> vi = { 3,1,4,1,5,9,2,6,5,1,5};
	vector<double> vd = { 3.14,7.28,9.02,6.51,9.11};
	cout << cnt(vs, s) << endl;//2
	cout << cnt(vi, 1) << endl;//3
	cout << cnt(vd, 3.14) << endl;//1
	//16.64
	const char* c1 = "hello";
	vector<const char*> vc = { "hello","hello" ,"baby","you","call"}; 
	cout << cnt(vc, c1) <<','<<cnt(vc,"baby")<< endl;//2,1

	system("pause");
    return 0;
}

