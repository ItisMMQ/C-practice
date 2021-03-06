// GA.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include  <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include "Sales_item.h"

using namespace std;
using namespace std::placeholders;
using std::string;
using std::vector;
using std::list;

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
		<< " total revenue: " << datum.revenue << " average price: " << datum.avg_price()<<endl;
	return os;
}
sales_data add(const sales_data &lhs, const sales_data &rhs)//实际用途不详
{
	sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
//******************************main函数**************************************
int main()
{
	//10.1
	/*int a1[10] = { 0,1,2,5,4,5,4,5,4,5 };
	vector<int> vec(a1, a1 + 10);
	int val1 = 5;
	cout << val1 << "出现的次数为：" << count(vec.begin(), vec.end(), val1) << endl;
	//10.2
	string s[6] = {"ready", "abc","abc"," hello","abc","abc" };
	string val = "abc";
	list<string>sl(s,s+6);
	cout<<val<<" occurred "<<count(sl.begin(),sl.end(),val)<<" times"<< endl;
	string a2[10] = { "morning","morning","123","123","evening","123","123","123","morning","123" };
	list<string> list1(a2, a2+ 10);
	string value = "123";
	cout << value << " occurred " << count(list1.begin(), list1.end(), value) << " times" << endl;*/
	//10.3
	/*vector<int> num;
	int n;
	while (cin >> n)
		num.push_back(n);
	int sum=accumulate(num.cbegin(), num.cend(), 0);
	cout << "Sum of num: " << sum << endl;*/
	//10.5
	/*const char *roster1[]= { "Mary","Bob","Linda" ,"Jane","Tim","Habe"};
	const char *roster2[] = { "Mary","Bob","Linda" ,"Jane","Tim","Habe","Cindy","Mindy","Zak","Hock" };
	bool isequ = equal(roster1, roster1+6, roster2);
	cout << "roster1 is " << ( isequ == 1 ? "equal to " : "not equal to " ) << "roster2";*/
	//10.6
	/*fill_n(num.begin(),num.size() , 0);
	for (auto &n : num)
		cout << n << ' ';
	cout << endl;*/
	//10.9
	/*
	string word;
	vector<string> words = { "Apink","lovelyz","Twice", "BLACKPINK","AOA","BLACKPINK","Red Velvet","Apink","Red Velvet","Red Velvet","Twice",
		                                          "BLACKPINK","lovelyz","Red Velvet","lovelyz","Twice"};
	//void elimDups(vector<string> &words);
	//elimDups(words);*/
	//10.11
	/*bool isShorter(const string &s1, const string &s2);
	stable_sort(words.begin(), words.end(), isShorter);
	for (const auto &w : words)
		cout << w << ' ';
	cout << endl;*/
	//10.12
	/*
	vector<sales_data> data;
	//data.push_back(datum1);
	//data.push_back(datum2);
	//bool compareISBN(const sales_data datum1, const sales_data datum2);
	//stable_sort(data.begin(), data.end(), compareISBN);
	//for (auto &sd : data)
		//print(cout,sd);//*/
	//10.13
    //	bool length(string &str);
	//vector<string> strs= { "handsome","ugly","beautiful","dumb","echo","hello","windows","ability","kid","cute" };
	/*vector<string>::iterator it= strs.begin();
	it = partition(strs.begin(), strs.end(), length);
	for (;it!=strs.end() ; ++it)
	{
		cout << *it << " ";
	}*/
	//10.14
	/*int a, b;
	cout << "Enter a and b:";
	cin >> a >> b;
	auto sum = [](int a,int b) {return a + b; };
	cout << a << " + " << b << " = " << sum(a,b)<<endl;
	//10.15
	auto s=[a](int b) {return a + b; };
	cout << a << " + " << 5 << " = " << s(5) << endl;
	//10.16
	void biggies(vector<string> &strs, vector<string>::size_type sz);
	biggies(strs, 5);*/
	//10.17
	/*data.resize(5);
	for (int i = 0; i < 5; ++i)
		read(cin, data[i]);
	stable_sort(data.begin(), data.end(), [](sales_data d1, sales_data d2) {return d1.ISBN() < d2.ISBN(); });
	for (auto &s : data)
		print(cout,s);
	//10.18
	void biggies(vector<string> &strs, vector<string>::size_type sz, ostream &os = cout, char c = ' ');
	biggies(strs, 5,cout,' ');*/
	//10.20
	/*auto c=count_if(words.begin(), words.end(), [](string s) {return s.length() > 6; });
	cout << "There are " << c << " words longer than 6"<<endl;
	//10.21
	int k=10;
	auto b = [&k]() mutable->bool {for (; k > 0; --k) { cout << "Continue decreasing... " <<k<< endl; }  return 1; };
	if (b()) cout << "k decreased to " << k << endl;*/
	//10.22
	/*bool len_exd(string &str, string::size_type len);
	auto newc=count_if(words.begin(), words.end(), bind(len_exd, _1, 6));
	cout << "There are " << newc << " words longer than 6" << endl;
	//10.24
	string s = "Forever young";
	int len = s.length();//13
	vector<int> find_len = { 7,10,5,8,13,21,16,9,4};
	bool len_less(string &str, string::size_type len);
	auto s_l = find_if(find_len.begin(),find_len.end(),bind(len_less,s, _1));
	cout << "第一个大于长度的值为  " <<* s_l  << endl;
	//10.25
	bool check_size(const string &s, string::size_type sz);
	void biggies(vector<string> &strs, vector<string>::size_type sz);
	biggies(words, 6);*/
	//10.27
	/*list <int>l_desk;
	vector<int>source = { 1,1,2,3,4,5,1,6,7,8,9};
	unique_copy(source.cbegin(), source.cend(), inserter(l_desk,l_desk.begin()));//unique_copy可以去重拷贝（删除相邻重复元素）
	unique_copy(source.cbegin(), source.cend(), front_inserter(l_desk));
	for (auto &i :l_desk)
		cout << i << ' ';
	cout << '\n';
	//10.28
	vector<int> v_desk;
	copy(source.cbegin(), source.cend(), back_inserter(v_desk));
	for (auto &i : v_desk)
		cout << i << ' ';
	cout <<endl;//下面例子使用流迭代器，刷新流会不会好一点？
	//exp
	cout << "输入流使用累加算法" << endl;
	istream_iterator<int>in(cin), eof;
	cout << accumulate(in, eof, 0) << endl;//此处需刷新流，用'\n'出错
	ostream_iterator<int >out_iter(cout, " ");
	for (auto e : source)
		*out_iter++ = e;//可以改成out_iter = e;因为*和++存在但不执行
	//但推荐使用*++形式，操作清晰，也便于与其他迭代器形式一致，易于后期修改为其他迭代器
	cout << endl;
	cout << "使用copy快速打印" << endl; 
	copy(l_desk.cbegin(), l_desk.cend(), out_iter);
	cout << endl;*/
	//exp of bookstore
	/*istream_iterator<Sales_item> item_iter(cin), eof;
	ostream_iterator<Sales_item> out_iter(cout, "\n");
	Sales_item sum = *item_iter++;
	while (item_iter!=eof)
	{
		if(item_iter->isbn() == sum.isbn())
			sum += *item_iter++;
		else
		{
			out_iter = sum;
			sum = *item_iter++;
		}
	}
	out_iter = sum;*/
	//10.29
	/*istream_iterator <string> it1(cin), eof1;
	vector <string> strs;
	cout << "Enter strs:" << endl;
	while (it1!= eof1)
		strs.push_back(*it1++);
	for (auto &s : strs)
		cout << s << ' ';
	cout << endl;//刷新输出流*/
	//10.30
	/*vector<int> ints;
	cout << "Enter ints: " << endl;
	istream_iterator<int>it2(cin), eof2;
	ostream_iterator<int>it3(cout, " ");
	while (it2 != eof2)
		ints.push_back(*it2++);
	sort(ints.begin(), ints.end());
	copy(ints.cbegin(), ints.cend(), it3);
	//10.31
	cout << '\n';
	unique_copy(ints.cbegin(), ints.cend(), it3);*/
	//10.32
	/*vector<Sales_item> items;
	cout << "Enter sale imformation: " << endl;//如果在流迭代器之后则无法正常输出
	istream_iterator<Sales_item> it4(cin), it5;
	ostream_iterator<Sales_item> it6(cout,"\n");
	while (it4 != it5)
		items.push_back(*it4++);
	bool compareISBN(const Sales_item datum1, const Sales_item datum2);
	sort(items.begin(), items.end(), compareISBN);
	//for_each(items.cbegin(), items.cend(), [](const Sales_item &s) {cout << s << '\n'; });
	auto beg = items.begin(), end = items.end(),itis=items.begin();
	while (beg != end) 
	{
		itis= find_if(beg, end ,[beg](Sales_item &s) {return s.isbn() !=beg->isbn(); });
		cout << accumulate(beg, itis, Sales_item(beg->isbn())) << endl;
		beg = itis;
	}*/
	//10.33
	/*ifstream in("from.txt");//输入文件
	if (!in)
	{
		cout << "Can't open from.txt!" << endl;
		in.close();
		system("pause");
		exit(1);
	}
	else
		cout << "from.txt opened." << endl;
	istream_iterator<int>read_int(in), end_read;//定义输入流迭代器，和输入流的尾迭代器
	vector<int> buf;//存储用vector
	ofstream out1("out1.txt",ofstream::out), out2("out2.txt", ofstream::out);
	//void r_and_w(ifstream in, ofstream out1, ofstream out2);
	ostream_iterator<int> write1(out1, " "),write2(out2,"\n");
	copy(read_int,end_read,back_inserter(buf));//将流中数据存入buf
	for (int i = 0; i<buf.size(); ++i)
	{
		if( buf[i] % 2 != 0)//偶数
		{
			*write1++ = buf[i];//奇数放在out1.txt中
		}
		else
		{
			*write2++ = buf[i];//偶数放在out2.txt中
		}
	}
	in.close();
	out1.close();
	out2.close();*/
	//exp
	/*vector<int> v = { 1,3,5,7,9,2,4,6,8,10 };
	for (auto r_iter = v.crbegin(); r_iter != v.crend(); ++r_iter)
		cout << *r_iter << ' ';
	cout << endl;
	sort(v.begin(), v.end());//正常序
	for (auto &vv : v)
		cout << vv <<' ';
	cout << endl;
	sort(v.rbegin(), v.rend());//逆序
	for (auto &vv : v)
		cout << vv << ' ';
	cout << endl;
	string line = "add,am, access,arch,ace,angle,any";
	auto rcomma = find(line.crbegin(), line.crend(),',');
	cout << string(rcomma.base(), line.cend()) << endl;*/
	//10.34
	/*vector<string> v_s = { "ok","opps","orient","oppose","often","omit", };
	vector<string>::reverse_iterator r_itb = v_s.rbegin(),r_ite=v_s.rend();//不能用crbegin和crend,会出错，还是auto方便
	for (; r_itb != r_ite; ++r_itb)
	{
		cout << *r_itb<<' ';
	}
	cout << endl;
	//10.35
	auto itb = v_s.begin(), ite = v_s.end();
	for (; ite !=itb ; --ite)
		cout << *(ite-1) << ' ';
	cout << endl;
	//10.36
	list<int> intlst = { 1,6,0,47,8,6,1,0,4,9,7,21,0,6,47,86,1,2,3,4,0,48,3,2,1,647,8 };
	auto rt = find(intlst.rbegin(), intlst.rend(), 0);
	cout  << *rt<< endl;//list不支持随机访问，只能++或--，不能+1或-1
	//10.37
	vector<int>from = { 1,2,3,4,5,6,7,8,9,10 };
	list<int>to;
	auto i1 = from.cbegin()+2, i2 = from.cbegin()+7;
	copy(i1, i2, front_inserter(to));
	for (auto &t : to)
		cout << t << ' ';
	cout << endl;*/
	//10.41--exam
	vector<int>hhh = { 1,4,3,8,1,9,9,4,4,6 };
	vector<int>ohh = { 0,0,0,0,0,0,0,0 ,0,0,0,0};
	replace_copy_if(hhh.begin(), hhh.end(), ohh.begin(), [](int i) {return i % 2 == 0; }, 2);
	for (auto &oh : ohh)
		cout << oh << ' ';
	cout << endl;
	//10.42
	void elimDups(list<string> &words);
	list<string>to_unisort = {"the","quick","red","fox","jumps","over","the","slow","red","turtle"};
	elimDups(to_unisort);
	system("pause");
    return 0;
}
//********************************functions*****************************//
//按字典序排序并删除重复单词
void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());//按字典序
	/*cout << "sorted words: ";
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;*/
	auto end_unique = unique(words.begin(), words.end());//查重
	/*cout << "uniqued words: ";
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;*/
	words.erase(end_unique, words.end());//去重
	/*cout << "After erase: ";
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;*/
}
//10.42--list重载版
void elimDups(list<string>&words)
{
	cout << "Original:" ;
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;
	words.sort();
	cout << "Sorted:  " ;
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;
	words.unique();
	cout << "Uniqued: ";
	for (auto &w : words)
		cout << w << ' ';
	cout << endl;
}

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

bool compareISBN(const sales_data datum1,const sales_data datum2)
{
	return datum1.ISBN() < datum2.ISBN();
}
//10.32重载
bool compareISBN(const Sales_item datum1, const Sales_item datum2)
{
	return datum1.isbn() < datum2.isbn();
}

bool len_exd(string &str,string::size_type len)
{
	return str.size() > len;
}

bool len_less(string &str, string::size_type len)
{
	return str.size() < len;
}
//10.16
/*void biggies(vector<string> &strs, vector<string>::size_type sz)
{
	elimDups(strs);//字典排序、删除重复
	stable_sort(strs.begin(), strs.end(), [](const string &a, const string &b) {return a.length() < b.length(); });//按长度排序，保留之前字典序
	auto wc = find_if(strs.begin(), strs.end(), [sz](const string &a) {return a.size() > sz; });//找到第一个长度>sz元素的迭代器
	auto count = strs.end() - wc;//有count个符合查找标准的元素...auto出count是ptrdiff_t类型，即有符号整型
	cout << count << " " << " of length " << sz << " or longer" << endl;
	for_each(wc, strs.end(), [](const string &s) {cout << s << " "; });
	cout << endl;
}*/
//10.18
/*void biggies(vector<string> &strs, vector<string>::size_type sz, ostream &os = cout, char c = ' ')
{
	elimDups(strs);//字典排序、删除重复
	stable_sort(strs.begin(), strs.end(), [](const string &a, const string &b) {return a.size() < b.size(); });//按长度排序，保留之前字典序
	auto it = partition(strs.begin(), strs.end(), [sz](const string &s) {return s.size() <= sz; });
	cout << "These words' length over " << sz << " characters: " << "\n";
	for (; it != s.end(); ++it)
	{
		cout << *it <<"\n";
	}
}*/
//10.19
/*void biggies(vector<string> &strs, vector<string>::size_type sz)
{
	elimDups(strs);//字典排序、删除重复
	stable_sort(strs.begin(), strs.end(), [](const string &a, const string &b) {return a.size()<b.size(); });//按长度排序，保留之前字典序
	auto it = stable_partition(strs.begin(), strs.end(), [sz](const string &s) {return s.size() <= sz; });//加stable,维持原顺序
	cout << "These words' length over " << sz << " characters: " << "\n";
	for (; it != s.end(); ++it)
	{
		cout << *it <<"\n";
	}
}*/

//10.25
void biggies(vector<string> &s, vector<string>::size_type sz)
{
	elimDups(s);//字典排序、删除重复
	stable_sort(s.begin(), s.end(), [](const string &a, const string &b) {return a.size()<b.size(); });//按长度排序 ，保留之前字典序
	auto it = partition(s.begin(), s.end(), bind(len_less, _1, sz)/*[sz](const string &s){return s.size()<=sz;}*/);
	cout << "These words' length over " << sz << " characters: " << "\n";
	for (; it != s.end(); ++it)
	{
		cout << *it <<"\n";
	}
}
