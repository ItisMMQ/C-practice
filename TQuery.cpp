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
	LineNo lineNo{ 0 };//�ۺϳ�ʼ��
					   //���ж�ȡ��vector��
	for (std::string line; std::getline(fs, line); ++lineNo)
	{
		input->push_back(line);
		std::istringstream line_stream(line);
		for (std::string text, word; line_stream >> text; word.clear())
		{
			//������ɾ����ĵ��ʴ洢��word��
			remove_copy_if(text.begin(), text.end(), std::back_inserter(word), ispunct);
			// ʹ�������Է�ֹshared_ptr�����ü�������
			auto& nos = result[word];//���ش����кŵ�setָ��
			if (!nos) //����ǿ�ָ��
				nos.reset(new std::set<LineNo>);//newһ��ָ�����
			nos->insert(lineNo);//���赱ǰ�к�
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
		out << "\t(line" << j + 1 << ")" << endl;//û��ԭ�ļ�¼��ֻ���к�
	return out;
}

void runQueries(ifstream &infile)
{
	//infileָ������Ҫ������ļ�
	TextQuery tq(infile);//�����ļ���������ѯmap
	while (true)
	{
		cout << "Enter word to look for,or q to quit: ";
		string s;
		//�������ļ�β���û�������'q'ʱѭ����ֹ
		if (!(cin >> s) && s == "q") break;
		//ָ���ѯ����ӡ���
		auto qr = tq.query(s);
		print(cout, qr) << endl;
	}
}

Query::Query(const std::string & s) :q(new WordQuery(s)) { cout << "Query" << endl; }

//eval����
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
	//infileָ������Ҫ������ļ�
	TextQuery tq(infile);//�����ļ���������ѯmap
	while (true)
	{
		cout << "Enter word to look for,or q to quit: ";
		std::string s;
		//�������ļ�β���û�������'q'ʱѭ����ֹ
		if (!(cin >> s) || s == "q") break;
		//ָ���ѯ����ӡ���
		auto qr = tq.query(s);
		auto newdata = make_pair(qr.word, qr.nos);
		h.histories.push_back(newdata);
		print(cout, qr) << endl;
	}
}
