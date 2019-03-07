#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iterator>
#include <utility>
#include "TQuery.h"

using namespace std;
using std::vector;
using std::string;

TextQuery::TextQuery(std::ifstream& fs) : input(new std::vector<std::string>)
{
	LineNo lineNo{ 0 };//聚合初始化
					   //按行读取到vector中
	for (std::string line; std::getline(fs, line); ++lineNo)
	{
		input->push_back(line);
		std::istringstream line_stream(line);
		for (std::string text, word; line_stream >> text; word.clear())
		{
			//将符号删除后的单词存储到word中
			remove_copy_if(text.begin(), text.end(), std::back_inserter(word), ispunct);
			// 使用引用以防止shared_ptr的引用计数增加
			auto& nos = result[word];//返回储存行号的set指针
			if (!nos) //如果是空指针
				nos.reset(new std::set<LineNo>);//new一个指针给它
			nos->insert(lineNo);//赋予当前行号
		}
	}
}

QueryResult TextQuery::query(const std::string& str) const
{
	// use static just allocate once.
	static std::shared_ptr<std::set<LineNo>> data(new std::set<LineNo>);
	auto found = result.find(str);
	if (found == result.end())
		return QueryResult(str, data, input);
	else
		return QueryResult(str, found->second, input);
}

std::ostream& print(std::ostream& out, const QueryResult& qr)
{
	out << qr.word << " occurs " << qr.nos->size()
		<< (qr.nos->size() > 1 ? " times" : " time") << std::endl;
	for (auto i : *qr.nos)
		out << "\t(line " << i + 1 << ") " << qr.input->at(i) << std::endl;
	return out;
}

ostream& HistoryPrint(ostream& out, const History&h,int i)
{
	out << h.histories[i].first << " occurs " << h.histories[i].second->size()
		<< (h.histories[i].second->size() > 1 ? "times" : "time") << '\n';
	for (auto j : *h.histories[i].second)
		out << "\t(line" << j + 1 << ")" << endl;//没有原文记录。只有行号
	return out;
}

void runQueries(ifstream &infile)
{
	//infile指向我们要处理的文件
	TextQuery tq(infile);//保存文件并建立查询map
	while (true)
	{
		cout << "Enter word to look for,or q to quit: ";
		string s;
		//若遇到文件尾或用户输入了'q'时循环终止
		if (!(cin >> s) && s == "q") break;
		//指向查询并打印结果
		auto qr = tq.query(s);
		print(cout, qr) << endl;
	}
}

Query::Query(const std::string & s) :q(new WordQuery(s)) { cout << "Query" << endl; }

//eval函数
QueryResult NotQuery::eval(const TextQuery &text) const
{
	auto result = query.eval(text);
	auto ret_lines = make_shared<set<Line_No>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
auto left = lhs.eval(text), right = rhs.eval(text);
auto ret_lines = make_shared<set<Line_No>>();
set_intersection(left.begin(), left.end(), right.begin(), right.end(),inserter(*ret_lines,ret_lines->begin()));
return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text)const
{
auto left = lhs.eval(text), right = rhs.eval(text);
auto ret_lines = make_shared<set<Line_No>>(left.begin(), left.end());
ret_lines->insert(right.begin(), right.end());
return QueryResult(rep(), ret_lines, left.get_file());
}

void QueryHistory(ifstream& infile, History& h)
{
	//infile指向我们要处理的文件
	TextQuery tq(infile);//保存文件并建立查询map
	while (true)
	{
		cout << "Enter word to look for,or q to quit: ";
		std::string s;
		//若遇到文件尾或用户输入了'q'时循环终止
		if (!(cin >> s) || s == "q") break;
		//指向查询并打印结果
		auto qr = tq.query(s);
		auto newdata = make_pair(qr.word, qr.nos);
		h.histories.push_back(newdata);
		print(cout, qr) << endl;
	}
}
