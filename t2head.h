#pragma once
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <utility>

template<typename F,typename T1,typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
	f(std::forward <T2>(t2),std::forward <T1>(t1));
}

//P615����ģ�庯��
template <typename T> std::string debug_rep(const T &t)
{
   ostringstream ret;
	ret << t;
	return ret.str();
}
//�˷������ʺϣ�const��char*����������
template <typename T> std::string debug_rep(T *p)
{
    ostringstream ret;
	ret << "pointer: " << p;
	if (p)
	{
		ret << " " << debug_rep(*p); cout << '\t'<<"here" << '\n';
	}
	else
	{
		ret << " null pointer"; cout << '\t' << "here" << '\n';
	}
	return ret.str();
}
//��ģ�庯��
std::string debug_rep(const std::string &s)
{
	return '"' + s + '"';
}
//16.65����ģ��������
template<>
std::string debug_rep(const char* p)
{
	return std::string(p);
}
template<>
std::string debug_rep(char* p)
{
	return std::string(p);
}
//16.50
template<typename T> void f(T t)
{
	std::cout << "f:T t��" << t <<std::endl;
}

template<typename T> void g(T *t)
{
	std::cout << "g:T *t��" << t << std::endl;
}

template<typename T> void g(T t)
{
	std::cout << "g:T t��" << t << std::endl;
}

template<typename T> void f(const T *t)
{
	std::cout << "f:const T*��" << t << std::endl;
}

//16.51
template<typename T,typename...Args>
void foo(const T &t, const Args&...rest)
{
	std::cout <<"Args: "<< sizeof...(Args) << std::endl;
	std::cout << "rest: "<<sizeof...(rest) << std::endl;
}

//16.53
template <typename T>
std::ostream  &print(std::ostream &os, const T &t)
{
	return os << t;//�������һ��Ԫ��֮�󲻴�ӡ�ָ���
}

template <typename T,typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args&... rest)
{
	os << t << ", ";
	return print(os, rest...);//�ݹ���ã���ӡ��������
}

//16.56
template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args&... rest)
{
	return print(os, debug_rep(rest)...);
}