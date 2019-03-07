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
	explicit Message(const std::string &str=""):contents(str){}//folders����ʽ��ʼ��Ϊ�ռ���
	Message(const Message&);                         //�������캯��
	
	Message& operator=(const Message&);    //������ֵ�����
	Message(Message &&m)                             //�ƶ����캯��
		:contents(std::move(m.contents))
	{
		move_Folders(&m);//�ƶ�folders������Folderָ��
	}
	Message& operator=(Message &&);       //�ƶ���ֵ�����
	~Message();                                                  //��������
	void save(Folder&f);
	void move_Folders(Message *);
	void remove(Folder&f);
private:
	std::string contents;
	std::set<Folder*> folders;
	//���ߺ���
	//����Message��ӵ�ָ�������Folder��
	void add_to_Folders(const Message&);
	//��folders�е�ÿ��Folder��ɾ����Message
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
