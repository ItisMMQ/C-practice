#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <initializer_list>

class StrVec
{
public:
	template<class... Args> void emplace_back(Args&&...);
	//构造函数
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec&);//拷贝构造函数
	StrVec(StrVec &&s) noexcept//移动构造函数
		:elements(s.elements), first_free(s.first_free), cap(s.cap)
	{
		//令s进入这样的状态——对其运行析构函数是安全的
		s.elements = s.first_free = s.cap = nullptr;
	}
	/*StrVec(initializer_list<string>)
	{
	//其实就是拷贝构造
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
	}*/
	StrVec&operator=(const StrVec&);//赋值运算符
	StrVec&operator=(StrVec &&) noexcept;//移动赋值运算符
	~StrVec();//析构函数
			  //接口
	void push_back(const std::string&);//拷贝版
	void push_back(std::string &&);//移动版
	size_t size() const { return first_free - elements; }
	//int resize(size_t );//自定义
	//int resize(size_t ,std::string);//自定义
	size_t capacity() const { return cap - elements; }
	//void reserve(size_t);//自定义
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }
private:
	//静态数据成员
	static std::allocator<std::string> alloc;//分配元素
											 //成员函数
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }//保证至少有容纳一个新元素的空间
	std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);//分配内存，并拷贝一个给定范围中的元素
	void free();//销毁元素并释放内存
	void reallocate();//空间用完时分配新空间
					  //void reallocate(size_t sz);//用于扩容到指定大小
					  //数据成员
	std::string *elements;//首元素
	std::string *first_free;//尾后指针
	std::string *cap;//指向最后可用空间
};

//16.58
template<class ...Args>
inline 
void StrVec::emplace_back(Args && ...)//将Args扩展
{
	chk_n_alloc();
	alloc.construct(first_free++, std::forward<Args>(args)...);//forword函数使参数类型得到保持 
	//实参即扩展Args有扩展args
}
