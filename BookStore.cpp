#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "BookStore.h"

using namespace std;
using std::vector;
using std::string;

double print_total(std::ostream &os, const Quote &item, std::size_t n);

Quote & Quote::operator=(const Quote &Q)
{
	this->bookNo = Q.bookNo;
	this->price = Q.price;
	cout << "Q拷贝构造运算符" << endl;
	return *this;
}

void Quote::debug() const
{
	cout << "ISBN: " << isbn() << " Price: " << price << endl;
	return;
}

Bulk_quote & Bulk_quote::operator=(const Bulk_quote&Bq)
{
	Quote::operator=(Bq);//为基类部分赋值
	Bq.min_qty;
	this->discount = Bq.discount;
	cout << "Bq拷贝运算符" << endl;
	return *this;
}

double Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= min_qty)
		return cnt * (1 - discount)*price;
	else
		return cnt * price;
}

void Bulk_quote::debug() const
{
	cout << "ISBN: " << isbn() << " Price: " << price << " Min_qty: " << min_qty << " Discount: " << discount << endl;
	return;
}

double B_quote::net_price(size_t cnt) const
{
	if (cnt >= quantity)
		return cnt * (1 - discount)*price;
	else
		return cnt * price;
}

double new_quote::net_price(size_t cnt) const
{
	if (cnt <= max_qty)
		return cnt * (1 - discount)*price;
	else
		return (max_qty*(1 - discount) + (cnt - max_qty))*price;
}
//15.16
double max_quote::net_price(size_t count) const
{
	if (count <= quantity)
		return count * (1 - discount)*price;
	else
		return (quantity*(1 - discount) + (count - quantity))*price;
}

double Basket::total_receipt(std::ostream &os) const
{
	double sum = 0.0;
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
	{
		sum += print_total(os, **iter, items.count(*iter));
	}
	os << "Total Sale: " << sum << endl;
	return sum;
}

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " #  sold: " << n << " total due: " << ret << std::endl;
	return ret;
}