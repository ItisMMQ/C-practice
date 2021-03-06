// Sales_data.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
//#include <cstring>  Cout不明确专用
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
	sales_data(const string &s):sales_data(s,0,0){ }
	//成员函数-----都是inline的
	string ISBN() const { return bookNo; }
	sales_data& combine(const sales_data&);
	void print();
private:
	double avg_price() const;//将const放在参数列表之后，表示参数是const类型
	// 成员
	string bookNo;//ISBN书号
	unsigned units_sold=0;//单次销售量，类内初始化
	double u_price;//单价
	double revenue=0.0;//单次交易收入
	//***以下内容有待补充***
	/*double sellingprice;
	double salesprice;
	double discount=10;
	union
	{
		char isdatum;
		char istotal;
	}category;*/
};

//7.53
//字面值常量类
/*class Debug
{
public:
	//构造函数
	constexpr Debug(bool b = true) :hw(b), io(b), other(b) {}
	constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
	//成员函数
	constexpr bool any() { return hw || io || other; }
	void set_hw(bool b) { hw = b; }
	void set_io(bool b) { io = b; }
	void set_other(bool b) { other = b; }
private:
	bool hw;
	bool io;
	bool other;
};*/
//********************main***函***数*****************************//
int main(int argc,char *argv[])
{
	//7.41
	//sales_data a("123");
	//sales_data b;//在没有参数的情况下会调用默认构造函数
	//sales_data c();//这是定义了一个返回类型为sales_data类的函数
	//7.13
	sales_data total;
	/*if(read(cin,total))
	{
		sales_data trans;
		while (read(cin, trans))//不强制停止会一直继续
		{
			if (total.ISBN() == trans.ISBN())
				total.combine(trans);
			else
			{
				total.print() ;//调用成员函数打印输出
				total = trans;
			}
			print(cout, total);//调用外部函数打印输出
		}
	}	
	else cerr << "No data?";
	/*vector<sales_data> data;
	sales_data tdata,total;
	string se;//Start Entering
	cout << "Shall we start? ";
	cin >> se;
	if (se == "y" || se == "Y") cout << "ISBN:\tunit price:\tunit sold:" << endl;
	while (se =="y"||se =="Y")
	{
		cin >> tdata.bookNo>>tdata.u_price>>tdata.units_sold;
		tdata.revenue = tdata.u_price*tdata.units_sold;
		data.push_back(tdata);
		cout << "Press y/Y to continue:" << endl;
		cin >> se;
	}*/
	//7.11
	/*sales_data data1, data2, data3,data4;
	data1.sales_data::sales_data(); data1.print();
	data2.sales_data::sales_data("123"); data2.print();
	data3.sales_data::sales_data("123", 10, 6); data3.print();
	data4.sales_data::sales_data(cin); data4.print();*/
	/*string currNo , tempNo;//记录和对比当前值和下一值
	if (!data.empty())//当有数据时,初始化
	{
		currNo = data[0].bookNo;
		total = data[0];//初始化记录总计
		if (data.size() ==1) total.print();
	}
	for(decltype(data.size()) index=1;index<data.size();++index)
	{
		tempNo = data[index].bookNo;
		if (currNo == tempNo)
		{
			total.combine(data[index]);
		}
		else
		{
			total.print();
			//更新
			total = data[index];
			currNo = tempNo;
		}
		if (index+1 == data.size())
		{
			total.print();
		}
	}*/
	//P245
	/*screen myscreen;
	char ch = myscreen.get();
	ch = myscreen.get(0, 0);*/
	//8.6 -------和7.13类似
	//由于此处的print是写入到文件，不会输出，判断是否成功的标准是去2.txt看看有没有内容
	//先在工作路径下创建两个文件1.txt和2.txt，并根据read函数格式在1.txt中写入一些数据
	//在调试->Sales_data属性->命令行参数中写“1.txt 2.txt ”
	if(argc>2)//确保参数数量大于2
	{
		ifstream input(argv[1]);//7.13由键盘输入，此处为由文件输入
		ofstream output(argv[2],ofstream::app);//7.13输出到设备，此处写入到文件
		//argv[1]和argv[2]分别为main函数的第一个和第二个参数
		if(input)
		{		
			if (read(input, total))
			{
				sales_data trans;			
				while (read(input, trans))//调用外部read函数			
				{			
					if (total.ISBN() == trans.ISBN())
					{
						total.combine(trans);
					}
					else				
					{			
						cout << "here2" << endl;
						print(output, total) << endl;//调用外部print函数					
						total = trans;				
					}			
				}			
				print(output, total) << endl;	
			}
			cout << "运行成功" << endl;
		}
		else cout << "Can't open file " << argv[1] << endl;
	}
	else cerr << "No data?!" << endl;
	system("pause");
    return 0;
}
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
	is >> datum.bookNo >> datum.units_sold >> price;
	datum.revenue = price * datum.units_sold;
	return is;
}
ostream &print(ostream &os, const sales_data &datum)//对象输出
{
	os << "ISBN:" << datum.ISBN() << " units sold: " << datum.units_sold
		<< " total revenue: " << datum.revenue << " average price: " << datum.avg_price();
	return os;
}
sales_data add(const sales_data &lhs, const sales_data &rhs)//实际用途不详
{
	sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
