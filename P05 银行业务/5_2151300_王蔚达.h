#ifndef _BANK_H_
#define _BANK_H_

#include<iostream>
#include<assert.h>
using namespace std;

/*List链表类*/
#ifndef _SINGLELIST_H_
#define _SINGLELIST_H_
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
class SingleList {
protected:
	LinkNode<Type>* first;								//链表的头指针
public:
	SingleList() { first = new LinkNode<Type>; }
	SingleList(const Type& x) { first = new LinkNode<Type>(x); }
	SingleList(SingleList<Type>& L);					//复制构造函数
	~SingleList() { makeEmpty(); }						//析构函数
	void makeEmpty();									//将链表设置成为空表
	int Length();										//计算链表的长度
	LinkNode<Type>* getHead()const { return first; }	//返回头指针的地址
	void setHead(LinkNode<Type>* ptr) { first = ptr; };	//设置头结点的地址
	LinkNode<Type>* Search(Type x);						//搜索含数据x的元素
	LinkNode<Type>* Locate(int i);						//搜索出第i个元素的地址
	Type* getData(int i);								//得到的i个元素的值
	void setData(int i, Type& x);						//用x修改第i个元素的值
	bool Insert(int i, Type& x);						//在第i个元素后面插入x
	bool Remove(int i, Type& x);						//删除第i个元素,x返回其值
	bool IsEmpty()const									//判断表是否为空
	{
		return first->link == NULL ? true : false;
	}
	bool IsFull()const { return false; }				//判断链表是否满了,直接返回false
	void Input(int num);								//输入
	void Output();										//输出
	SingleList<Type>& operator=(SingleList<Type>& L);	//重载函数:赋值
};

//复制构造函数
template<class Type>SingleList<Type>::SingleList(SingleList<Type>& L)
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
template<class Type>void SingleList<Type>::makeEmpty()
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
template<class Type>int SingleList<Type>::Length()
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
template<class Type>LinkNode<Type>* SingleList<Type>::Search(Type x)
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
template<class Type>LinkNode<Type>* SingleList<Type>::Locate(int i)
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
template<class Type>Type* SingleList<Type>::getData(int i)
{
	if (i < 0)return NULL;
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return NULL;
	else
		return &cur->data;
}
//用x修改第i个元素的值
template<class Type>void SingleList<Type>::setData(int i, Type& x)
{
	if (i <= 0)return;//i值太小
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return;//i值太大
	else
		cur->data = x;
}
//在第i个元素后面插入x
template<class Type>bool SingleList<Type>::Insert(int i, Type& x)
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
template<class Type>bool SingleList<Type>::Remove(int i, Type& x)
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
template<class Type>void SingleList<Type>::Input(int num)
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
//输出
template<class Type>void SingleList<Type>::Output()
{
	LinkNode<Type>* cur = first->link;
	while (cur != NULL) {
		cout << cur.data << endl;//注意这里要对运算符<<重载
		cur = cur->link;
	}
}
//重载函数:赋值
template<class Type>SingleList<Type>& SingleList<Type>::operator=(SingleList<Type>& L)
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

/*Queue队列类*/
#ifndef _QUEUE_H_
#define _QUEUE_H_

//父类-纯虚
const int maxSize = 50;
template<class Type>
class Queue {
public:
	Queue() {};
	~Queue() {};
	virtual bool EnQueue(const Type& x) = 0;	//新元素x进入队列
	virtual bool DeQueue(Type& x) = 0;			//队头元素出队列
	virtual bool getFront(Type& x)const = 0;	//读取对头元素的值
	virtual bool IsEmpty()const = 0;			//判断队列空否
	//virtual bool IsFull()const = 0;			//判断队列满否
	virtual int getSize()const = 0;				//求队列元素个数
};
//队列的链式储存
template<class Type>
class LinkedQueue :public Queue<Type> {
protected:
	LinkNode<Type>* front, * rear;
public:
	LinkedQueue() :front(NULL), rear(NULL) {}
	~LinkedQueue() { makeEmpty(); }

	bool IsEmpty()const;
	void makeEmpty();
	int getSize()const;
	bool getFront(Type& x)const;

	bool EnQueue(const Type& x);
	bool DeQueue(Type& x);
	Type DeQueue();

};
//判断队列空否
template<class Type> bool LinkedQueue<Type>::IsEmpty()const
{
	return (front == NULL) ? true : false;
}
//置空队列，释放链表中所有结点
template<class Type> void LinkedQueue<Type>::makeEmpty()
{
	LinkNode<Type>* del;
	while (front != NULL) {
		del = front;
		front = front->link;
		delete del;
	}
}
//求队列元素个数
template<class Type>int LinkedQueue<Type>::getSize() const
{
	LinkNode<Type>* ptr = front;
	int cnt = 0;
	while (ptr != NULL) {
		ptr = ptr->link;
		cnt++;
	}
	return cnt;
}
//读取对头元素的值
template<class Type>bool LinkedQueue<Type>::getFront(Type& x) const
{
	if (IsEmpty())return false;
	x = front->data;
	return true;
}
//新元素x进入队列
template<class Type>bool LinkedQueue<Type>::EnQueue(const Type& x)
{
	if (front == NULL) {
		front = rear = new LinkNode<Type>(x);//一开始指向同一块地方
		if (front == NULL) return false;
	}
	else {
		rear->link = new LinkNode<Type>(x);
		if (rear == NULL)return false;
		rear = rear->link;
	}
	return true;

}
//队头元素出队列
template<class Type>bool LinkedQueue<Type>::DeQueue(Type& x)
{
	//if (IsEmpty())return false;
	LinkNode<Type>* del = front;
	x = front->data;
	front = front->link;
	delete del;
	return true;
}
template<class Type> Type LinkedQueue<Type>::DeQueue()
{

	LinkNode<Type>* del = front;
	Type x = front->data;
	front = front->link;
	delete del;
	return x;
}

//输出队列元素
template<class Type>ostream& operator<<(ostream& os, const LinkedQueue<Type>& queue)
{
	os << "队列中的元素个数有" << queue.getSize() << endl;
	LinkNode<Type>* ptr = queue.front;
	int i = 0;
	while (ptr != NULL) {
		os << ++i << ":" << ptr->data << endl;
		ptr = ptr->link;
	}
	return os;
}

#endif // !_QUEUE_H_
#endif // !_BANK_H_
