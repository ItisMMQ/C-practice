#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <set>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) :
		bookNo(book), price(sales_price){}
	Quote(const Quote&Q)
		:bookNo(Q.bookNo), price(Q.price) 
	{
		std::cout << "Quote拷贝构造" << std::endl;
	}
	Quote& operator=(const Quote&);
	std::string isbn() const {return bookNo;};
	//返回给定数量的书籍的销售总额
	//派生类负责改写并使用不同的折扣计算方法
	virtual double net_price(std::size_t n) const {return n * price;}
	virtual void debug()const;//15.11
	virtual Quote* clone()const & { return new Quote(*this); }
	virtual Quote* clone() && {return new Quote(std::move(*this)); }
	virtual ~Quote() = default;  //对析构函数进行动态绑定
private:
	std::string bookNo;            //书籍的ISBN号
protected:
	double price = 0.0;             //代表普通状态下不打折的价格
};

class Bulk_quote :public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&book, double p, std::size_t qty, double disc) 
	    :Quote(book,p),min_qty(qty),discount(disc){}
	Bulk_quote(const Bulk_quote&Bq):
		Quote(Bq),min_qty(Bq.min_qty),discount(Bq.discount)
	{
		std::cout << "B_q拷贝构造" << std::endl;
	}
	Bulk_quote& operator=(const Bulk_quote&);
	//覆盖基类的函数版本以实现基于大量购买的折扣政策
	double net_price(std::size_t) const override;
	void debug() const override;
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	Bulk_quote* clone() && {return new Bulk_quote(std::move(*this)); }
private:
	std::size_t min_qty = 0;//享受折扣最低购买数量
	double discount = 0.0;  //折扣
}; 

class Disc_quote :public Quote//抽象基类，不能定义该类型对象
{
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book,double price,std::size_t qty,double disc)
		:Quote(book,price),quantity(qty),discount(disc){}
	double net_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

//重新实现Bulk-Quote
class B_quote :public Disc_quote
{
public:
	B_quote() = default;
	B_quote(const std::string &book,double price,std::size_t qty,double disc):
		Disc_quote(book,price,qty,disc){}
	double net_price(std::size_t) const override;
};

//15.7
class new_quote :public Quote
{
public:
	new_quote() = default;
	new_quote(const std::string &book, double p, std::size_t qty,double disc)
		:Quote(book,p),max_qty(qty),discount(disc){}
	double net_price(std::size_t) const override;
private :
	std::size_t max_qty = 0;
	double discount = 0.0;
};

//15.16
class max_quote :public Disc_quote
{
public:
	max_quote() = default;
	max_quote(const std::string &book, double price, std::size_t qty, double disc)
		:Disc_quote(book, price, qty, disc){}
	double net_price(std::size_t)const override;
};

//15.18&15.19测试
/*class Base
{
public:
	void pub_men();
protected:
	int prot_men;
private:
	char priv_men;
};

struct Pub_Derv:public Base
{
	int f() { return prot_men; }
	//char g() { return priv_men; }
	void menfcn(Base &b) { b = *this; }
};

struct Priv_Derv:private Base
{
	int f1() const { return prot_men; }
	void menfcn(Base &b) { b = *this; }
};
struct Prot_Derv:protected Base
{
	void menfcn(Base &b) { b = *this; }
};
struct Derived_from_Public :public Pub_Derv
{
	int use_base() { return prot_men; }
	void menfcn(Base &b) { b = *this; }
};
struct Derived_from_Private :public Priv_Derv
{
	//int use_base() { return prot_men; }
	void menfcn(Base &b) { b = *this; }
};
struct Derived_from_Protected:public Prot_Derv
{
	void menfcn(Base &b) { b = *this; }
};
Pub_Derv d1; Priv_Derv d2; Prot_Derv d3;
Derived_from_Public dd1;
Derived_from_Private dd2;
Derived_from_Protected dd3;
Base *p1= &d1;
Base *p2= &d2;
Base *p3 = &d3;
Base*p11 = &dd1;
Base *p22 = &dd2;
Base *p33 = &dd3;
*/

class Basket
{
public:
	void add_item(const Quote& sale)
	    { items.insert(std::shared_ptr<Quote>(sale.clone())); }
	void add_item(Quote&& sale)
	    {items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));}
	double total_receipt(std::ostream&)const;
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs)
	    {return lhs->isbn() < rhs->isbn();}
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*>items{ compare };//{compare}初始化items并令其使用compare函数
};
