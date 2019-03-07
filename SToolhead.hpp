#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <new>
#include <cstdlib>

using namespace std;

//19.3
/*
class A
{
public:
	A() { std::cout << "A();" <<std::endl; }
	virtual ~A() { std::cout << "~A();" << std::endl; }
};

class B:public A
{
public:
	B() { std::cout << "B();" << std::endl; }
	virtual ~B() { std::cout << "~B();" << std::endl; }
};

class C:public B
{
public:
	C() { std::cout << "C();" << std::endl; }
	virtual ~C() { std::cout << "~C();" << std::endl; }
};
/*
class D :public B,public A
{
public:
	D() { std::cout << "D();" << std::endl; }
	virtual ~D() { std::cout << "~D();" << std::endl; }
};
    */    
//P734
/*
class Base
{
	friend bool operator==(const Base&, const Base&);
public:
	//Base的接口成员
protected:
	virtual bool equal(const Base&)const;
};

class Derived :public Base
{
public:
	//Derived的其他接口成员
protected:
	bool equal(const Base&) const;
};

bool operator==(const Base& l, const Base& r)
{
	//如果typeid不同则返回false，否则虚调用equal
	return typeid(l) == typeid(r) && l.equal(r);
}

bool Base::equal(const Base& r) const
{
	//执行比较Base对象的操作
	return 0;
}
bool Derived::equal(const Base& r) const
{
	auto rr=dynamic_cast<const Derived&>(r);
	return 0;
}

//P739
class Screen
{
public:
	static const std::string Screen::*data() { return &Screen::contents; }
	static const std::string::size_type Screen::*cs() { return &Screen::cursor; }
	typedef std::string::size_type pos;
	using Action = Screen & (Screen::*)();
	//19.17
	using Action2= char(Screen::*)();
	using Action3 = char(Screen::*)(pos, pos);
	enum Directions{HOME,FORWARD,BACK,UP,DWON};
	Screen& move(Directions);
	char get_cursor() const { return contents[cursor]; }
	char get() const;
	char get(pos ht, pos wd) const;
	//移动光标函数
	Screen& home();
	Screen& forword();
	Screen& back();
	Screen& up();
	Screen& down();
private:
	static Action Menu[];//函数表
   	std::string contents;
	pos cursor;
	pos height, width;
};
/*
Screen& Screen::move(Directions cm)
{
	return (this->*Menu[cm])();
}

Screen::Action Screen::Menu[] ={ &Screen::home,
														 &Screen::forword,
														 &Screen::back,
														 &Screen::up,
														 &Screen::down
                                                      };
*/
//Nested Class
/*
class QueryResult;
class TextQuery
{
public:
	class QueryResult;
	using line_no =vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<std::vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;
};

class TextQuery::QueryResult
{
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s,
		                 shared_ptr<set<line_no>> p,
		                 shared_ptr<vector<string>> f):
		sought(s),lines(p),file(f){}
private:
	string sought;
	shared_ptr<set<line_no>>lines;
	shared_ptr<vector<string>>file;
	static int static_mem;
};
//嵌套类的静态成员应定义于外部类的作用域之外
int TextQuery::QueryResult::static_mem = 1024;

//以下为类成员外部定义

TextQuery::TextQuery(ifstream &is) :file(new vector<string>)
{
	string text;
	while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

TextQuery::QueryResult
TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata (new set<line_no>);
	auto loc = wm.find(sought);//TextQuery::std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

ostream& print(ostream& os, const TextQuery::QueryResult& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " << "time(s)" << endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
	return os;
}

//查询函数主体
void runQueries(ifstream& infile)
{
	TextQuery tq(infile);
	while (1)
	{
		cout << "Enter word ro look for, or press 'q' to quit: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}
}
*/
//Union
/*class Token
{
public:
	Token():tok(INT),ival{0}{}
	Token(const Token& t) :tok(t.tok) { copyUnion(t); }
	Token& operator=(const Token&);
	~Token() { if (tok == STR)  sval.~string(); }
	Token& operator=(const string&);
	Token& operator=(char);
	Token& operator=(int);
	Token& operator=(double);
private:
	enum{INT,CHAR,DBL,STR}tok;//判别式
	union
	{
		char cval;
		int ival;
		double dval;
		string sval;
	};
	void copyUnion(const Token&);
};

Token& Token::operator=(int i)
{
	if (tok == STR)
		sval.~string();
	ival = i;
	tok = INT;
	return *this;
}

Token& Token::operator=(const std::string& s)
{
	if (tok == STR)
		sval = s;
	else
		new(&sval) string(s);//定位new表达式，P729
	tok = STR;
	return *this;
}

void Token::copyUnion(const Token& t)
{
	switch (t.tok)
	{
		//完成拷贝构造
		case Token::INT: ival = t.ival; break;
		case Token::CHAR:cval = t.cval; break;
		case Token::DBL:dval = t.dval; break;
		case Token::STR: new(&sval) string(t.sval); break;
	}
}

Token& Token::operator=(const Token& t)
{
	if (tok == STR && t.tok != STR) sval.~string();
	if (tok == STR && t.tok == STR)
		sval = t.sval;
	else
		copyUnion(t);
	tok = t.tok;//更新判别式
	return *this;
}*/
//Bid-Field
/*typedef unsigned int Bit;
class File
{
	Bit mode : 2;
	Bit modified : 1;
	Bit prot_owner : 3;
	Bit prot_group : 3;
	Bit prot_world : 3;
public:
	enum modes { READ = 01, WRITE = 02, EXECUTE = 03 };
	File& open(modes);
	void close();
	void write();
	bool isRead() const;
	void setWrite();
};

inline bool File::isRead() const { return mode & READ; }
inline void File::setWrite() { mode |= WRITE; return; }*/
//volatile
/*class Foo
{
public:
	Foo(const volatile Foo&);
	Foo& operator=(volatile const Foo&);
	Foo& operator=(volatile const Foo&) volatile;
};*/
