// OPP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "BookStore.h"

using namespace std;
using std::vector;
using std::string;

int main()
{
	double print_total(std::ostream &os, const Quote &item, std::size_t n);
	//15.6
	Quote q1("A123", 12.5);
	Bulk_quote b1("B256",17,5,0.2);
	/*print_total(cout, q1, 3);
	print_total(cout, b1, 7);
	//15.11
	q1.debug();
	b1.debug();
	//15.26
	Bulk_quote b2("B256", 17, 5, 0.2), b3 = b2, b4;
	b4 = b2;
	//15.28
	vector<shared_ptr<Quote>> basket;
	basket.push_back(make_shared<Quote>(q1));
	basket.push_back(make_shared<Bulk_quote>(b1));
	cout << basket[0]->net_price (10)<< ' ' << basket[1]->net_price(10);*/
	//15.30
	Basket BT;
	BT.add_item(q1);
	BT.add_item(b1);
	BT.total_receipt(cout);
	system("pause");
    return 0;
}