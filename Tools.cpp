// Tools.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "exp.h"

using namespace std;

int main()
{
	//18.5
	//try {/**/}
    //标准库异常类型只定义了一个名为what的成员函数，
    //该函数没有任何参数，返回值是一个指向C风格字符串的const char*。
	/*catch (overflow_error e)
	{
		cout << e.what();
		
		abort();
	}
	catch (underflow_error u)
	{
		cout << u.what();
		abort();
	}
	catch (range_error r)
	{
		cout << r.what();
		abort();
	}
	catch (domain_error d)
	{
		cout << d.what();
		abort();
	}
	catch (invalid_argument i)
	{
		cout << i.what();
		abort();
	}
	catch (out_of_range o)
	{
		cout << o.what();
		abort();
	}
	catch (length_error l)
	{
		cout << l.what();
		abort();
	}
	catch (runtime_error r)
	{
		cout << r.what();
		abort();
	}
	catch (logic_error l)
	{
		cout << l.what();
		abort();
	}
	catch (bad_alloc b)
	{
		cout << b.what();
		abort();
	}
	catch (bad_alloc b)
	{
		cout << b.what();
		abort();
	}
	catch (exception e)
	{
		cout << e.what();
		abort();
	}
	//P695
	sales_data item1, item2, sum;
	while (cin >> item1 >> item2)
	{
		try 
		{
			sum = item1 + item2;
		}
		catch (const isbn_mismatch& e)
		{
			cerr << e.what() << " : left isbn( " << e.left << ") right isbn(" << e.right << ")" << endl;
		}
	}*/
	//18.17
	/*void manip();
	manip();
	vector<int> vi = { 1,2,3,4 };
	string str = "It can work.";
	cout << str;
	//text
	T2 t2;
	auto t=t2.T1::a;//基类中的同名成员被继承，需要用限定符读取
	cout << t2.a << endl;//覆盖基类同名成员，且不会出现二义性
	cout << t << endl;*/
	;

	system("pause");
    return 0;
}
/********************************************************/
//18.3
//组合使用智能指针和lambda
void exercise1(int *b, int *e)
{
	vector<int> v(b, e);
	//智能指征不能管理动态数组，需使用lambda自定义删除器
	shared_ptr<int> p (new int[v.size()], [](int *p) {delete[] p; });
	ifstream in("ints");
	return ;
}

class intPtr
{
	int *p = 0;
public:
	intPtr(size_t n) :p(new int[n]) {}
	~intPtr() { delete []p; }
};

void exercise2(int *b, int *e)
{
	vector<int> v(b, e);
	//构造int *类，并定义析构函数
	intPtr p(v.size());
	ifstream in("ints");
	return;
}

//18.17
namespace Exercise
{
	int ivar = 0;
	double dvar = 0; 
	const int limit = 1000;
}
int ivar = 20;
//using namespace Exercise;

void manip()
{
	//using namespace Exercise;
	using Exercise::ivar;
	using Exercise::dvar;
	using Exercise::limit;
	//double dvar = 3.1415;
	int iobj = limit + 1;
	++ivar;
	++::ivar;
	cout << "dvar: " << dvar << " iobj: " << iobj << " ivar: " << ivar << " ::ivar " << ::ivar << endl;
}