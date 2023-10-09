#include<iostream>
#include<assert.h>
using namespace std;

/*List 链表类*/
#ifndef _LIST_H_
#define _LIST_H_

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
	List(List<Type>& L);					//复制构造函数
	~List() { makeEmpty(); }						//析构函数
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
	List<Type>& operator=(List<Type>& L);	//重载函数:赋值
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
//输出
template<class Type>void List<Type>::Output()
{
	LinkNode<Type>* cur = first->link;
	while (cur != NULL) {
		cout << cur.data << endl;//注意这里要对运算符<<重载
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


#endif // !_LIST_H_

/*Stack 栈类*/
#ifndef _STACK_H_
#define _STACK_H_


//链式栈的定义:使用之前定义过的单链表
template<class Type>
class Stack
{
private:
	LinkNode<Type>* top;			//栈顶指针
public:
	Stack() :top(NULL) {}				//构造函数
	~Stack() { makeEmpty(); }		//析构函数
	bool IsEmpty()const;			//检查栈是否为空
	void makeEmpty();				//将栈清空
	Type getTop()const;		//得到栈顶元素

	void Push(const Type& x);		//将元素压入栈顶
	Type Pop();				//将栈顶元素弹出
	bool Pop(Type& x);				//将栈顶元素弹出
	int size()const;				//获得栈中元素的多少

	friend ostream& operator<<<Type>(ostream& os, const Stack<Type>& stack);//输出栈中的元素
};
//检查栈是否为空
template<class Type>bool Stack<Type>::IsEmpty()const {
	if (top == NULL)return true;
	else return false;
}
//获得栈中元素的多少
template<class Type>int Stack<Type>::size() const {
	LinkNode<Type>* ptr = top;
	int cnt = 0;
	while (top != NULL) {
		top = top->link;
		cnt++;
	}
	return cnt;
}
//将栈清空
template<class Type>void Stack<Type>::makeEmpty() {
	LinkNode<Type>* del;
	while (top != NULL) {
		del = top;
		top = top->link;
		delete del;
	}
}
//将元素压入栈顶
template<class Type>void Stack<Type>::Push(const Type& x) {
	top = new LinkNode<Type>(x, top);//将新进来的link指向top
	if (top == NULL) {
		cout << "存储分配错误！" << endl;
		exit(1);
	}
}
//将栈顶元素弹出
template<class Type>Type Stack<Type>::Pop() {
	if (IsEmpty() == true)
		exit(1);
	LinkNode<Type>* del = top;
	Type x = top->data;
	top = top->link;
	delete del;
	return x;
}
template<class Type>bool Stack<Type>::Pop(Type& x) {
	if (IsEmpty() == true)return false;
	LinkNode<Type>* del = top;
	top = top->link;
	x = del->data;
	delete del;
	return true;
}
//得到栈顶元素
template<class Type>Type Stack<Type>::getTop() const {
	if (IsEmpty() == true)
		exit(1);
	return top->data;
}
//输出栈中的元素
template<class Type>ostream& operator<<(ostream& os, const Stack<Type>& stack) {
	os << "栈中元素的个数 = " << stack.size() << endl;
	LinkNode<Type>* ptr = stack.top;
	int i = 0;
	while (ptr != NULL)
		os << ++i << ":" << ptr->data << endl;
	return os;
}

#endif // !_STACK_H_

/*Vector 向量类*/
#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_DEFAULT_SIZE 1

template<class Type>
class Vector
{
private:
	int curSize;		//数据大小
	int maxSize;		//当前容量
	Type* data;			//数据
public:
	//迭代器
	class Iterator
	{
	private:
		Type* data;			//一个指针，指向数据类型
	public:
		//默认构造函数
		Iterator() :data(nullptr) {};
		//构造函数
		Iterator(Type* init_data) :data(init_data) {};

		//运算符重载
		//读数据操作
		Type& operator*() { return *data; }
		//比较运算符
		bool operator==(const Iterator& comp)const { return data == comp.data; }
		bool operator<(const Iterator& comp)const { return data < comp.data; }
		bool operator>(const Iterator& comp)const { return data > comp.data; }
		bool operator>=(const Iterator& comp)const { return data >= comp.data; }
		bool operator<=(const Iterator& comp)const { return data <= comp.data; }
		bool operator!=(const Iterator& comp)const { return data != comp.data; }
		//自增运算符:前置和后置
		Vector<Type>::Iterator& operator++() { data++; return (*this); }
		Vector<Type>::Iterator operator++(int)
		{
			Vector<Type>::Iterator old = (*this);
			++(*this);
			return old;
		}
		//自减运算符:前置和后置
		Vector<Type>::Iterator& operator--() { data--; return (*this); }
		Vector<Type>::Iterator operator--(int) {
			Vector<Type>::Iterator old = (*this);
			--(*this);
			return old;
		}
		//后加上一个数
		Vector<Type>::Iterator operator+(int index)
		{
			Vector<Type>::Iterator old = (*this);
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//前加上一个数,需要使用typename才能让编译器知道Vector<Type>是个类型
		friend typename Vector<Type>::Iterator operator+(int index, typename Vector<Type>::Iterator data)
		{
			typename Vector<Type>::Iterator old = data;
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//后减去一个数
		Vector<Type>::Iterator operator-(int index)
		{
			Vector<Type>::Iterator old = (*this);
			for (int i = 0; i < index; ++i)
				--old;
			return old;
		}
		//自加
		Vector<Type>::Iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i)
				++(*this);
			return (*this);
		}
		//自减
		Vector<Type>::Iterator& operator-=(int index)
		{
			for (int i = 0; i < index; ++i)
				--(*this);
			return (*this);
		}
		friend int operator-(const Vector<Type>::Iterator& i, const Vector<Type>::Iterator& j)
		{
			return int(i.data - j.data);
		}
	};
	Vector();
	Vector(int init_size);
	Vector(const Vector& ob);
	Vector(int init_size, Type indata);
	~Vector() { delete[]data; }

	int size()const { return curSize; }
	void push_back(const Type& element);				//尾部插入数据
	Type pop_back();								//删除尾部数据
	Type getLast() { return data[curSize - 1]; }
	bool insert(const Iterator place, Type item);	//在指定迭代器位置插入数据
	bool erase(const Iterator place);				//删除指定迭代器的数据
	bool clear();									//清空数据
	bool IsEmpty() { return curSize == 0; }

	void fillAll(const Type x);						//给元素统一赋值
	bool Enlarge();									//扩大元素容量

	void Print();

	Type& operator[](int i);
	Vector<Type>& operator=(const Vector<Type>& ob);

	//有了这个才更好地指示所在位置
	Iterator begin();
	Iterator end();
	const Vector<Type>::Iterator begin()const;
	const Vector<Type>::Iterator end()const;
};
//构造函数
template<class Type> Vector<Type>::Vector()
	:curSize(0), maxSize(VECTOR_DEFAULT_SIZE)
{
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "内存分配错误！" << endl;
		exit(1);
	}
}
template<class Type> Vector<Type>::Vector(int init_size)
{
	curSize = init_size;
	maxSize = (init_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "内存分配错误！" << endl;
		exit(1);
	}
}
template<class Type> Vector<Type>::Vector(const Vector& ob)
{
	curSize = ob.curSize;
	maxSize = ob.maxSize;
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "内存分配错误！" << endl;
		exit(1);
	}
	for (int i = 0; i < curSize; ++i)
		data[i] = ob.data[i];
}
template<class Type> Vector<Type>::Vector(int init_size, Type init_data)
{
	curSize = init_size;
	maxSize = (init_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "内存分配错误！" << endl;
		exit(1);
	}
	for (int i = 0; i < curSize; ++i)
		data[i] = init_data;
}
//尾部插入数据
template<class Type>void Vector<Type>::push_back(const Type& element) {
	if (curSize == maxSize)
		Enlarge();
	data[curSize++] = element;//注意这里的curSize是用完了再++
}
//删除尾部数据
template<class Type>Type Vector<Type>::pop_back() {
	if (curSize == 0) {
		cout << "Vector中没有元素了！" << endl;
		exit(1);
	}
	return data[--curSize];//注意这里是先--curSize再返回
}
//在指定迭代器位置插入数据
template<class Type> bool Vector<Type>::insert(const Iterator place, Type item)
{
	//先记录下相对位置，之后Enlarge会导致其地址变化
	int pos = place - begin();
	if (curSize == maxSize)
		if (Enlarge() == false)return false;
	int i = 0;
	//将元素都向后移动一位
	for (i = curSize - 1; i >= pos; --i)
		data[i + 1] = data[i];
	data[pos] = item;
	curSize++;
	return true;
}
//删除指定迭代器的数据
template<class Type>bool Vector<Type>::erase(const Iterator place)
{
	int pos = place - begin();
	if (pos < 0 || pos >= curSize)
		return false;
	while (pos < curSize - 1) {
		data[pos] = data[pos + 1];
		++pos;
	}
	curSize--;
	return true;
}
//清空数据
template<class Type>bool Vector<Type>::clear() {
	delete[]data;
	curSize = 0;
	maxSize = VECTOR_DEFAULT_SIZE;
	data = new Type[maxSize];
	if (data == NULL)
		return false;
	return true;
}
//统一赋值(覆盖已经有过值的部分)
template<class Type>void Vector<Type>::fillAll(const Type x)
{
	for (int i = 0; i < curSize; i++)
		data[i] = x;
}
//扩大元素容量
template<class Type>bool Vector<Type>::Enlarge()
{
	maxSize += VECTOR_DEFAULT_SIZE;
	Type* del = data;
	Type* newData = new Type[maxSize];
	if (newData == NULL)return false;
	for (int i = 0; i < curSize; ++i)
		newData[i] = data[i];
	data = newData;
	delete[]del;
	return true;
}
template<class Type> void Vector<Type>::Print()
{
	for (int i = 0; i < curSize; ++i)
		cout << data[i] << " ";
}
//重载下标运算符
template<class Type>Type& Vector<Type>::operator[](int i)
{
	if (i < 0 || i >= curSize) {
		cout << "地址访问错误！" << endl;
		exit(1);
	}
	return data[i];
}
//重载等号运算符
template<class Type>Vector<Type>& Vector<Type>::operator=(const Vector<Type>& ob)
{
	//若两者的地址相同则直接返回
	if (data == ob.data)//是两个==，真的哭死
		return *this;
	this->clear();
	for (auto i = ob.begin(); i != ob.end(); ++i)
		this->push_back(*i);
	return *this;
}
template<class Type>typename Vector<Type>::Iterator Vector<Type>::begin() {
	return curSize > 0 ? typename Vector<Type>::Iterator(&data[0]) :
		typename Vector<Type>::Iterator();
}
template<class Type>inline const typename Vector<Type>::Iterator Vector<Type>::begin()const
{
	return curSize > 0 ? typename Vector<Type>::Iterator(&data[0]) :
		typename Vector<Type>::Iterator();
}

template<class Type>typename Vector<Type>::Iterator Vector<Type>::end()
{
	return curSize > 0 ? ++(typename Vector<Type>::Iterator(&data[curSize - 1])) :
		typename Vector<Type>::Iterator();
}
template<class Type>
inline const typename Vector<Type>::Iterator Vector<Type>::end()const
{
	return curSize > 0 ? ++(typename Vector<Type>::Iterator(&data[curSize - 1])) :
		typename Vector<Type>::Iterator();
}
#endif // !_VECTOR_H_

/*LinkedQueue 链式队列类*/
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

/*PriorityQueue 优先队列类*/
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

template<class Type>bool Compare_Max(Type a, Type b) {
	return a > b;
}
template<class Type>bool Compare_Min(Type a, Type b) {
	return a < b;
}

template<class Type>void FilterDown(int start, int curSize, Type* heap, bool(*Comp)(Type, Type))
{
	int curPos = start;
	while (curPos >= 0) {
		int cur = curPos;
		int child = 2 * curPos + 1;//j是i的左子
		Type temp = heap[cur];

		//保证是小根堆，每一个子树也是
		while (child < curSize)
		{
			if (child < curSize - 1 && Comp(heap[child + 1], heap[child])) //j不是指向最后一个结点,两子女中选小者
				child++;
			if (Comp(heap[cur], heap[child]))//head的值比pos小
				break;
			else //head的值比pos大
			{
				heap[cur] = heap[child];
				cur = child;

				child = 2 * child + 1;//pos转到它的左子上
			}
		}
		heap[cur] = temp;

		curPos--;
	}

}
template<class Type>void FilterUp(int start, Type* heap, bool(*Comp)(Type, Type)) {
	int cur = start, parent = (cur - 1) / 2;
	Type temp = heap[cur];
	while (cur > 0) {
		if (Comp(heap[parent], heap[cur]))//parent<heap
			break;
		else {
			heap[cur] = heap[parent];
			cur = parent;
			parent = (parent - 1) / 2;
		}
		heap[cur] = temp;
	}
}
template<class Type>int Insert(const Type& x, int& curSize, Type* heap, bool(*Comp)(Type, Type)) {
	//if (curSize == maxSize) {
	//	cout << "堆已满" << endl;
	//	return 0;
	//}
	heap[curSize] = x;
	FilterUp(curSize, heap, Comp);
	curSize++;
	return 1;
}
template<class Type>int Remove(Type& x, int& curSize, Type* heap, bool(*Comp)(Type, Type)) {
	if (curSize == 0) {
		cout << "堆已空" << endl;
	}
	x = heap[0];
	heap[0] = heap[--curSize];//取最后一个填补到头上
	FilterDown(0, curSize, heap, Comp);//自上而下调整
	return 1;
}


template<class Type>
class PriorityQueue {
protected:
	Type* data;
	int maxSize;
	int curSize;
	bool(*Compare)(Type, Type);	//采用函数指针指示比较方式，默认是Min
	enum { DefaultPQSize = 100 };
public:
	PriorityQueue(bool (*compare)(Type, Type) = Compare_Min, int size = DefaultPQSize);
	~PriorityQueue() { delete[]data; }
	bool push(const Type& x);
	bool pop(Type& x);
	int size()const { return curSize; }

	bool getFront(Type& x);

	void makeEmpty() { curSize = 0; }
	bool IsEmpty() { return curSize == 0; }
	bool IsFull() { return curSize == maxSize; }
	void Print() {
		for (int i = 0; i < curSize; ++i)
			cout << data[i] << " ";
		cout << endl;
	}
};

template<class Type>PriorityQueue<Type>::PriorityQueue(bool (*compare)(Type, Type), int size)
	:maxSize(size), curSize(0), Compare(compare) {
	data = new Type[maxSize];
	assert(data != NULL);
}
template<class Type> bool PriorityQueue<Type>::push(const Type& x)
{
	if (IsFull())return false;
	Insert(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::pop(Type& x)
{
	if (IsEmpty())return false;
	Remove(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::getFront(Type& x)
{
	if (IsEmpty())return false;
	x = data[0];
	return true;
}


#endif // !_PRIORITY_QUEUE_H_

/*Maze 迷宫处理类*/
#ifndef _MAZE_H_
#define _MAZE_H_
enum Direction { NONE = -1, UP, DOWN, LEFT, RIGHT };

#define Static_Rows 15
#define Static_Cols 15

#define Wall_Patten '#'
#define Passage_Patten '0'
#define ShowWay '1'
#define MAX_INT 1000

#define WALL "# "//"█ "
#define WAY "O "// "⊙"
#define PATH "  "

struct Position {
	int X, Y;
	int dir;
	int predictCost = 0;
	Position() :X(-1), Y(-1), dir(NONE), predictCost(0) {};
	Position(int x, int y) :X(x), Y(y), dir(NONE), predictCost(0) {};
	Position(int x, int y, Position dst) :X(x), Y(y), dir(NONE) {
		//计算曼哈顿距离，进行对预期的比较
		predictCost = (X > dst.X) ? X - dst.X : dst.X - X;
		predictCost += (Y > dst.Y) ? Y - dst.Y : dst.Y - Y;
	};
	Position(int x, int y, Direction tdir) :X(x), Y(y), dir(tdir) {};
	Position& operator =(Position pos) {
		X = pos.X;
		Y = pos.Y;
		dir = pos.dir;//push_back()中有涉及到赋值
		predictCost = pos.predictCost;
		return *this;
	}
	bool operator ==(Position& ob) {
		if (ob.X == X && ob.Y == Y)
			return true;
		else return false;
	}
	bool operator !=(Position& ob) {
		if (ob.X == X && ob.Y == Y)
			return false;
		else return true;
	}
	friend ostream& operator <<(ostream& out, const Position pos) {
		out << '<' << pos.X << ',' << pos.Y << '>' << ' ';
		return out;
	}
};


//将其传入PrioityQueue中，确定出队列的优先级
bool PositionCompare(Position a, Position b) {
	int distance_A, distance_B;
	distance_A = a.predictCost;
	distance_B = b.predictCost;
	bool res = distance_A < distance_B;
	return res;
}

class MazeProblem {
private:
	char** maze = {};
	int rows = 0;
	int cols = 0;
	int move[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };//右下左上
	Vector<Position> res;//用于储存路径结果
private:
	//打印迷宫与路径
	void printMaze()
	{
		cout << endl;
		if (cols + rows >= 300) {
			cout << "迷宫行列数太多，此处不做打印" << endl;
			return;
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (maze[i][j] == '#')
					cout << WALL;//█
				else if (maze[i][j] == ShowWay)
					cout << WAY;
				else
					cout << PATH;
			}
			cout << endl;
		}
	}
	//以坐标形式-0打印迷宫路径
	void printPath() {

		cout << endl << "迷宫路径：" << endl;
		//已经对Postion中运算符<<重载
		for (int i = res.size() - 1; i > 0; i--) {
			cout << res[i] << " ---> ";
		}
		cout << res[0] << endl;
	}

	//DFS寻路算法
	void DFS_SeekPath(Position src, Position dst) {
		printMaze();
		Vector<Position> stack;
		stack.clear();
		bool notFind = false;

		Vector<Vector<bool>> visited(rows, Vector<bool>(cols, false));
		stack.push_back(src);
		visited[src.X][src.Y] = true;

		//运用栈的结构解决问题
		while (stack.getLast() != dst) {
			if (stack.IsEmpty())
				notFind = 1;

			Position cur = stack[stack.size() - 1];
			Position pre;
			if (stack.size() >= 2)
				pre = stack[stack.size() - 2];

			//访问其四个方向
			int dir = cur.dir + 1;
			while (dir < 4)
			{
				int x1 = cur.X + move[dir][0];
				int y1 = cur.Y + move[dir][1];
				Position newPos(x1, y1);
				if (maze[x1][y1] == Wall_Patten || visited[x1][y1] == true)//该点是墙，或者该点已经访问过了
					dir++;
				else {
					stack[stack.size() - 1].dir = dir;
					stack.push_back(newPos);
					visited[newPos.X][newPos.Y] = true;
					break;
				}
			}
			if (dir == 4)//四个方向都找过了没有，是死路,将点pop出来
			{
				Position temp = stack.pop_back();
				visited[temp.X][temp.Y] = false;
			}
		}


		if (notFind) {
			cout << "没有路径可将其连通！" << endl;
			exit(1);
		}
		else {
			while (stack.IsEmpty() == false) {
				Position temp = stack.pop_back();
				res.push_back(temp);
				maze[temp.X][temp.Y] = ShowWay;
			}

		}

	}
	//BFS寻路算法
	void BFS_SeekPath(Position src, Position dst) {
		Vector<Vector<int>>mazePoint(rows, Vector<int>(cols, 0));//用于记录层数
		Position cur = src;
		LinkedQueue<Position>queue;
		bool find = 0;

		mazePoint[src.X][src.Y] = 1;
		queue.EnQueue(cur);

		while (queue.IsEmpty() == false) {
			queue.DeQueue(cur);
			int dir = 0;
			while (dir < 4) {
				Position temp(cur.X + move[dir][0], cur.Y + move[dir][1]);
				if (temp.X == dst.X && temp.Y == dst.Y) {//查找到终点了
					find = 1;
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					break;
				}
				if (mazePoint[temp.X][temp.Y] == 0 && maze[temp.X][temp.Y] != Wall_Patten) {
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					queue.EnQueue(temp);
				}
				else
					dir++;//其他则查找下一个方向
			}
			if (find == 1) {
				queue.makeEmpty();
				res.push_back(Position(dst));
				break;
			}
		}

		if (find == 0) {
			cout << "没有路径可将其连通！" << endl;
			exit(1);
		}
		//生成路径
		else {
			int x = dst.X, y = dst.Y;
			int cnt = mazePoint[x][y];
			maze[x][y] = ShowWay;
			for (; cnt > 1; cnt--) {
				Position tmp(x, y);
				int dir = 0;
				while (dir < 4) {
					int x1 = x + move[dir][0];
					int y1 = y + move[dir][1];
					if (mazePoint[x1][y1] == cnt - 1) {
						x = x1; y = y1;
						res.push_back(Position(x, y));
						maze[x][y] = ShowWay;
						break;
					}
					dir++;
				}
			}
		}
	}
	//A*算法寻路，已经完成
	void AStar_SeekPath(Position src, Position dst) {
		//初始化计算
		Vector<Vector<int>>mazePoint(rows, Vector<int>(cols, 0));
		PriorityQueue<Position>Pqueue(PositionCompare, rows);
		bool find = 0;

		mazePoint[src.X][src.Y] = 1;
		Pqueue.push(Position(src.X, src.Y, dst));

		while (Pqueue.IsEmpty() == false) {
			Position cur, top;
			Pqueue.pop(cur);
			Pqueue.getFront(top);

			int dir = 0;
			while (dir < 4) {
				Position temp(cur.X + move[dir][0], cur.Y + move[dir][1], dst);
				if (temp.X == dst.X && temp.Y == dst.Y) {//查找到终点了
					find = 1;
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					break;
				}
				if (mazePoint[temp.X][temp.Y] == 0 && maze[temp.X][temp.Y] != Wall_Patten) {
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					//GotoXY(temp.Y*2, temp.X );
					//cout<< "⊙";
					Pqueue.push(temp);
				}
				else
					dir++;//其他则查找下一个方向
			}

			if (find == 1) {
				res.push_back(Position(dst));
				break;
			}
		}
		//GotoXY(cols * 2, rows);
		if (find == 0) {
			cout << "没有路径可将其连通！" << endl;
			exit(1);
		}
		//生成路径
		else {
			int x = dst.X, y = dst.Y;
			int cnt = mazePoint[x][y];
			maze[x][y] = ShowWay;
			for (; cnt > 1; cnt--) {
				Position tmp(x, y);
				int dir = 0;
				while (dir < 4) {
					int x1 = x + move[dir][0];
					int y1 = y + move[dir][1];
					if (mazePoint[x1][y1] == cnt - 1) {
						x = x1; y = y1;
						res.push_back(Position(x, y));
						maze[x][y] = ShowWay;
						break;
					}
					dir++;
				}
			}
		}
	}

	//找出与当前位置相邻的墙，用于Prim算法生成随机迷宫
	void FindBlock(int pos_X, int pos_Y, Vector<Position>& myblock) {
		if (pos_X + 1 < rows - 1 && maze[pos_X + 1][pos_Y] == Wall_Patten) {//down
			myblock.push_back(Position(pos_X + 1, pos_Y, DOWN));
		}
		if (pos_Y + 1 < cols - 1 && maze[pos_X][pos_Y + 1] == Wall_Patten) {//right
			myblock.push_back(Position(pos_X, pos_Y + 1, RIGHT));
		}
		if (pos_X - 1 > 1 && maze[pos_X - 1][pos_Y] == Wall_Patten) {//up
			myblock.push_back(Position(pos_X - 1, pos_Y, UP));
		}
		if (pos_Y - 1 > 1 && maze[pos_X][pos_Y - 1] == Wall_Patten) {//left
			myblock.push_back(Position(pos_X, pos_Y - 1, LEFT));
		}
	}
public:
	//检查整数是否越界
	void getNum(int& num)
	{
		while (true)
		{
			cin >> num;
			if (cin.fail() || num < 3 || num >= MAX_INT)
			{
				cout << "输入错误,请输入在[3," << MAX_INT << "]之间的正整数, 请重新输入：";
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}
	}
	//生成随机迷宫
	void getRandomMaze() {
		cout << "请输入地图的行数：";
		getNum(rows);
		cout << "请输入地图的列数：";
		getNum(cols);

		///////////////////////////////////////////Prim迷宫生成算法/////////////////////////////////////////////////

		//等待提示：解决行列数太大用户不知道在干什么的问题
		cout << endl << "迷宫生成中......" << endl;

		//把地图其余部分全部设置为墙
		maze = new char* [rows];
		for (int i = 0; i < rows; ++i) {
			maze[i] = new char[cols + 1];
			for (int j = 0; j <= cols; ++j)
				maze[i][j] = Wall_Patten;
			maze[i][cols] = '\0';
		}

		maze[1][1] = Passage_Patten;
		Vector<Position>myblock;

		//srand(1);//随机数种子
		srand((unsigned int)(time(0)));
		int pos_X = 1, pos_Y = 1;
		FindBlock(pos_X, pos_Y, myblock);
		//第一步压入两堵墙（起点右边和起点下面）进入循环
		while (myblock.size()) {
			int BlockSize = myblock.size();
			//随机选择一堵墙（生成0 ~ BlockSize-1之间的随机数，同时也是vector里墙的下标）
			int randnum = rand() % BlockSize;

			Position SelectBlock = myblock[randnum];

			//矿工来到我们“选择的墙”这里
			pos_X = SelectBlock.X;
			pos_Y = SelectBlock.Y;
			//根据当前选择的墙的方向进行后续操作
			//此时，起始点 选择的墙 目标块 三块区域在同一直线上
			//我们让矿工从“选择的墙”继续前进到“目标块”
			switch (SelectBlock.dir) {
			case DOWN:
				pos_X++;
				break;
			case RIGHT:
				pos_Y++;
				break;
			case LEFT:
				pos_Y--;
				break;
			case UP:
				pos_X--;
				break;
			}
			//目标块如果是墙
			if (maze[pos_X][pos_Y] == Wall_Patten) {
				//打通墙和目标块
				if ((pos_X > 0 && pos_X < rows - 1 && pos_Y>0 && pos_Y < cols - 1)) {
					maze[pos_X][pos_Y] = Passage_Patten;
					//再次找出与矿工当前位置相邻的墙
					FindBlock(pos_X, pos_Y, myblock);
				}

				if ((SelectBlock.X > 0 && SelectBlock.X < rows - 1 && SelectBlock.Y>0 && SelectBlock.Y < cols - 1))
					maze[SelectBlock.X][SelectBlock.Y] = Passage_Patten;
				/*maze[pos_X][pos_Y] = Passage_Patten;
				maze[SelectBlock.X][SelectBlock.Y] = Passage_Patten;*/

			}
			else {}//relax

			//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
			myblock.erase(myblock.begin() + randnum);
		}
		/*if (rows % 2 == 0) {
			maze[rows - 3][cols - 3] = maze[rows - 2][cols - 2] = Passage_Patten;
			maze[rows - 2][cols - 3] = maze[rows - 3][cols - 2] = Passage_Patten;
		}*/
		maze[rows - 2][cols - 3] = Wall_Patten;
		maze[rows - 2][cols - 2] = Passage_Patten;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "生成随机地图如下：" << endl;
		printMaze();

	}
	//使用固定迷宫
	void getStaticMaze()
	{
		//初始化固定迷宫
		rows = Static_Rows;
		cols = Static_Cols;
		maze = new char* [rows];
		for (int i = 0; i < rows; ++i) {
			maze[i] = new char[cols + 1];
			for (int j = 0; j <= cols; ++j)
				maze[i][j] = Wall_Patten;
		}

		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				maze[i][j] = fixed_maze[i][j];
		cout << "固定迷宫如下：" << endl;
		printMaze();
	}
	//从三种算法中选择一种寻找路径
	void FindPath()
	{
		char ch;
		cout << endl << "请输入next并按下回车进行寻找路径步骤" << endl;
		cin >> ch;
		cin.clear();
		cin.ignore(65536, '\n');

		Position src(1, 1), dst(rows - 2, cols - 2);

		cout << "****************************************" << endl;
		cout << "迷宫寻路算法：" << endl
			<< "1.DFS算法求迷宫路径" << endl
			<< "2.BFS算法求迷宫路径" << endl
			<< "3.A*算法求迷宫路径" << endl;
		cout << "****************************************" << endl;
		cout << "请选择迷宫寻路方式的编号(默认为A*算法)：";
		int algorithm;
		cin >> algorithm;

		switch (algorithm)
		{
		case 1:
			DFS_SeekPath(src, dst);
			break;
		case 2:
			BFS_SeekPath(src, dst);
			break;
		case 3:
			AStar_SeekPath(src, dst);
			break;
		default:
			AStar_SeekPath(src, dst);
			break;
		}
		cout << "默认起点为" << src << "，终点为" << dst << endl << endl;
		cout << "以下为迷宫路径展示：" << endl;
		printMaze();

		printPath();
	}
protected:
	char fixed_maze[15][15] = { //水平向右为y正；竖直向下为X正
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
	{'#','0','0','0','#','0','#','#','#','#','#','0','0','0','#'},
	{'#','0','#','0','#','0','0','0','0','0','0','0','#','0','#'},
	{'#','0','#','0','0','0','#','#','0','#','0','#','0','0','#'},
	{'#','#','#','0','#','#','0','0','0','#','0','#','#','0','#'},
	{'#','0','0','0','#','#','#','#','0','0','0','0','0','0','#'},
	{'#','#','0','#','#','0','0','0','#','#','#','0','#','#','#'},
	{'#','0','0','0','0','0','#','#','#','#','0','0','#','0','#'},
	{'#','#','#','0','#','#','#','0','#','0','0','#','#','0','#'},
	{'#','0','#','0','#','#','#','0','0','#','0','0','0','0','#'},
	{'#','0','0','0','#','#','0','#','#','#','#','0','#','0','#'},
	{'#','#','#','0','0','#','0','#','#','0','#','#','#','0','#'},
	{'#','0','#','#','0','0','0','0','#','0','#','0','0','0','#'},
	{'#','0','0','#','0','0','0','#','#','0','0','0','#','0','#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
	};
};



#endif // !_MAZE_H_


