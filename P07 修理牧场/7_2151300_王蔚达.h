#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include<iostream>
#include<assert.h>
using namespace std;

#define DefaultPQSize  10
namespace myCompare {
	template<class Type>bool Compare_Max(Type a, Type b) {
		return a > b;
	}
	template<class Type>bool Compare_Min(Type a, Type b) {
		return a < b;
	}
	//定义函数指针为comp，方便后续导入自己的排序方式
	typedef bool(*comp)(int, int);

}
namespace Heap {
	//自上而下的调整
	template<class Type>void FilterDown(int start, int curSize, Type* heap, myCompare::comp Comp)
	{

		int cur = start;
		int child = 2 * cur + 1;//j是i的左子
		Type temp = heap[cur];
		//保证是小根堆，每一个子树也是
		while (child < curSize)
		{
			//child不是指向最后一个结点,两子女中选小者
			if (child < curSize - 1 && Comp(heap[child + 1], heap[child])) 
				child++;
			if (Comp(temp, heap[child]))//head的值比pos小
				break;
			else //head的值比pos大
			{
				heap[cur] = heap[child];
				cur = child;

				child = 2 * child + 1;//pos转到它的左子上
			}
		}
		heap[cur] = temp;
	}
	//自下而上的调整
	template<class Type>void FilterUp(int start, Type* heap, myCompare::comp Comp) 
	{
		int cur = start, parent = (cur - 1) / 2;
		while (cur > 0) {
			if (Comp(heap[parent], heap[cur]))//parent<heap
				break;
			else {
				Type temp = heap[cur];
				heap[cur] = heap[parent];
				heap[parent] = temp;

				cur = parent;
				parent = (parent - 1) / 2;

			}
		}
	}
	//向堆中插入元素
	template<class Type>bool Insert(const Type& x, int& curSize, Type* heap, myCompare::comp Comp) 
	{
		heap[curSize] = x;
		FilterUp(curSize, heap, Comp);
		curSize++;
		return true;
	}
	//删除堆中元素
	template<class Type>bool Remove(Type& x, int& curSize, Type* heap, myCompare::comp Comp) 
	{
		if (curSize == 0) {
			cout << "堆已空" << endl;
			return false;
		}
		x = heap[0];
		heap[0] = heap[--curSize];//取最后一个填补到头上
		FilterDown(0, curSize, heap, Comp);//自上而下调整
		return true;
	}
}



template<class Type>
class PriorityQueue {
protected:
	Type* data;
	int maxSize;
	int curSize;
	myCompare::comp Compare;	//采用函数指针指示比较方式，默认是Min
public:
	PriorityQueue(int size = DefaultPQSize, bool (*Compare)(Type, Type) = myCompare::Compare_Min);
	~PriorityQueue() { delete[]data; }
	bool push(const Type& x);
	bool pop(Type& x);
	int size()const { return curSize; }

	bool getFront(Type& x)const;

	void makeEmpty() { curSize = 0; }
	bool IsEmpty() { return curSize == 0; }
	bool IsFull() { return curSize == maxSize; }
	void Print() {
		for (int i = 0; i < curSize; ++i)
			cout << data[i] << " ";
		cout << endl;
	}
};
template<class Type>PriorityQueue<Type>::PriorityQueue(int size, bool (*compare)(Type, Type))
	:maxSize(size), curSize(0), Compare(compare) {
	data = new Type[maxSize];
	assert(data != NULL);
}
template<class Type> bool PriorityQueue<Type>::push(const Type& x)
{
	if (IsFull())return false;
	Heap::Insert(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::pop(Type& x)
{
	if (IsEmpty())return false;
	Heap::Remove(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::getFront(Type& x) const
{
	if (IsEmpty())return false;
	x = data[0];
	return true;
}



#endif // !_PRIORITY_QUEUE_H_
