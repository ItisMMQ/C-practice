#include "stdafx.h"
#include "VecHead.h"
#include <iostream>
#include <string>
#include <memory>
#include <initializer_list>
#include <utility>


using namespace std;
using std::string;
//静态成员外部声明
std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(const StrVec &s)
{
	//调用alloc_n_copy分配空间一容纳与s中一样多的元素
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec & StrVec::operator=(const StrVec &sv)
{
	//调用alloc_n_copy分配内存，大小与sv中元素占用空间一样多
	auto data = alloc_n_copy(sv.begin(), sv.end());
	free();//将原内容销毁
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec & StrVec::operator=(StrVec &&s) noexcept
{
	if (this != &s)//地址
	{
		free();//释放已有元素
		elements = s.elements;//接管资源
		first_free = s.first_free;
		cap = s.cap;
		s.elements = s.first_free = s.cap = nullptr;//将s置于可析构状态
	}
	return *this;
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();//确保有空间容纳新元素
				  //在first_free指向的元素中构造s的副本
	alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
	chk_n_alloc();//如果需要的话为StrVec重新分配空间
	alloc.construct(first_free++, std::move(s));
}

/*int StrVec::resize(size_t sz)//自定义
{
auto orgcap = capacity();
auto orgsize = size();
if (sz = orgcap)
return 0;
if (sz > orgcap)
{
StrVec::reallocate(sz);
return 0;
}
else
{
//first_free = elements + sz;
auto new_cap= elements + sz;
if (sz >orgsize)
{
alloc.deallocate(cap - sz, cap - new_cap);
cap = new_cap;
return 0;
}
if (sz < orgsize)
{
alloc.deallocate(first_free, cap-new_cap);
if (new_cap)
{
for (auto p = first_free; p != new_cap;)
alloc.destroy(--p);
alloc.deallocate(new_cap, first_free-new_cap);
first_free = cap = new_cap;
}
return 0;
}
}
return -1;
}
*/
/*int StrVec::resize(size_t sz, string s)//自定义
{
auto orgcap = capacity();
auto orgsize = size();
if (sz = orgcap)
return 0;
if (sz > orgcap)
{
StrVec::reallocate(sz);
for ( ;first_free!= cap;)
alloc.construct(first_free++, s);
return 0;
}
else
{
resize(sz);
return 0;
}
return -1;
}
*/
/*void StrVec::reserve(size_t sz)
{
if (sz <= capacity())
return;
else
{
reallocate(sz);
return;
}
}*/

std::pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
	//分配空间保存给定范围中的元素
	//未验证b和e的合法性，考虑加入迭代器
	auto data = alloc.allocate(e - b);
	//初始化并返回一个pair,该pair有打他和uninitialized_copy 的返回值构成
	return { data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
	//不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
	if (elements)
	{
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto dest = alloc.allocate(newcapacity);
	/*auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
	alloc.construct(dest++, std::move(*elem++));//使用移动构造函数，内存将不被拷贝*/
	auto elem = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), dest);//移动迭代器版
	free();
	elements = dest;
	first_free = elem;
	cap = elements + newcapacity;
}
/*void StrVec::reallocate(size_t sz)//自定义
{
auto newcapacity = sz;
auto newdata = alloc.allocate(newcapacity);
auto dest = newdata;
auto elem = elements;
for (size_t i = 0; i != size(); ++i)
alloc.construct(dest++, std::move(*elem++));//使用移动构造函数，内存将不被拷贝
free();
elements = newdata;
first_free = dest;
cap = elements + newcapacity;
}*/

