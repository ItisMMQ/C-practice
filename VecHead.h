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
	//���캯��
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec&);//�������캯��
	StrVec(StrVec &&s) noexcept//�ƶ����캯��
		:elements(s.elements), first_free(s.first_free), cap(s.cap)
	{
		//��s����������״̬���������������������ǰ�ȫ��
		s.elements = s.first_free = s.cap = nullptr;
	}
	/*StrVec(initializer_list<string>)
	{
	//��ʵ���ǿ�������
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
	}*/
	StrVec&operator=(const StrVec&);//��ֵ�����
	StrVec&operator=(StrVec &&) noexcept;//�ƶ���ֵ�����
	~StrVec();//��������
			  //�ӿ�
	void push_back(const std::string&);//������
	void push_back(std::string &&);//�ƶ���
	size_t size() const { return first_free - elements; }
	//int resize(size_t );//�Զ���
	//int resize(size_t ,std::string);//�Զ���
	size_t capacity() const { return cap - elements; }
	//void reserve(size_t);//�Զ���
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }
private:
	//��̬���ݳ�Ա
	static std::allocator<std::string> alloc;//����Ԫ��
											 //��Ա����
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }//��֤����������һ����Ԫ�صĿռ�
	std::pair<std::string*, std::string*>alloc_n_copy(const std::string*, const std::string*);//�����ڴ棬������һ��������Χ�е�Ԫ��
	void free();//����Ԫ�ز��ͷ��ڴ�
	void reallocate();//�ռ�����ʱ�����¿ռ�
					  //void reallocate(size_t sz);//�������ݵ�ָ����С
					  //���ݳ�Ա
	std::string *elements;//��Ԫ��
	std::string *first_free;//β��ָ��
	std::string *cap;//ָ�������ÿռ�
};

//16.58
template<class ...Args>
inline 
void StrVec::emplace_back(Args && ...)//��Args��չ
{
	chk_n_alloc();
	alloc.construct(first_free++, std::forward<Args>(args)...);//forword����ʹ�������͵õ����� 
	//ʵ�μ���չArgs����չargs
}
