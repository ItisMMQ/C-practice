// Screen.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
using std::string;
using std::vector;

class win_mgr//窗口管理
{
public:
	using screenIndex = vector<screen>::size_type;
	void clear(screenIndex);
private:
	vector<screen> screens{screen(24,8,' ',0) };
};

class screen
{
public:
	//类型声明
	typedef string::size_type pos;
	//构造函数
	screen() :screen(0, 0,' ',0) {}//委托构造的默认构造函数
	screen(int id) :screen(0, 0, ' ', id) {}
	screen(pos ht, pos wd) :screen(ht,wd,' ',0) {}
	screen(const string &s):contents(),ID(' '){}
	screen(pos ht, pos wd, char c,int id) :height(ht), width(wd), contents(ht*wd, c) ,ID(id){}
	//成员函数
	char get() const//获取当前光标所指的字符
	{
		return contents[cursor];
	}
	char get(pos r, pos c) const;
	screen &move(pos r, pos c);//将光标移到指定位置
	void some_member() const;//测试说明const对可变数据成员的作用
	screen &set(char c);//置定当前光标所指位置字符
	screen &set(pos r, pos col, char c);//置定特定位置（某行某列）字符
	screen &display(ostream &os) { do_display(os); return *this; }
	const screen &display(ostream &os)const { do_display(os); return *this; }
	//友元
	friend void win_mgr::clear(screenIndex);//仅将类中的某个成员函数而非整个类作为友元
	pos size() const
	{
		return height * width;
	}
private:
	//数据成员
	pos cursor = 0;//光标
	pos height = 0, width = 0;
	string contents;//内容
	const int ID;//const成员必须由构造函数提供初始值
	//可变数据成员
	mutable size_t access_ctr;
	//成员函数
	void do_display(ostream &os)const{os << contents;}
};

//7.31
class x
{
	int a = 0;
	friend void f() { cout << "It's been definited here"; }//在类内部定义友元，此时只定义未声明，不可使用
};
class y
{
	int b = 0;
	y *next;
	x* relt;
	x u;
};
void f();//在外部声明友元
//友元的声明影响了访问权限，而非普通的函数声明
//7.43
struct Nodefault
{

};
struct C
{
	Nodefault c;
	C(Nodefault t) :c(t) {}
};
//************************************main**************************************************//
int main()
{
	screen myscreen(5, 5, 'x',0);
	myscreen.move(4, 0).set('y').display(cout);
	cout << "\n";
	myscreen.display(cout);
	cout << "\n";
	screen item1("an experinence");
	system("pause");
    return 0;
}
//**************************************func************************************************//

char screen::get(pos r, pos c) const//获取某行某列处的内容
{
	pos row = r * width;
	return contents[row + c];
}

inline screen & screen::move(pos r, pos c)//移动光标到某行某列
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

void screen::some_member() const
{
	++access_ctr;//const限定不了可变数据成员
}

screen &screen::set(char c)//为当前光标处内容赋值
{
	contents[cursor] = c;
	return *this;
}

screen & screen::set(pos r, pos col, char c)//为某行某列内容赋值
{
	contents[r*width + col] = c;
	return *this;
}
//友元成员函数必须在该类之前被声明，否则友元将无法调用该类私有成员
//必须将友元所属类定义在先，用extern声明也不行
void win_mgr::clear(screenIndex i)
{
	screen &s = screens[i];
	//将选定的那个screen置为空白
	s.contents = string(s.height*s.width, ' ');
}