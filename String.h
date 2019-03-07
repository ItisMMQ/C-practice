#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>

class String
{
public:
	String() :beg(nullptr), ed(nullptr),fin(nullptr) { std::cout << "default constructor" << std::endl; };
	String(const char*);
	String(const String&);
	String(String &&s) noexcept
		:beg(s.beg), ed(s.ed), fin(s.fin)
	{
		s.beg = s.ed = s.fin = nullptr;
		std::cout << "Executed." <<std:: endl;//13.50
	};
	~String();
	String &operator=(const String &);
	String &operator=(String &&) noexcept;
	void push_back(const char&);
	size_t size()const { return ed - beg; }
	size_t capacity() const { return fin - beg; }
	char *begin() const { return beg; }
	char *end()  const { return ed; }
private:
	static std::allocator<char> alloc;
	void chk_n_alloc();
	void reallocate();
	std::pair<char *, char *>alloc_n_copy(const char *,const char*);
	void free();
	char *beg;
	char *ed;
	char *fin;
};
