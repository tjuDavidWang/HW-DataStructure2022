#include<iostream>
#include<assert.h>

using namespace std;

#pragma once
#ifndef _SINGLELIST_H_
#define _SINGLELIST_H_

#include<iostream>
using namespace std;
//带附加头结点的单链表类

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
	LinkNode<Type>* first;								//链表的头指针,有空头结点
public:
	List() { first = new LinkNode<Type>; }
	List(const Type& x) { first = new LinkNode<Type>(x); }
	List(const List<Type>& L);				//复制构造函数
	~List() { makeEmpty(); }						//析构函数
	void makeEmpty();									//将链表设置成为空表
	int Length();										//计算链表的长度
	LinkNode<Type>* getHead()const { return first; }	//返回头指针的地址
	void setHead(LinkNode<Type>* ptr) { first = ptr; };	//设置头结点的地址
	LinkNode<Type>* Search(Type x);						//搜索含数据x的元素
	LinkNode<Type>* Locate(int i);						//搜索出第i个元素的地址
	Type* getData(int i);								//得到的i个元素的值
	void setData(int i, Type& x);						//用x修改第i个元素的值
	bool Insert(int i, const Type& x);						//在第i个元素后面插入x
	bool Remove(int i, Type& x);						//删除第i个元素,x返回其值
	bool IsEmpty()const									//判断表是否为空
	{
		return first->link == NULL ? true : false;
	}
	bool IsFull()const { return false; }				//判断链表是否满了,直接返回false
	void Input(int num);								//输入
	void Output();										//输出
	List<Type>& operator=(const List<Type>& L);	//重载函数:赋值

	void push_back(const Type& x) {
		Insert(Length(), x);
	}
	void pop_back(Type& x) {
		Remove(Length(), x);
	}
};

//复制构造函数
template<class Type>List<Type>::List(const List<Type>& L)
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
template<class Type>bool List<Type>::Insert(int i, const Type& x)
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
template<class Type>List<Type>& List<Type>::operator=(const List<Type>& L)
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

/*Queue 队列类*/
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

#endif // !_QUEUE_H_

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
			return i.data - j.data;
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

/*Activities 关键活动类*/
#ifndef _AOE_NET_H_
#define _AOE_NET_H_
#define MAX_N 100
#define ERROR_EXIT_OUTPUT 0 

struct Edge {
	int fromVertex;
	int toVertex;	//到达的结点
	int weight;		//边的权重
	bool isKey;
	Edge(int from = -1, int to = -1, int val = 0,bool iskey=false)
		:fromVertex(from), toVertex(to), weight(val),isKey(iskey) {};
};
class AOE_Net {
private:
	int vertexNum, edgeNum;				//顶点数和边数【顶点编号从1开始】
	int minTime ;						//最短时间
	Vector<List<Edge>> adjacentList;	//邻接表
	Vector<List<Edge>> InadjacentList;	//逆邻接表
	Vector<int>inDegrees;				//存放所有点的入度
	Vector<int>TopoSequence;			//存放拓补序列

public:
	void Initialize();	//初始化AOE网络
	void GetTopoSequence();	//获得活动的拓补排序
	void CalculateTime();	//计算活动时间
	void OutputResult();	//输出结果

};
//初始化AOE网络
void  AOE_Net::Initialize()
{

	//输入点数和边数
	while (1) {
		cout << "请输入两个不超过" << MAX_N << "的正整数：";
		cin >> vertexNum >> edgeNum;
		if (cin.fail() || vertexNum > MAX_N || edgeNum > MAX_N || edgeNum <= 0 || vertexNum <= 0||vertexNum==1) {
			if (vertexNum == 1)
			{
				cout << "该图应该是有向无环图" << endl;
				exit(1);
			}
			cout << "输入错误！" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}


	inDegrees = Vector<int>(vertexNum + 1, 0);
	for (int i = 0; i <= vertexNum; ++i) {
		inDegrees[i] = 0;
		adjacentList.push_back(List<Edge>());
		InadjacentList.push_back(List<Edge>());
	}

	//输入边
	cout << "请输入" << edgeNum << "条边，交接点按照1~" << vertexNum << "编号，项目时间为小于" << MAX_N << "的正整数" << endl;
	int pos = 1, fromVertex, toVertex, value;
	while (pos <= edgeNum) {
		printf("第%3d条边：", pos);
		cin >> fromVertex >> toVertex >> value;
		if (fromVertex > vertexNum || fromVertex <= 0 || toVertex > vertexNum || toVertex <= 0 
			|| value <= 0 || value >= MAX_N||fromVertex==toVertex)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "该边输入错误，请重新输入" << endl;
			pos--;
		}
		else {
			inDegrees[toVertex]++;
			//将该边放入邻接表中
			adjacentList[fromVertex].Insert(0, Edge(fromVertex, toVertex, value));
			InadjacentList[toVertex].Insert(0, Edge(toVertex, fromVertex, value));
		}
		pos++;
	}

}
//获得活动的拓补排序序列
void AOE_Net::GetTopoSequence()
{
	//获得拓补排序
	LinkedQueue<int>TopoQueue;
	int count = 0;//用于判断是否成环
	//先将入度已经为0的放入队列
	for (int i = 1; i <= vertexNum; ++i) {
		if (inDegrees[i] == 0) {
			TopoQueue.EnQueue(i);
			TopoSequence.push_back(i);
			count++;
		}
	}
	//遍历表，直至所有点都在拓补序列中
	while (!TopoQueue.IsEmpty()) {
		int top = TopoQueue.DeQueue();
		for (int i = 1; i <= adjacentList[top].Length(); i++) {
			int to = adjacentList[top].getData(i)->toVertex;
			if (to == -1)
				break;
			inDegrees[to]--;
			if (inDegrees[to] == 0) {
				TopoQueue.EnQueue(to);
				TopoSequence.push_back(to);
				count++;
			}
		}
	}	
	//整个活动序列中存在环
	if (count != vertexNum) {
		cout << endl;
		cout << ERROR_EXIT_OUTPUT << endl;
		exit(1);
	}

}
//计算活动时间
void AOE_Net::CalculateTime()
{
	minTime = 0;
	//记录每个事件的时间：二维的,分别是ve/vl
	Vector<Vector<int>>VertexTime(1, Vector<int>(vertexNum + 1, 0));

	//计算ve:每个事件最早开始时间
	for (int i = 0; i < vertexNum; ++i) {
		int fromVertex = TopoSequence[i];
		for (int j = 1; j <= adjacentList[fromVertex].Length(); ++j) {
			int toVertex = adjacentList[fromVertex].getData(j)->toVertex;
			int value = adjacentList[fromVertex].getData(j)->weight;
			int temp = VertexTime[0][fromVertex] + value;
			if (temp > VertexTime[0][toVertex]) {
				VertexTime[0][toVertex] = temp;
			}
		}
	}

	//计算出最短所需要的时间
	for (int i = 1; i <= vertexNum; ++i)
		minTime = minTime > VertexTime[0][i] ? minTime : VertexTime[0][i];

	VertexTime.push_back(Vector<int>(vertexNum + 1, minTime));

	//计算vl：每个事件最晚开始时间
	for (int i = vertexNum-1; i >=0; --i) {
		int fromVertex = TopoSequence[i];
		for (int j = 1; j <= InadjacentList[fromVertex].Length(); ++j) {
			int toVertex = InadjacentList[fromVertex].getData(j)->toVertex;
			int value = InadjacentList[fromVertex].getData(j)->weight;
			int temp = VertexTime[1][fromVertex] - value;
			if (temp < VertexTime[1][toVertex]) {
				VertexTime[1][toVertex] = temp;
			}
		}
	}

	//计算活动的最早开始时间与最晚开始时间
	for (int i = 1; i < vertexNum; i++)
	{
		//实现同一起点的输出顺序为逆输入顺序
		for (int j = 1; j <= adjacentList[i].Length(); ++j)
		{
			Edge* temp = adjacentList[i].getData(j);
			int earlytime= VertexTime[0][temp->fromVertex];
			int latetime = VertexTime[1][temp->toVertex] - temp->weight;
			if (earlytime == latetime)
				adjacentList[i].getData(j)->isKey = true;
		}
	}

}
//输出结果
void AOE_Net::OutputResult()
{
	//输出
	cout << endl;
	cout << minTime << endl;
	//满足题目输出要求
	for (int i = 1; i <= vertexNum; i++)
	{
		//实现同一起点的输出顺序为逆输入顺序
		for (int j =1;j<= adjacentList[i].Length(); ++j)
		{
			Edge* temp = adjacentList[i].getData(j);
			if(temp->isKey==true)
			cout <<temp->fromVertex << "->" << temp->toVertex << endl;
		}
	}

}
#endif // !_AOE_NET_H_
