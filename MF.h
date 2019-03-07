#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>

class Folder;
class Message
{
	friend class Folder;
	friend void swap(Message &lhs, Message &rhs);
public:
	explicit Message(const std::string &str=""):contents(str){}//folders被隐式初始化为空集合
	Message(const Message&);                         //拷贝构造函数
	
	Message& operator=(const Message&);    //拷贝赋值运算符
	Message(Message &&m)                             //移动构造函数
		:contents(std::move(m.contents))
	{
		move_Folders(&m);//移动folders并更新Folder指针
	}
	Message& operator=(Message &&);       //移动赋值运算符
	~Message();                                                  //析构函数
	void save(Folder&f);
	void move_Folders(Message *);
	void remove(Folder&f);
private:
	std::string contents;
	std::set<Folder*> folders;
	//工具函数
	//将本Message添加到指向参数的Folder中
	void add_to_Folders(const Message&);
	//从folders中的每个Folder中删除本Message
	void remove_from_Folders();
};


class Folder
{
	friend class Message;
	friend void swap(Message &lhs, Message &rhs);
public:
public:
	Folder() = default;
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();
private:
	std::set<Message *> msgs;
	void  addMsg(Message*);
	void remMsg(Message*);
};
