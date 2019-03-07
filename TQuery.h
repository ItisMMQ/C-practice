#ifndef TQ
#define TQ

#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <utility>

class QueryResult;

class History
{
	friend void runQueries(std::ifstream &infile);
public:
	History() = default;
	std::vector <std::pair< std::string, std::shared_ptr<std::set<std::size_t>>>>histories;
};

class TextQuery 
{
public:
	using LineNo = std::vector<std::string>::size_type;//�к�
	std::string textname = "Unknown ";
	//���캯��
	TextQuery(std::ifstream&fs);
	//��Ա����
	QueryResult query(const std::string&) const;
private:
	std::vector<std::string> text;//���б����ļ�����
	std::shared_ptr<std::vector<std::string>> input;//���ļ����ݸ��Ƶ���̬�ڴ�
	std::map<std::string, std::shared_ptr<std::set<LineNo>>> result;//���浥�ʳ��ֵ��к�
};

std::ostream& print(std::ostream&, const QueryResult&);//��ǰ����

class QueryResult 
{
	friend class History;
	friend std::ostream& print(std::ostream&, const QueryResult&);
	friend void QueryHistory(std::ifstream& infile, History& h);
public:
	//���캯��
	QueryResult(const std::string& s, std::shared_ptr<std::set<TextQuery::LineNo>> set,
		std::shared_ptr<std::vector<std::string>> v) : word(s), nos(set), input(v) {std::cout << "QueryResult" << std::endl;}
	std::string::iterator begin() { return word.begin(); }
	std::string::iterator end() { return word.end(); }
	std::shared_ptr<std::vector<std::string>> get_file() { return input; }
private:
	std::string word;
	std::shared_ptr<std::set<TextQuery::LineNo>> nos;
	std::shared_ptr<std::vector<std::string>> input;
};
//Volume15
class Query_Base
{
	friend class Query;
protected:
	using Line_No = TextQuery::LineNo;//����eval����
	virtual ~Query_Base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;//�����뵱ǰQueryƥ���QueryResult
	virtual std::string rep() const = 0;                                   //rep��ʾ��ѯ��һ��string
};

class Query
{
	friend Query operator~(const Query&);                           //����notQuery
	friend Query operator|(const Query&, const Query&); //����orQuery
	friend Query operator&(const Query&, const Query&); //����andQuery
public:                               
	Query(const std::string &s);//����wordQuery
	QueryResult eval(const TextQuery &t)const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_Base>query) :q(query){}//���캯��
	std::shared_ptr<Query_Base> q;
};

class WordQuery:public Query_Base
{
	friend class Query;
	WordQuery(const std::string& s) :query_word(s) { std::cout << "WordQuery" << std::endl; }
	QueryResult eval(const TextQuery &t) const {return t.query(query_word);}
	std::string rep() const {return query_word;}
	std::string query_word;
};

class NotQuery :public Query_Base
{
	friend Query operator~(const Query&);
	NotQuery(const Query& q) :query(q) { std::cout << "NotQuery" << std::endl; }
	std::string rep() const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const;
	Query query;
};

class BinaryQuery :public Query_Base
{
protected:
	BinaryQuery(const Query& l,const Query &r,std::string s)
		:lhs(l), rhs(r), opSym(s) {std::cout << "BinaryQuery" << std::endl;}
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	std::string opSym;
};

class AndQuery :public BinaryQuery
{
	friend Query operator& (const Query&, const Query&);
	AndQuery(const Query& left,const Query& right)
		:BinaryQuery(left, right, "&") {std::cout << "AndQuery" << std::endl;}
	QueryResult eval(const TextQuery&) const;
};

class OrQuery :public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& left,const Query& right)
		:BinaryQuery(left,right,"|"){std::cout << "OrQuery" << std::endl;}
	QueryResult eval(const TextQuery&) const;
};

#endif  //TQ