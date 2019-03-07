#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <initializer_list>
#include <utility>

/*template<typename T>
int compare(const T &v1, const T &v2)
{
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}

template<unsigned N,unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M])
{
	return strcmp(p1, p2);
}

//16.4
template<typename T,typename U> std::size_t myfind(const T& b,const T& e,const U&val)
{
	auto it = b;//参数是const，不能更改
	int index = 0;
	for (; it != e; ++index, ++it)
	{
		if (*it == val) break;//中断循环，return当前下标
	}
	return index;//若没有该元素，则返回尾后下标
}

//16.5
template<typename T> 
void print(const T& arr)
{
	for (auto elem : arr)
		std::cout << elem << endl;//没有加std好像也没关系
}

//16.6
template<typename T,unsigned N>
T* begin(const T(&arr)[N])
{
	return arr;
} 
template<typename T,unsigned N>
T* end(const T(&arr)[N])
{
	return arr+N;
}*/
//16.7
/*template<typename T,unsigned N>
constexpr std::size_t (const T(&arr)[N])
{
	return N;
}
template<typename> class BlobPtr;
template<typename>class Blob;
template<typename T>bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//构造函数
	Blob();
	Blob(std::initializer_list<T> il);
	template<typename It> Blob(It b, It e)
		:data(std::make_shared<std::vector>(b, e)) {}
	//Blob中的元素数目
	size_type size() const {return data->size(); }//实例化的时候就可以用了
	bool empty() const { return data->empty(); }
	//添加与删除元素
	void push_back(const T& t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(std::move(t)); }//移动版本
	void pop_back();
	//元素访问
	T& front();
	T& back();
	T& operator[](size_type i);//详见P501
private:
	std::shared_ptr<std::vector<T>> data;//std::shared_ptr<std::vector<std::string>> data;
	//若data[i]无效，则抛出msg
	void check(size_type i, const std::string &msg) const;
};

template<typename T>
inline Blob<T>::Blob():data(std::make_shared<std::vector<T>>()){}

template<typename T>
inline Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)){}

template<typename T>
inline void Blob<T>::pop_back()
{
	check(0, "pop_back on empty Blob");
	data->pop_back();
}

template<typename T>
inline T & Blob<T>::front()
{
	return data->front();
}

template<typename T>
inline T& Blob<T>::back()
{
	check(0, "back on empty Blob");
	return data->back();
}

template<typename T>
inline T & Blob<T>::operator[](size_type i)
{
	check(i, "subscript out of range");
	return (*data)[i];
}

template<typename T>
inline void Blob<T>::check(size_type i, const std::string & msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

template<typename T> class BlobPtr
{
public:
	BlobPtr():curr{}
	BlobPtr(Blob<T> &a,size_t sz=0)
		:wptr(a.data),curr(sz){}
	T& operator* () const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	BlobPtr& operator++();
	BlobPtr& operator--();
private:
	std::shared_ptr<std::vector<T>>
		check(std::size_t, const std::string&)const;
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};

template<typename T>
inline BlobPtr<T> & BlobPtr<T>::operator++()
{
	BlobPtr ret = *this;
	++*this;
	return ret;
}*/
/*
//类模板与友元
template <typename T> class Pal;//前置声明，在将模板的一个特定是声明成友元是要用
class C
{
	friend class Pal<C>;//用类C实例化的Pal是C的一个友元
	//Pal2的所有实例都是C的友元；这种情况无需前置声明；
	template<typename T> friend class Pal2;
};
template<typename T> class C2
{
	friend class Pal<T>;
};

//16.14
template <unsigned N,unsigned M>
class Screen
{
public:
	typedef std::string::size_type pos;
	Screen() = default;
	Screen(char c):contents(N*M,c){}
	Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht*wd,c)P{}
	char get() const {return contents[cursor];}
	inline char get(pos ht, pos wd)const;
	Screen& move(pos r, pos c);
	Screen& display(std::ostream& os) { do_display(os); return *this; }
	const Screen& display(std::ostream& os)const { do_display(os); return *this; }
private:
	void do_display(std::ostream& os) const { os << contents; }
	pos cursor = 0;//光标
	pos height = M;
	pos width = N;
	std::string contents;
};

template<unsigned N, unsigned M>
inline char Screen<N, M>::get(pos ht, pos wd) const
{
	pos row = r * width;
	return contents[row + c];
}

template<unsigned N, unsigned M>
inline Screen<N, M>& Screen<N, M>::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

template<typename T>
void  OK(T& t)
{
	//16.19
	//for (std::size_t i = 0; i < t.size(); ++i)
		//std::cout << t[i] << '\t';
	//16.20
	T::iterator it = t.begin();
	for (; it != t.end(); ++it)
	{
		std::cout << *it << '\t';
	}
}*/

//成员模板
class DebugDelete
{
public:
	DebugDelete(std::ostream &s=std::cerr):os(s){}
	template<typename T>void operator()(T *p)const//不是墨绿色可能是因为它不是对类内数据成员操作的运算符
	{
		os << "deleting unique_ptr" << std::endl;
		delete p;
	}
private:
	std::ostream &os;
}; 

//16.28
namespace myptr{
template <typename T> class shared_ptr
{
public:
	//不允许隐式类型变换
	explicit shared_ptr(T *q = 0) :p(q) { pn = new unsigned(1); }
	explicit shared_ptr(T a) :{
		p = new T(a);
		pn = new unsigned(1);
	}
	explicit shared_ptr( ) :{
		p = 0;
		pn = new unsigned(1);
	}
	~shared_ptr(){
		if(--*pn==0){
			delete p;
			delete pn;
		}
	}
	shared_ptr(shared_ptr const &ptr):p(ptr.p),pn(ptr.pn)//所有的引用都是底层const
	{
		++*pn;
	}
	shared_ptr operator=(shared_ptr const &ptr)
	{
		if (this != &ptr)
		{
			this->p = ptr.p;
			this->pn = ptr.pn;
			++*pn;
		}
		return *this;
	}
private:
	T *p;
	unsigned *pn;//会被共享，一个加上所有指向它的都会变
};
}
//????????????
template<typename T>  myptr::shared_ptr<T> make_shared(T a) { return myptr::shared_ptr(a); }
template<typename T>  myptr::shared_ptr<T> make_shared( ) { return myptr::shared_ptr( ); }//
//16.29
//不会，16.28中未实现shared_ptr中的make_shared

//16.41
template <typename T> sum(const T& a, const T& b)->decltype(a + b)
{
	return a + b;
}