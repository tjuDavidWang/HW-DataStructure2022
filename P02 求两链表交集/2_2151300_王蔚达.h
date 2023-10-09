/*List 链表类*/
#ifndef _SINGLELIST_H_
#define _SINGLELIST_H_

#include<iostream>
using namespace std;

//链表结点类的定义
template <class Type>
struct LinkNode {
	Type data;				//数据域
	LinkNode<Type>* link;	//链指针域
	//两种构造函数，看是否有数据对其进行初始化
	LinkNode(LinkNode<Type>* ptr = NULL) :link(ptr) {}
	LinkNode(const Type& item, LinkNode<Type>* ptr = NULL) :data(item), link(ptr) {}
};
//对单链表的定义
template <class Type>
class List {
protected:
	LinkNode<Type>* first;								//链表的头指针
public:
	List() { first = new LinkNode<Type>; }
	List(const Type& x) { first = new LinkNode<Type>(x); }
	List(List<Type>& L);								//复制构造函数
	~List() { makeEmpty(); }							//析构函数
	void makeEmpty();									//将链表设置成为空表
	int Length();										//计算链表的长度
	LinkNode<Type>* getHead()const { return first; }	//返回头指针的地址
	void setHead(LinkNode<Type>* ptr) { first = ptr; };	//设置头结点的地址
	LinkNode<Type>* Search(Type x);						//搜索含数据x的元素
	LinkNode<Type>* Locate(int i);						//搜索出第i个元素的地址
	Type* getData(int i);								//得到的i个元素的值
	void setData(int i, Type& x);						//用x修改第i个元素的值
	bool Insert(int i, Type& x);						//在第i个元素后面插入x
	bool Remove(int i, Type & x);						//删除第i个元素,x返回其值
	bool IsEmpty()const									//判断表是否为空
	{
		return first->link == NULL ? true : false;
	}
	bool IsFull()const { return false; }				//判断链表是否满了,直接返回false
	void Input(int num);								//一起输入
	void push_back(Type input);					//逐个输入
	void Output();										//输出
	List<Type>& operator=(List<Type>& L);				//重载函数:赋值
};

//复制构造函数
template<class Type>List<Type>::List(List<Type>& L)
{
	Type value;
	LinkNode<Type>* from_ptr = L.getHead();
	LinkNode<Type>* to_ptr = first = new LinkNode<Type>;
	while (from_ptr->link != NULL) {
		value = from_ptr->link->data;
		to_ptr->link = new LinkNode<Type>(value);
		to_ptr = to_ptr->link;
		from_ptr = from_ptr->link;
	}
	to_ptr->link = NULL;
}
//将链表设置成为空表
template<class Type>void List<Type>::makeEmpty()
{
	LinkNode<Type>* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = first->link->link;
		delete q;
	}
	delete first;
}
//计算链表的长度
template<class Type>int List<Type>::Length()
{
	int count = 0;
	LinkNode<Type>* ptr = first->link;
	while (ptr != NULL) {
		ptr = ptr->link;
		++count;
	}
	return count;
}
//搜索含数据x的元素
template<class Type>LinkNode<Type>* List<Type>::Search(Type x)
{
	LinkNode<Type>* cur = first->link;
	while (cur != NULL) {
		if (cur->data == x)
			break;
		else
			cur = cur->link;
	}
	return cur;
}
//搜索出第i个元素的地址(>=0),找不到则返回NULL
template<class Type>LinkNode<Type>* List<Type>::Locate(int i)
{
	if (i < 0 || i>Length())return NULL;
	LinkNode<Type>* cur = first;
	int k = 0;
	while (cur != NULL && k < i) {
		cur = cur->link;
		++k;
	}
	return cur;
}
//得到的i个元素的值,返回指针，便于区分是否有该元素
template<class Type>Type* List<Type>::getData(int i)
{
	if (i < 0)return NULL;
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return NULL;
	else
		return &cur->data;
}
//用x修改第i个元素的值
template<class Type>void List<Type>::setData(int i, Type& x)
{
	if (i <= 0)return;//i值太小
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return;//i值太大
	else
		cur->data = x;
}
//在第i个元素后面插入x
template<class Type>bool List<Type>::Insert(int i, Type& x)
{
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return false;
	LinkNode<Type>* newNode = new LinkNode<Type>(x);
	if (newNode == NULL) {
		cerr << "内存分配错误!" << endl;
		exit(1);
	}
	newNode->link = cur->link;
	cur->link = newNode;
	return true;
}
//删除第i个元素,x返回其值
template<class Type>bool List<Type>::Remove(int i, Type& x)
{
	LinkNode<Type>* cur = Locate(i - 1);//注意是从第i-1个去看
	if (cur == NULL || cur->link == NULL)
		return false;
	LinkNode<Type>* del = cur->link;
	cur->link = del->link;
	x = del->data;
	delete del;
	return true;
}
//输入:采用后插法，将第一次输入的所有结点集成到链表中
template<class Type>void List<Type>::Input(int num)
{
	//需要有endTag/num来结束一次的输入
	LinkNode<Type>* newNode, * last;
	Type val;
	first = new LinkNode<Type>;//设置空头结点
	if (first == NULL || num < 0) {
		cerr << "存储分配错误!" << endl;
		exit(1);
	}
	if (num == 0) {
		first->link = NULL;
		return;
	}
	last = first;
	while (num--) {
		cin >> val;//记得对Type类型进行>>运算符重载
		newNode = new LinkNode<Type>(val);
		if (newNode == NULL) {
			cerr << "存储分配错误!" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
	}
}
//逐个输入
template<class Type>void List<Type>::push_back(Type input)
{
	LinkNode<Type>* newNode, * last;
	//得到最后面的结点位置
	for (last = first; last->link != NULL; last = last->link);

	newNode = new LinkNode<Type>(input);
	if (newNode == NULL) {
		cerr << "存储分配错误!" << endl;
		exit(1);
	}
	last->link = newNode;
	last = newNode;
}

//输出
template<class Type>void List<Type>::Output()
{
	LinkNode<Type>* cur = first->link;
	if (cur == NULL) {
		cout << "NULL" << endl;
		return;
	}
	while (cur != NULL) {
		cout << cur->data << " ";//注意这里要对运算符<<重载
		cur = cur->link;
	}
}
//重载函数:赋值
template<class Type>List<Type>& List<Type>::operator=(List<Type>& L)
{
	Type value;
	LinkNode<Type>* srcptr = L.getHead();
	LinkNode<Type>* destptr = first = new LinkNode<Type>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;//注意要对data的=进行运算符重载
		destptr->link = new LinkNode<Type>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;//最后一个要指向NULL
	return *this;//返回操作对象地址
}


#endif