#pragma once
#include "stdafx.h"
#include "Sales_data.hpp"
#include <unordered_set>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

//16.62
/*namespace std
{
	template<>
	struct hash<sales_data>
	{
		typedef size_t result_type;
		typedef sales_data argument_type;
		size_t operator() (const sales_data& s) const;
	};
	size_t
		hash<sales_data>::operator() (const sales_data& s) const
	{
		//使用一个未命名的hash<unsigned>对象来生成bookNo的哈希值，下同...
		return hash<std::string>() (s.bookNo) ^  
			hash<unsigned>()(s.units_sold) ^
			hash<double>()(s.revenue);
	}
}*/

//16.63
template <typename T>
int cnt(std::vector<T>& v, const T t)
{
	int c = 0;
	for (T& temp : v)
	{
		if (temp == t)//string类型也有==运算符且大小写敏感
			++c;
	}
	return c;
}
//16.64
template<>
int cnt(std::vector<const char*>& v, const char* t)
{
	int c = 0;
	for (auto& temp : v)
		if (strcmp(temp, t)==0)
			++c;
	return c;
}