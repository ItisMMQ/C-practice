// Associative_C.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <set>
#include <cctype>
#include <algorithm>
#include <utility>//pair
#include <unordered_set>
#include <unordered_map>

using namespace std;
using std::string;
using std::vector;

struct sales_data
{
	friend istream &read(istream &is, sales_data&datum);
	friend ostream &print(ostream &os, const sales_data &datum);
	friend sales_data add(const sales_data &lhs, const sales_data &rhs);
	//构造函数---特殊的成员函数
	//sales_data() = default;//默认初始化
	//sales_data(const string &s):bookNo(s){}//仅用于初始化，没有其它操作，故函数体为空
	sales_data(const string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n) {}
	sales_data(istream &);//读取交易信息,并在函数体内部进行初始化
						  //委托构造函数
	sales_data() :sales_data("\t", 0, 0) { }
	sales_data(const string &s) :sales_data(s, 0, 0) { }
	//成员函数-----都是inline的
	string ISBN() const { return bookNo; }
	sales_data& combine(const sales_data&);
	void print();
private:
	double avg_price() const;//将const放在参数列表之后，表示参数是const类型
							 // 成员
	string bookNo;//ISBN书号
	unsigned units_sold = 0;//单次销售量，类内初始化
	double u_price;//单价
	double revenue = 0.0;//单次交易收入
};

//*******************成**员**函**数**定**义*************************//
sales_data::sales_data(istream &is)
{
	read(is, *this);
}
//成员函数实现明细
sales_data & sales_data::combine(const sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

inline double sales_data::avg_price() const//定义和声明  只写明一次inline就够了
{
	if (units_sold) return revenue / units_sold;
	else return 0;
}
//*******************外**部**函**数**定**义*************************//
void sales_data::print()
{
	cout << "ISBN:" << bookNo << "  total sold:" << units_sold
		<< "  revenue:" << revenue << "average price: " << avg_price() << endl;
}

//P234,定义外部函数read，print和add
istream &read(istream &is, sales_data&datum)//为某个已声明的对象初始化或赋新值
{
	double price = 0;
	cout << "Enter bookNo,units_sold and price:" << endl;
	is >> datum.bookNo >> datum.units_sold >> price;
	datum.revenue = price * datum.units_sold;
	return is;
}
ostream &print(ostream &os, const sales_data &datum)//对象输出
{
	os << "ISBN:" << datum.ISBN() << " units sold: " << datum.units_sold
		<< " total revenue: " << datum.revenue << " average price: " << datum.avg_price() << endl;
	return os;
}
sales_data add(const sales_data &lhs, const sales_data &rhs)//实际用途不详
{
	sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

int main()
{
	//11.3
	/*map<string, size_t>word_count;
	set<string> exclude = { "And","Or","But","The","A","An","and","or","but","the","a","an" };
	for (auto &e : exclude)
		cout << e << ' ';//set会自动排序
	cout << endl;
	string word;
	while (cin >> word)
	{
		for (auto it = word.begin(); it != word.end(); ++it)
		{
			*it=tolower(*it);
			word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());//删除从标点到结尾
		}
		if(exclude.find(word)==exclude.end())
			++word_count[word];//只统计不在exclude里的单词
	}
	for (const auto &w : word_count)
		cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " times") << endl;*/
	//11.7
	/*map<string, vector<string>> family;
	string last_name, first_name,c;
	//**使用Lambda作为循环条件
	while ([&]()->bool {cout << "Please enter family name：" << endl; return (cin >> last_name) && (last_name != "end"); }())
	//最右侧小括号保证优先级？？？还是调用运算符
	{
		cout << "Please enter members' names：" << endl<<"Input end to stop.";
		while ([&]()->bool { return (cin >> first_name) && (first_name != "end"); }())
			family[last_name].push_back(first_name);
	}
	for (const auto &f : family)
	{
		cout << "Family of " << f.first << " members are:" << endl;
		for (const auto &m : f.second)
			cout << m << ' ' << f.first << endl;
	}*/
	//11.8
	/*vector<string>words;
	string word;
	while (cin >> word)
	{
		for (auto &w : word)
			word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
		words.push_back(word);
	}
	sort(words.begin(), words.end());
	auto it=unique(words.begin(), words.end());
	words.erase(it, words.end());
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;*/
	//11.12
	/*vector<pair<string, int>> toward;
	vector<string>s_from = {"apple","banana","cherry","date","fig","grape","organge"};
	vector<int>i_from = { 5,6,6,4,3,5,7 };
	pair<string, int> read_pair(const string s, const int i);
	for (int k = 0; k < 6; ++k)
	{
		toward.push_back(read_pair(s_from[k], i_from[k]));
	}
	for (auto &t : toward)
		cout << t.first << ' ' << t.second << endl;
	//11.14
	map < string, vector<pair<string, string>>> child_info;
	string last_name, first_name, birthday;
	cout << "Start entering children's informations,input \"end\" to stop." << endl;
	while ([&]()->bool {cout << "Please enter family name：" << endl; return (cin >> last_name) && (last_name != "end"); }())
		//最右侧小括号保证优先级？？？还是调用运算符
	{
		cout << "Please enter members' names and birthday:"<< endl ;
		while ([&]()->bool { return (cin >> first_name ) && (first_name != "end"); }())
		{ 
			cin >> birthday;
			child_info[last_name].push_back(make_pair(first_name,birthday));
		}	
	}
	for (const auto &info : child_info)
	{
		cout << "Family of " << info.first << " members are:" << endl;
		for (const auto &p : info.second)
			cout << p.first << ' ' << info.first <<' '<<p.second<< endl;
		cout << endl;
	}
	//11.16
	map<string, string> a_map;
    map<string, string>::iterator map_it;
	map_it->first = "Unchangeable" ;
	map_it->second = "Changeable";*/
	//11.17---exp
	/*multimap<int, int>m = { {1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7} };
	vector<int>v = { 1,2,3,4,5,6,7 };
	//copy(v.begin(), v.end(), inserter(m, m.end()));//不合法
	//copy(v.begin(), v.end(), back_inserter(m));;//不合法
	//copy(m.begin(), m.end(), inserter(v, v.end()));;//不合法
	//copy(m.begin(),m.end(), back_inserter(v));;//不合法
	for (auto &vv : v)
		cout << vv << ' ';
	cout << endl;
	for (auto &mm : m)
		cout << mm.first << ' ' << mm.second << endl;
    //11.18
	multimap<int, int> ::iterator map_it = m.begin();
	for (; map_it != m.end(); ++map_it)
		cout << map_it->first <<' '<< map_it->second << endl;
	//11.19
	bool compareIsbn(const sales_data &lhs, const sales_data &rhs);
	multiset<sales_data, decltype(compareIsbn)*>bookstroe1(compareIsbn);
	using cmp = bool(*)(const sales_data &lhs, const sales_data &rhs);
	multiset<sales_data, cmp> bookstore2(compareIsbn);*/
	//11.20
	/*map<string, size_t>word_count;
	string word;
	while (cin >> word)
	{
		auto w = word_count.insert({ word,1 });
		if (!w.second)
			++w.first->second;
	}
	cout << "map of word_count:" << endl;
	for (auto &ww : word_count)
		cout << ww.first << ' ' << ww.second << endl;*/
	//11.23
	/*map<string, vector<int>>ohh;
	ohh.insert({ "abc",{1,2,3} });
	ohh.insert({ "def",{4,5,6} });
	for (auto &oh : ohh)
	{
		cout << oh.first << ' ';
		for (auto &o : oh.second)
			cout << o << ' ';
		cout << endl;
	}
	multimap<string, string>fm;
	string last_name, first_name, oooo;
	while ([&]() {cout << "姓: "; return (cin >> last_name) && (last_name != "end"); }())
	{
		cout << "名: ";
		cin >> first_name; 
		fm.insert({ first_name,last_name });
	}
	for (auto &fms : fm)
		cout << fms.first << ' ' << fms.second << endl;*/
	//11.31&&11.32
	/*multimap<string, string> works = { {"Charlotte Bronte","Jane Eyre"},{ "Charlotte Bronte","Shirley "} ,
	                                                           { "Charlotte Bronte", "Villette"}, { "Charlotte Bronte","The Professor"},
	                                                           {"Alexandre Dumas","The Three Musketeers"},{ "Alexandre Dumas","The Count of Monte Cristo" },
	                                                           { "Alexandre Dumas","Queen Margot" },{ "Alexandre Dumas","The Black Tulip" } };
	//11.31 
	auto it=works.find("Alexandre Dumas");
	cout << "It is to be erased: " << it->first << ' ' << it->second << endl;
	works.erase(it); */
	//11.32
	/*auto beg = works.cbegin(), end = works.cend();//大范围
	auto lower = works.begin(), upper=works.begin();//关键字相同范围内
	void KeyCmp(multimap<string, string>::iterator it1, multimap<string, string>::iterator it2);//声明
	for(;lower!=end;)
	{
		upper=works.upper_bound(lower->first);//获取当前关键字范围
		auto low=lower, upp = upper;//完成循环
		int num=works.count(lower->first);//确定关键字个数
		while(num>1)
		{
			--upp;//范围内，不是尾后
			for (; low !=upper; ++low)
			{
				//利用冒泡法对mapped_value进行排序
				KeyCmp(low,upp);
			}
			--num;//循环总次数为n!
			low = lower;//low归位，以便下一次循环
		}
		lower = upper;//进入下一个关键字
	}
	for (auto &work : works)
		cout << work.first << ' ' << work.second << '\n'<< endl;*/
	//11.31
	void word_transform(ifstream &map_file, ifstream &input);
	map<string, string> buildMap(ifstream &map_file);
	const string& transform(const string &s, const map<string, string> &m);
	ifstream rule("rule.txt"),words("words.txt");
	if (!rule)
		cout << "from.txt cant open!" << endl; 
	if (!words)
		cout << "words.txt cant open!" << endl;
	word_transform(rule,words);
	rule.close();
	words.close();
	//11.38
	unordered_map<string, size_t> w_count;
	string word;
	while ((cin>>word)&&(word!="end"))
	{
		++w_count[word];
	}
	for (auto &w : w_count)
		cout << w.first << ' ' << w.second << '\n';

	system("pause");
    return 0;
}

pair<string,int> read_pair(const string s,const int i )
{
	//10.13——三种创建并返回pair对象的方式
	//return {s,i };//最简便
	//return pair<string, int> (s, i) ;
	return make_pair(s, i);//最好理解
}
 bool compareIsbn(const sales_data &lhs, const sales_data &rhs)
{
	return lhs.ISBN() < rhs.ISBN();
}
 //冒泡排单词
 void KeyCmp(multimap<string, string>::iterator it1, multimap<string, string>::iterator it2)
 {
	 string s1= it1->second, s2 = it2->second;
	 if(s1>s2)
	 {
		 it1->second = s2;
		 it2->second =s1;
	 }
	 return;
 }
//exp
 void word_transform(ifstream &map_file, ifstream &input)
 {
	 map<string, string> buildMap(ifstream &map_file);//声明
	 const string& transform(const string &s, const map<string, string> &m);//声明
	 auto trans_map = buildMap(map_file);//保存转换规则
	 string text;//保存输入中的每一行
	 while (getline(input, text))//读取一行输入
	 {
		 cout << "原文：" << text<<'\n';
		 istringstream stream(text);//读取每个单词
		 string word;
		 bool firstword = true;//是否为该行第一个单词
		 cout << "译文：" ;
		 while (stream >> word)
		 {
			 if (firstword)//控制是否打印空格
				 firstword = false;
			 else
				 cout << ' ';//在单词间打印一个空格
			 //transform返回它的第一个参数或其转换之后的形式
			 cout << transform(word, trans_map);//打印输出
		 }
		 cout << endl;//完成一行的转换
	 }
 }
 map<string, string> buildMap(ifstream &map_file)
 {
	 map<string, string> trans_map;//保存转换规则
	 string key;//要转换单词
	 string value;//替换后的内容
	 //读取第一个单词存入key中，行中剩余内容存入value
	 while (map_file >> key && getline(map_file, value))
	 {
		 if (value.size() > 1)//检查是否有转换规则
			 trans_map[key] = value.substr(1);//跳过前导空格,从下标为1的字符截取到该string结尾
		 else
			 throw runtime_error("no rule for " +key);
	 }
	 return trans_map;
 }
 const string& transform(const string &s, const map<string, string> &m)
 {
	 //实际的转换工作，程序核心
	 auto map_it = m.find(s);
	 if (map_it != m.cend())
		 return map_it->second;//使用替换短语
	 else
		 return s;//否则返回原string
 }