#define _CRT_SECURE_NO_WARNINGS 
#include<string.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

/*String字符串类*/
#ifndef _STRING_H_
#define _STRING_H_

const int MAX_LENGTH = 128;

class String
{
private:
	int curLen;
	char* str;
	int maxLen;

public:
	String(const String& ob);
	String(const char* init);
	String();
	~String() { delete[] str; }
	int Length() const;
	char* getString() const { return str; } //访问私有成员,注意要使用const便于比较
	int getMaxLen() const { return maxLen; }
	int KMP_Find(String& pat) const;
	void clear();//清空字符串

	//运算符重载
	String& operator()(int pos, int len);
	int operator==(const String& ob) const { return strcmp(str, ob.getString()) == 0; }
	int operator!=(const String& ob) const { return strcmp(str, ob.getString()) != 0; }
	friend istream& operator>>(istream& in, String& instr);
	friend ostream& operator<<(ostream& out, String& outstr);
	int operator!() const { return Length() == 0; }

	String& operator=(const String& ob);
	String& operator=(char* ob);
	String operator +(char ch);
	String& operator+(const String& ob);
	String& operator+=(const char ch);
	String& operator+=(const String& ob);
	char& operator[](int i);
};
//复制构造函数，从已有串中复制
String::String(const String& ob)
{
	str = new char[MAX_LENGTH + 1];
	if (str == NULL)
	{
		cerr << "存储分配错误!" << endl;
		exit(1);
	}
	curLen = ob.Length();
	maxLen = ob.getMaxLen();
	strcpy(str, ob.getString());
}
//复制构造函数，从已有字符数组中复制
String::String(const char* init)
{
	str = new char[MAX_LENGTH + 1];
	if (str == NULL || strlen(init) > MAX_LENGTH)
	{
		cerr << "存储分配错误!" << endl;
		exit(1);
	}
	curLen = strlen(init);
	maxLen = MAX_LENGTH;
	strcpy(str, init); // strcpy是拷贝到'\0'自动停止的
}
//构造函数：创建一个空字符串
String::String()
{
	str = new char[MAX_LENGTH + 1];
	if (str == NULL)
	{
		cerr << "存储分配错误!" << endl;
		exit(1);
	}
	str[0] = '\0';
	curLen = 0;
	maxLen = MAX_LENGTH;
}
int String::Length() const {
	int len = 0;
	while (str[len] != 0)
		++len;
	return len;
}
int String::KMP_Find(String& pat) const
{
	int posP = 0, posT = 0; // P为子串，T为主串
	int lengthP = pat.Length(), lengthT = curLen;
	int f[MAX_LENGTH] = {};
	//计算失效函数
	if (1)
	{
		int lP = pat.Length();
		f[0] = -1;
		for (int j = 1; j < lP; ++j)
		{
			int i = f[j - 1];
			while (*(str + j) != *(str + i + 1) && i >= 0)
				i = f[i]; //递推
			if (*(str + j) == *(str + i + 1))
				f[j] = i + 1;
			else
				f[j] = -1;
		}
	}
	//进行子串的移动
	while (posP < lengthP && posT < lengthT)
	{
		if (pat[posP] == str[posT])
		{
			++posP;
			++posT;
		}
		else if (posP == 0)
			++posT;
		else
			posP = f[posP - 1] + 1;
	}
	if (posP < lengthP)
		return -1;
	else
		return posT - lengthP;
}
//清空字符串
void String::clear()
{
	delete[]str;
	maxLen = MAX_LENGTH;
	curLen = 0;
	str = new char[maxLen + 1];
	if (str == NULL) {
		cout << "内存分配错误！" << endl;
		exit(1);
	}
}
//运算符重载：截取字符串,从pos开始连续提取len个字符形成子串返回
String& String::operator()(int pos, int len)
{
	if (pos < 0 || pos + len - 1 > MAX_LENGTH || len < 0)
	{
		String* temp = new String;
		return *temp;
	}
	else
	{
		if (pos + len - 1 >= curLen)
			len = curLen - 1;
		char* ttemp = new char[MAX_LENGTH + 1];
		for (int i = 0, j = pos; i < len; ++i, ++j)
			ttemp[i] = str[j];
		ttemp[len] = '\0';
		String* temp = new String(ttemp);
		return *temp;
	}
}
//运算符重载：输入运算符
istream& operator>>(istream& in, String& instr)
{
	in >> instr.str;
	int len = 0;
	while (instr[len] != '\0')
		len++;
	instr.curLen = len;
	return in;
}
//运算符重载：输出运算符
ostream& operator<<(ostream& out, String& outstr)
{
	out << outstr.str;
	return out;
}
//运算符重载：将一个字符加到String上
String String::operator+(char ch)
{
	String res(*this);
	int len = res.Length();
	res[len] = ch;
	res[len + 1] = '\0';
	res.curLen++;
	return res;
}
//运算符重载：从已有串ob复制
String& String::operator=(const String& ob)
{
	if (&ob != this)
	{
		delete[] str;
		str = new char[MAX_LENGTH + 1];
		if (!str)
		{
			cerr << "内存不足!" << endl;
			exit(1);
		}
		curLen = ob.Length();
		strcpy(str, ob.getString());
	}
	else
		cout << "字符串自身赋值出错!" << endl;
	return *this;
}
//从char中赋值给字符串
String& String::operator=(char* ob)
{
	delete[] str;
	str = new char[MAX_LENGTH + 1];
	if (!str || strlen(ob) > MAX_LENGTH)
	{
		cerr << "内存不足!" << endl;
		exit(1);
	}
	else {
		strcpy(str, ob);
		curLen = Length();
	}
	return *this;
}
//运算符重载：将两个字符串合并，变成另一个字符串
String& String::operator+(const String& ob)
{
	curLen += ob.Length();
	char* ttemp = new char[MAX_LENGTH + 1];
	if (!ttemp)
	{
		cerr << "字符串下标越界!" << endl;
		exit(1);
	}
	strcpy(ttemp, str);
	strcpy(ttemp, ob.getString());
	String* temp = new String(ttemp);
	delete[] ttemp;
	return *temp;
}
//运算符重载：串连接
String& String::operator+=(const String& ob)
{
	char* temp = str;
	curLen += ob.Length();
	str = new char[MAX_LENGTH + 1];
	if (!str)
	{
		cerr << "字符串下标越界!" << endl;
		exit(1);
	}
	strcpy(str, temp);
	strcpy(str, ob.getString());
	delete[] temp;
	return *this;
}
String& String::operator+=(const char ch)
{
	char* temp = str;
	curLen++;
	str = new char[MAX_LENGTH + 1];
	if (!str)
	{
		cerr << "字符串下标越界!" << endl;
		exit(1);
	}
	strcpy(str, temp);
	strcpy(str, &ch);
	delete[] temp;
	return *this;
}
//运算符重载：按串名提取串中第i个字符
char& String::operator[](int i)
{
	if (i < 0 && i >= curLen)
	{
		cout << "字符串下标超界!" << endl;
		exit(1);
	}
	return str[i];
}
#endif // !_STRING_H_

/*Vector向量类*/
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
	if (data == ob.data)
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

/*Graph图类*/
#ifndef _GRAPH_H_
#define _GRAPH_H_
#define INF 100000
#define UNFOUND -1
//MST所用的结点以及adjacentList所存的边
struct Edge {
	int leftVertex;
	int rightVertex;	//到达的结点
	int weight;		//边的权重
	Edge(int from = -1, int to = -1, int val = 0) :leftVertex(from), rightVertex(to), weight(val) {};
};
//稠密图：边数比顶点数多
#ifndef _GRAPH_
#define _GRAPH_
class Graph
{
private:
	//顶点
	Vector<String> Vertex;
	//稠密，用邻接矩阵来储存边，邻接表，之后都用index代替String进行底层操作
	Vector<Vector<int>> Matrix;
	//Prim算法的最小生成树
	Vector<Edge> MSTree;
public:
	Graph() {};
	void CreateVertex();//创建电网顶点  --A
	void AddEdge();		//添加电网的边  --B
	void BuildMST();	//构建最小生成树--C
	void PrintMST();	//显示最小生成树--D
private:
	int findVertex(const String& vetex);//查看是否重复，不重复则返回
	void clear();//清楚整个图中所有内容
	void Prim(int index);//找到在Vertex中的坐标
	void NotConnectedCase(Vector<bool>visited);//没有完全连通的输出，输出已经连通和未连通的情况
	String& getName(int index) { return Vertex[index]; }
};
int Graph::findVertex(const String& vetex) {
	if (Vertex.IsEmpty())
		return UNFOUND;
	else {
		for (int i = 0; i != Vertex.size(); ++i) {
			if (Vertex[i] == vetex)
				return i;
		}
		return UNFOUND;
	}
}
void Graph::CreateVertex() {
	clear();
	int numVertex;
	cout << "请输入顶点的个数：";
	while (1) {
		cin >> numVertex;
		if (numVertex <= 0 || numVertex > INF || cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "顶点个数应该为不超过" << INF << "的正整数，请重新输入！" << endl;
		}
		else
			break;
	}
	cout << "请依次输入各顶点的名称：" << endl;
	for (int i = 0; i < numVertex; ++i)
	{
		String vertexName;
		cin >> vertexName;
		//判断是否已存在
		if (findVertex(vertexName) != UNFOUND) {
			cout << "顶点" << vertexName << "已存在！" << endl;
			i--;//重新输入该节点
		}
		else
			Vertex.push_back(vertexName);
	}
	Matrix = Vector<Vector<int>>(numVertex, Vector<int>(numVertex, INF));

}
void Graph::AddEdge() {
	String vertexA, vertexB;
	int edgeLength;
	while (true)
	{
		cout << "请输入两个顶点及边：";
		cin >> vertexA >> vertexB >> edgeLength;
		int indexA = findVertex(vertexA);
		int indexB = findVertex(vertexB);

		//停止读取条件
		if (edgeLength <= 0 || vertexA == "?" || vertexB == "?")
			break;

		if (indexA == -1) {
			cout << "顶点 " << vertexA << " 不存在" << endl;
			continue;
		}
		if (indexB == -1) {
			cout << "顶点 " << vertexB << " 不存在" << endl;
			continue;
		}
		if (edgeLength >= INF||edgeLength<=0) {
			cout << "边的权重应该是一个小于" << INF << "的正整数" << endl;
			continue;
		}
		if (edgeLength < Matrix[indexA][indexB]) {
			Matrix[indexA][indexB] = edgeLength;
			Matrix[indexB][indexA] = edgeLength;
		}

	}
}
void Graph::BuildMST()
{
	MSTree.clear();
	if (Vertex.size() == 1) {
		cout << "只含一个顶点，无需生成最小树！" << endl;
		return;
	}
	String startVertex;
	cout << "请输入起始顶点：";
	cin >> startVertex;
	int index = findVertex(startVertex);
	if (index == -1) {
		cout << "顶点 " << startVertex << " 不存在" << endl;
		return;
	}
	//开始生成最小树
	cout << endl;
	cout << "生成Prim最小树..." << endl;
	Prim(index);
}
void Graph::PrintMST()
{
	if (MSTree.size() != Vertex.size() - 1 || Vertex.size() == 1)
	{
		cout << "该图不连通，不能生成最小生成树" << endl;
		return;
	}
	else
	{
		cout << "最小生成树的顶点及边为：" << endl << endl;
		for (int i = 0; i < MSTree.size(); ++i)
			cout << getName(MSTree[i].leftVertex) << "-<" << MSTree[i].weight << ">->" << getName(MSTree[i].rightVertex) << '\t';
		cout << endl;
	}
}
void Graph::Prim(int index)
{
	int vertexNum = Vertex.size();
	Vector<bool>visited(vertexNum, false);
	Vector<int>distance(vertexNum, INF);
	Vector<int>nearVertex(vertexNum, index);

	distance[index] = 0;
	for (int i = 0; i < vertexNum; ++i) {
		//一开始是在哨兵位置
		int minIndex = index, minCost = INF;
		//找到到集合最近的点的位置
		for (int j = 0; j < vertexNum; j++) {
			if (visited[j] == false && distance[j] < minCost)
			{
				minIndex = j;
				minCost = distance[j];
			}

		}
		//设置为已访问，加入集合中
		visited[minIndex] = true;
		if (distance[minIndex] != 0 && distance[minIndex] != INF)
			MSTree.push_back({ nearVertex[minIndex],minIndex,distance[minIndex] });
		//更新所有点到集合的距离
		for (int i = 0; i < vertexNum; ++i) {
			int curVertex = i;
			int curWeight = Matrix[minIndex][i];
			if (distance[curVertex] > curWeight) {
				distance[curVertex] = curWeight;
				nearVertex[curVertex] = minIndex;
			}
		}
		if (distance[minIndex] == INF)
			break;

	}
	if (MSTree.size() != vertexNum - 1) {
		NotConnectedCase(visited);
	}
	else {
		cout << "生成完成！" << endl << endl;
	}

}
void Graph::NotConnectedCase(Vector<bool>visitedList)
{
	cout << "该图不连通！" << endl;
	cout << "这些结点已经连通：";
	for (int i = 0; i < visitedList.size(); ++i) {
		if (visitedList[i] == true)
			cout << getName(i) << " ";
	}
	cout << endl;
	cout << "这些结点尚未连通：";
	for (int i = 0; i < visitedList.size(); ++i) {
		if (visitedList[i] == false)
			cout << getName(i) << " ";
	}
	cout << endl;
}
void Graph::clear() {
	Vertex.clear();
	Matrix.clear();
	MSTree.clear();
}
#endif // !_GRAPH_
#endif // !_GRAPH_H_