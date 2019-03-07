#include "stdafx.h"
#include <memory>
#include <iostream>
#include "String.h"

using namespace std;

allocator<char>String:: alloc;

String::String(const char *c)
{
	int i = 0;
	while (*(c + i) != '\0')
		i++;
	i += 1;//ÔªËØ¸öÊý
	alloc_n_copy(c, c + i);
	//beg= newstring.first;
	//ed= newstring.second;
}

String::String(const String &s)
{
	auto newstring = alloc_n_copy(s.begin(), s.end());
	beg = newstring.first;
	ed = fin = newstring.second;
}

String::~String()
{
	free();
}

String & String::operator=(const String &s)
{
	auto string = alloc_n_copy(s.begin(), s.end());
	free();
	beg = string.first;
	ed = fin = string.second;
	cout << "operator= " << endl;
	return *this;
}

String & String::operator=(String &&s) noexcept
{
	if (this != &s)
	{
		free();
		beg = s.beg;
		ed = s.ed;
		fin = s.fin;
		s.beg = s.ed = s.fin = nullptr;
	}
	return *this;
}

void String::push_back(const char&c)
{
	chk_n_alloc();
	alloc.construct(ed++, c);
}

void String::chk_n_alloc()
{
	if (size() == capacity()) reallocate();
}

void String::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newstring = alloc.allocate(newcapacity);
	auto dest = newstring;
	auto bb = beg;
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*bb));
	free();
	beg = newstring;
	ed = dest;
	fin = beg + newcapacity;
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e)
{
	auto data = alloc.allocate(e - b);
	return{ data,uninitialized_copy(b,e,data) };

}

void String::free()
{
	if (beg)
		for (auto p = ed; p != beg;)
			alloc.destroy(--p);
	alloc.deallocate(beg, fin - beg);
}
