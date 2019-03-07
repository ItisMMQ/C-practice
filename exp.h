#pragma once
#include "stdafx.h"
#include <iostream>
#include <initializer_list>
#include <memory>
#include <vector>
#include <string>
#include <new>
#include <initializer_list>

//18.7   
/*template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) try:
	data(std::make_shared<std::vector<T>>(il)) {
}
catch (const std::bad_alloc &e) { std::cerr << e.what() <<std::endl; }

template<typename T> 
class Blob
{
public:
	typedef  T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//Blob();
	Blob(std::initializer_list<T> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(T &&t) { data->push_back(t); }
	//void pop_back();
	//T& back();
	//T& operator[] (size_type i);
private:
	std::shared_ptr<std::vector<T>> data;
	//void check(size_type i, const std::string &msg) const;
};

//P694
class out_of_stock : public std::runtime_error
{
public:
	explicit out_of_stock(const std::string & s) :std::runtime_error(s){}
};
class isbn_mismatch :public std::logic_error
{
public:
	explicit isbn_mismatch(const std::string &s):std::logic_error(s){}
	isbn_mismatch(const std::string &s,const std::string &l,const std::string &r):
		std::logic_error(s),left(l),right(r){}
	const std::string left, right;
};
class sales_data
{
public:
	std::string isbn;
	double revenue;
	int units_sold;
	sales_data&operator+=(const sales_data &);
};
*/
/*
//18.26
struct Base1
{
	void print(int)const { ; }//不可用
protected:;
	int ival;
	double dval;
	char cval;
private:
	int *id;
};

struct Base2
{
	void print(double)const { ; }//不可用
protected:
	double fval;
private:
	double dval;
};

struct Derived :public Base1
{
	void print(std::string) const { ; }//不可用
protected:
	std::string sval;
	double dval;
};

struct MI :public Derived, public Base2
{
	void print(std::vector<double>) { ; }//不可用
	void foo(double cval);
protected:
	int* ival;
	std::vector<double>dvec;
};
//text
class T1
{
public:
	int a = 0;
};
class T2 :public T1
{
public:
	int a = 1;
	int b = 2;
 };
//18.28
struct Base
{
	void bar(int);
protected:
	int ival;
};
struct Derived1 :virtual public Base
{
	void bar(char);
	void foo(char);
protected:
	char cval;
};
struct Derived2 :virtual public Base
{
	void foo(int);
protected:
	int ival;
	char cval;
};
class VMI:public Derived1,public Derived2{};
*/
//18.30
class Class{};

class Basic:public Class
{
public:
	Basic() = default;
	Basic(const Basic& b) { *this = b; };
	Basic(int i):a(i){}
	Basic& operator=(const Basic&);
protected:
	int a = 0;
};

class D1 :virtual public Basic
{
public:
	D1():Basic(){}
	D1(const D1& d1) = default;
	D1(int i):Basic(i){}
};

class D2 :virtual public Basic
{
public:
	D2():Basic(){}
	D2(const D2& d2) = default;
	D2(int i):Basic(i){}
};

class MI :public D1, public D2
{
public:
	MI():D1(),D2(){}
	MI(const MI& mi) = default;
	MI(int i):D1(i),D2(i){}
};

class Final :public MI, public Class
{
public:
	Final():MI(),Class(){}
	Final(const Final& f) = default;
	Final(int i) :MI(i),Class(){}
};