// Tuple.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <regex>
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <sstream>
#include <fstream>

using namespace std;
using std::vector;
using std::string;
using namespace std::regex_constants;

int main()
{
	//tuple<int, int, int> tp1{ 10,20,30 };
	//tuple<string, vector<string>, pair<string, int>> tp2{ "hello",{"my","I"," know"," your","name?"},make_pair<string,int>("oops",2)};
	//P646
	/*
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex r1(pattern);
	smatch result1;
	string test_str = "recipt freind theif receive";
	if (regex_search(test_str, result1, r1))
		cout << result1.str() << endl;
	//P648
	regex r2("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
	smatch result2;
	string filename;
	while (cin >> filename)
		if (regex_search(filename, result2, r2))
			cout << result2.str() << endl;
	//P655
	bool valid(const smatch&);
	string phone =
		"(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]/)?(\\d{4}))";
	regex r3(phone);
	string s3;
	while (getline(cin, s3))
	{
		for (sregex_iterator it(s3.begin(), s3.end(), r3), end_it; it != end_it; ++it)
			if (valid(*it))
				cout << "valid: " << it->str() << endl;
			else
				cout << "not valid: " << it->str() << endl;
	}
	//657
	string fmt = "$2.$5.$7";
	regex r4(phone);
	string number = "(908) 555-1800";
	cout << regex_replace(number, r4, fmt) << endl;
	//P658
	regex r5(phone);
	smatch m5;
	string s5;
	string fmt5 = "$2.$5.$7";
	while (getline(cin, s5))
		cout << regex_replace(s5, r5, fmt5) << endl;
	//P659
	cout << regex_replace(s5, r5, fmt5, format_no_copy) << endl;//必须要using命名空间
	*/
	//P661
	/*
	uniform_int_distribution<unsigned> u(0, 9);
	default_random_engine e;
	for (size_t i = 0; i < 10; ++i)
		cout << u(e) << " ";
	cout << '\n';
	cout << "min: " << e.min() << " max: " << e.max() << endl;
	//P662 -- 错误示例
	vector<unsigned> bad_randVec();
	vector<unsigned> v1(bad_randVec());
	vector<unsigned> v2(bad_randVec());
	cout << ((v1 == v2) ? "v1 is equal to v2" : "v1 is not equal to v2") << endl;
	//正确示例
	vector<unsigned> good_randVec();
	vector<unsigned> v3(good_randVec());
	vector<unsigned> v4(good_randVec());
	cout << ((v3 == v4) ? "v3 is equal to v4" : "v3 is not equal to v4") << endl;
	//P663--- 随机数种子
	default_random_engine e1;
	default_random_engine e2(2147483646);
	default_random_engine e3;
	e3.seed(32767);
	default_random_engine e4(32767);
	for (size_t i = 0; i != 100; ++i)
	{
		if (e1() == e2())
			cout << "unseeded match at iteration: " << i << endl;
		if (e3() != e4())
			cout << "seeded differs at iteration: " << i << endl;
	}
	default_random_engine e5(time(0));
	for (size_t i = 0; i != 10; ++i)
		cout << e5() << " ";
	cout << endl;
	//P664
	default_random_engine e6;
	uniform_real_distribution<double> u6(0, 1);
	for (size_t i = 0; i < 10; ++i)
		cout << u6(e6) << " ";
	cout << '\n';
	uniform_real_distribution<> u7(0, 1);
	//P665
	default_random_engine e8;
	normal_distribution<> n8(4, 1.5);
	vector<unsigned> vals(9);//9个元素均为0
	for (size_t i = 0; i != 200; ++i)
	{
		unsigned v = lround(n8(e8));//舍入到最接近的整数
		if (v < vals.size())
			++vals[v];
	}
	for (size_t j = 0; j != vals.size(); ++j)
		cout << j << ": " << string(vals[j], '*') << endl;

	string reap;
	default_random_engine e9;
	bernoulli_distribution b;
	do
	{
		bool first = b(e9);
		cout << (first ? "We go first" : "You get to go first") << endl;
		cout << ((play(first)) ? "Sorry,you lost" : "Congrats,you won") << endl;
		cout<<"Play again? Enter 'yes' or 'no' "<<endl;
	}while (cin>>resp&&resp[0]=='y');
	bernoulli_distribution b(.55);//调整概率
	*/
	//IO库再探
	//P667
cout << "default boo values: " << true << " " << false
<< "\nalpha bool values: " << boolalpha << true << " " << false << endl;
//bool bool_val = get_status();
cout << boolalpha << noboolalpha << true << ' ' << false << endl;
cout << "default: " << 20 << " " << 1024 << endl;
cout << "octal: " << oct << 20 << " " << 1024 << endl;
cout << "hex: " << hex << 20 << " " << 1024 << endl;
cout << "decimal: " << dec << 20 << " " << 1024 << endl;
cout << showbase;
cout << boolalpha << noboolalpha << true << ' ' << false << endl;
cout << "default: " << 20 << " " << 1024 << endl;
cout << "octal: " << oct << 20 << " " << 1024 << endl;
cout << "hex: " << hex << 20 << " " << 1024 << endl;
cout << "decimal: " << dec << 20 << " " << 1024 << endl;
cout << noshowbase;
cout << uppercase << showbase << hex << "printed in hexadecimal: " << 20 << " " << 1024 << nouppercase << noshowbase << dec << endl;
//打印精度
cout << "Precision: " << cout.precision() << ", Value:" << sqrt(2.0) << endl;
cout.precision(12);
cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
cout << setprecision(3);
cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
cout << "default format: " << 100 * sqrt(2.0) << '\n'
<< "scientific: " << scientific << 100 * sqrt(2.0) << '\n'
<< "fixed decimal: " << fixed << 100 * sqrt(2.0) << '\n'
<< "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << '\n'
<< "use defaults: 	" << defaultfloat << 100 * sqrt(2.0) << "\n\n";
cout << 10.0 << endl;
cout << showpoint << 10.0 << noshowpoint << endl;
//输出补白
int i = -16;
double d = 3.14159;
cout << "i: " << setw(12) << i << "next col" << '\n'
<< "d: " << setw(12) << d << "next col" << '\n';
cout << left
<< "i: " << setw(12) << i << "next col" << '\n'
<< "d: " << setw(12) << d << "next col" << '\n'
<< right;
cout << right
<< "i: " << setw(12) << i << "next col" << '\n'
<< "d: " << setw(12) << d << "next col" << '\n';
cout << internal
<< "i: " << setw(12) << i << "next col" << '\n'
<< "d: " << setw(12) << d << "next col" << '\n';
cout << setfill('#')
<< "i: " << setw(12) << i << "next col" << '\n'
<< "d: " << setw(12) << d << "next col" << '\n'
<< setfill(' ');
//控制输入格式
char ch;
while (cin >> ch)
cout << ch;
cin >> noskipws;
while (cin >> ch)
cout << ch;
cin >> skipws;
//未格式化的输入输出操作
//P673
char ch2;
while (cin.get(ch2))
cout.put(ch2);//输入输出完全相同
int ch3;
while ((ch3 == cin.get()) != EOF)
cout.put(ch3);
//流随机访问
fstream inOut("copyOut", fstream::ate | fstream::in | fstream::out);
if (!inOut)
{
	cerr << "unable to open file!" << endl;
	return EXIT_FAILURE;
}
auto end_mark = inOut.tellg();
inOut.seekg(0, fstream::beg);
size_t cnt = 0;
string line;
while (inOut&&inOut.tellg() != end_mark && getline(inOut, line))
{
	cnt += line.size() + 1;
	auto mark = inOut.tellg();
	inOut.seekp(0, fstream::end);
	inOut << cnt;
	if (mark != end_mark) inOut << " ";
	inOut.seekg(mark);
}
inOut.seekp(0, fstream::end);
inOut << "\n";
return 0;

		;
	system("pause");
    return 0;
}
/**********************************************************************************************/
bool valid(const smatch& m)
{
	if (m[1].matched)
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	else
		return !m[3].matched&&m[4].str() == m[6].str();
}
//P662
vector<unsigned> bad_randVec()
{
	default_random_engine e;
	uniform_int_distribution<unsigned> u(0, 9);
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
		ret.push_back(u(e));
	return ret;
}
vector<unsigned> good_randVec()
{
	static default_random_engine e;
	static uniform_int_distribution<unsigned> u(0, 9);
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
		ret.push_back(u(e));
	return ret;
}
