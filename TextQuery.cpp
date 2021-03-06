// TextQuery.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include "TQuery.h"

using namespace std;
using std::vector;
using std::string;

int main()
{
	void QueryHistory(ifstream& infile, History& h);
	ifstream file("find_s.txt");
	//runQueries(file);
	//Query p("abc");
	cout << "Query q = Query(you)&Query(me) " << endl;
	Query q = Query("you")&Query("me") ;//由于BinaryQuery内eval函数没有完善，所以无法构造对象
	//Query q = Query("you") | Query("me");
	History h;
	QueryHistory(file, h);
	cout << "History: " << h.histories[1].first << " record: " << '\n' <<  ' ' << endl;
	file.close();
	system("pause");
	return 0;
}
//运算符
std::ostream& operator<<(std::ostream &os, const Query &query)
{
	return os << query.rep();
}
inline
Query operator~(const Query& operand)
{
	return std::shared_ptr<Query_Base>(new NotQuery(operand));
}
inline
Query operator&(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_Base>(new AndQuery(lhs, rhs));
}
inline
Query operator|(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_Base>(new OrQuery(lhs, rhs));
}