#include "stdafx.h"
#include "VecHead.h"
#include <iostream>
#include <string>
#include <memory>
#include <initializer_list>
#include <utility>


using namespace std;
using std::string;
//��̬��Ա�ⲿ����
std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(const StrVec &s)
{
	//����alloc_n_copy����ռ�һ������s��һ�����Ԫ��
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec & StrVec::operator=(const StrVec &sv)
{
	//����alloc_n_copy�����ڴ棬��С��sv��Ԫ��ռ�ÿռ�һ����
	auto data = alloc_n_copy(sv.begin(), sv.end());
	free();//��ԭ��������
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec & StrVec::operator=(StrVec &&s) noexcept
{
	if (this != &s)//��ַ
	{
		free();//�ͷ�����Ԫ��
		elements = s.elements;//�ӹ���Դ
		first_free = s.first_free;
		cap = s.cap;
		s.elements = s.first_free = s.cap = nullptr;//��s���ڿ�����״̬
	}
	return *this;
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();//ȷ���пռ�������Ԫ��
				  //��first_freeָ���Ԫ���й���s�ĸ���
	alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
	chk_n_alloc();//�����Ҫ�Ļ�ΪStrVec���·���ռ�
	alloc.construct(first_free++, std::move(s));
}

/*int StrVec::resize(size_t sz)//�Զ���
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
/*int StrVec::resize(size_t sz, string s)//�Զ���
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
	//����ռ䱣�������Χ�е�Ԫ��
	//δ��֤b��e�ĺϷ��ԣ����Ǽ��������
	auto data = alloc.allocate(e - b);
	//��ʼ��������һ��pair,��pair�д�����uninitialized_copy �ķ���ֵ����
	return { data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
	//���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0������ʲôҲ����
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
	alloc.construct(dest++, std::move(*elem++));//ʹ���ƶ����캯�����ڴ潫��������*/
	auto elem = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), dest);//�ƶ���������
	free();
	elements = dest;
	first_free = elem;
	cap = elements + newcapacity;
}
/*void StrVec::reallocate(size_t sz)//�Զ���
{
auto newcapacity = sz;
auto newdata = alloc.allocate(newcapacity);
auto dest = newdata;
auto elem = elements;
for (size_t i = 0; i != size(); ++i)
alloc.construct(dest++, std::move(*elem++));//ʹ���ƶ����캯�����ڴ潫��������
free();
elements = newdata;
first_free = dest;
cap = elements + newcapacity;
}*/

