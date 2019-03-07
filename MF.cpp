#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include "MF.h"

using namespace std;
using std::string;
using std::vector;
using std::set;

Message& Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}
void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::move_Folders(Message *m)
{
	folders = std::move(m->folders);//使用set的移动赋值运算符
	for (auto f : folders)//对每个Folder
	{
		f->remMsg(m);//从Folder中删除旧版本的Message
		f->addMsg(this);//将本Message添加到Folder中
	}
	m->folders.clear();//确保销毁m是无害的
}
void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}
void Message::add_to_Folders(const Message&m)
{
	for (auto f:m.folders)
		f->addMsg(this);
}
//拷贝构造函数
Message::Message(const Message&m) :contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}
void Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(this);
}
Message&  Message::operator=(Message && m)
{
	if (this != &m)
	{
		remove_from_Folders();
		contents = std::move(m.contents);
		move_Folders(&m);
	}
	return *this;
}
Message::~Message()
{
	remove_from_Folders();
}
void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

Folder & Folder::operator=(const Folder &f)
{
	for (auto &m : this->msgs)
		m->folders.erase(this);
	for (auto &m : f.msgs)
		m->folders.insert(this);
	for (auto &m : f.msgs)
		this->msgs.insert(m);
	return *this;
}
void Folder::addMsg(Message *m)
{
	msgs.insert(m);
}
void Folder::remMsg(Message *m)
{
	msgs.erase(m);
}