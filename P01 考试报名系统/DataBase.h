#define _CRT_SECURE_NO_WARNINGS 

#include<string.h>
#include<iostream>
#include<assert.h>

using namespace std;

/*String 字符串类*/
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
	int f[MAX_LENGTH];
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
#endif  // ! _STRING_H_

/*List 链表类*/
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
	bool Insert(int i, const Type& x);					//在第i个元素后面插入x
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


#endif // !_SINGLELIST_H_

/*RBTree 红黑树类*/
#ifndef _RBTREE_H_
#define _RBTREE_H_

//颜色
enum Color
{
	RED,
	BLACK,
};
template<class KeyType, class ValType>
struct RBTreeNode
{
	RBTreeNode<KeyType, ValType>* _left;	//左指针
	RBTreeNode<KeyType, ValType>* _right;	//右指针
	RBTreeNode<KeyType, ValType>* _parent;	//双亲指针
	KeyType _key;							//关键比较字
	ValType _data;							//数据
	Color _color;							//结点颜色

	RBTreeNode(const KeyType key, const ValType data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _key(key)
		, _data(data)
		, _color(RED)
	{}
};

template<class KeyType, class ValType>
class RBTree
{
	typedef RBTreeNode<KeyType, ValType> Node;
private:
	Node* _root;//红黑树的根节点
public:
	int curSize;//红黑树的大小(其中结点的个数)

	RBTree() :_root(nullptr), curSize(0) {}				//构造函数
	~RBTree() { _Destory(_root); }						//析构函数

	Node* Find(const KeyType& key);						//查找结点所在位置
	bool Insert(const KeyType key, const ValType data);	//插入结点
	void OutPut();										//打印所有结点，中序遍历

	bool IsRBTree();									//判断是否满足红黑树
	bool IsEmpty() { return _root == nullptr; }			//判断红黑树是否为空
	bool Erase(const KeyType& key);						//删除某一个结点

private:
	void RotateL(Node* parent);							//单左旋
	void RotateR(Node* parent);							//单右旋
	bool _IsRBTree(Node* root, int blacknum, int count);//用于递归判断是否满足红黑树要求
	void _Destory(Node*& root);							//用于递归释放结点析构
	void _OutPut(Node* cur);							//用于递归打印所有结点

};

/************************************************
* 红黑树的规则：
* 1. 结点只有红黑两色
* 2. 根节点为黑色
* 3. 叶结点(NULL处)为黑色
* 4. 路径上没有两个相邻的红色结点
* 5. 每个结点到叶结点的所有路径都包含相同数目的黑色结点
************************************************/
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::IsRBTree()
{
	//头结点是空结点，则是红黑树
	if (_root == nullptr)
	{
		return true;
	}
	//检查是否满足条件2：根节点不能为红色
	if (_root->_color == RED)
	{
		cout << "根节点为红色" << endl;
		return false;
	}

	//检查是否满足条件5：计算根节点到每一个叶结点的距离相同
	int BlackNum = 0;	//路径上黑色结点的数目
	Node* cur = _root;
	while (cur)
	{
		if (cur->_color == BLACK)
			BlackNum++;
		cur = cur->_left;
	}

	int count = 0;
	return _IsRBTree(_root, BlackNum, count);
}
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::_IsRBTree(Node* root, int blacknum, int count)
{
	//检查是否满足条件5：遍历结束，路径上黑节点数目相同
	if (root == nullptr)
	{
		if (blacknum == count)
			return true;
		cout << "各路径上黑色节点个数不同" << endl;
		return false;
	}
	//检查是否满足条件4：路径上没有两个相邻的红色结点
	if (root->_color == RED && root->_parent->_color == RED)
	{
		cout << "存在连续红色节点" << endl;
		return false;
	}

	if (root->_color == BLACK)
		count++;

	//递归遍历，依次遍历其左右子树，均为1才为true
	return _IsRBTree(root->_left, blacknum, count) && _IsRBTree(root->_right, blacknum, count);
}

//用于递归释放结点析构
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::_Destory(Node*& root)
{
	//采用后续遍历，释放结点
	if (root == nullptr)
		return;

	_Destory(root->_left);
	_Destory(root->_right);

	delete root;
	root = nullptr;
}
//单左旋：逆时针旋转红黑树的两个结点，使得父结点被自己的右孩子取代，而自己成为自己的左孩子
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::RotateL(Node* parent)
{
	Node* subRight = parent->_right;
	Node* subRightLeft = subRight->_left;
	Node* parentP = parent->_parent;


	parent->_right = subRightLeft;
	if (subRightLeft)
		subRightLeft->_parent = parent;

	subRight->_left = parent;
	parent->_parent = subRight;

	if (parent == _root) {
		_root = subRight;
		subRight->_parent = nullptr;
	}
	else {
		subRight->_parent = parentP;
		if (parentP->_left == parent)
			parentP->_left = subRight;
		else
			parentP->_right = subRight;
	}
}
//单右旋：顺时针旋转红黑树的两个结点，使得父结点被自己的左孩子取代，而自己成为自己的右孩子
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::RotateR(Node* parent)
{
	Node* subLeft = parent->_left;
	Node* subLeftRight = subLeft->_right;
	Node* parentP = parent->_parent;


	parent->_left = subLeftRight;
	if (subLeftRight)
		subLeftRight->_parent = parent;

	subLeft->_right = parent;
	parent->_parent = subLeft;

	if (parent == _root) {
		_root = subLeft;
		subLeft->_parent = nullptr;
	}
	else {
		subLeft->_parent = parentP;
		if (parentP->_left == parent)
			parentP->_left = subLeft;
		else
			parentP->_right = subLeft;
	}
}
/************************************************
* 查找结点所在位置
* 遍历查找树，左边比它小，右边比它大
************************************************/
template<class KeyType, class ValType>
inline RBTreeNode<KeyType, ValType>* RBTree<KeyType, ValType>::Find(const KeyType& key)
{
	Node* cur = _root;
	while (cur != nullptr)
	{
		if (cur->_key > key)
			cur = cur->_left;
		else if (cur->_key < key)
			cur = cur->_right;
		else
			return cur;
	}
	return nullptr;
}

/************************************************
* 插入结点：
* 基本过程：①初始为红色 ②插入成为叶子 ③调整树形
* 1. 是根节点：由红变黑即可
* 2. 父节点是黑色：直接插入
* 3. 父节点是红色，叔结点是红色：父节点和叔结点变黑，爷结点变红，问题转移至爷结点
* 4. 父节点是红色，叔结点是黑色，其方向为LL/RR：父节点变成爷结点，交换两者的颜色
* 5. 父节点是红色，叔结点是黑色，其方向为LR/RL：调整方向至LL/RR，转化成情况4
************************************************/
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::Insert(const KeyType key, const ValType data)
{
	//情况1：空树的情况：将结点染成黑色即可
	if (_root == nullptr)
	{
		_root = new Node(key, data);
		_root->_color = BLACK;
		curSize++;
		return true;
	}

	//查找位置插入节点：parent为要插入位置的双亲结点
	Node* cur = _root, * parent = _root;
	while (cur)
	{
		if (cur->_key > key) {
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_key < key) {
			parent = cur;
			cur = cur->_right;
		}
		//关键字相同则不插入
		else
			return false;
	}

	//在cur处创建链接节点
	cur = new Node(key, data);
	if (parent->_key > key)
		parent->_left = cur;
	else
		parent->_right = cur;
	cur->_parent = parent;

	//情况2：直接插入，退出
	if (parent->_color == BLACK) {
		curSize++;
		return true;
	}


	//情况3/4/5：父节点存在且为红，则需要调整
	while (parent && parent->_color == RED)
	{
		//此时当前节点一定有爷节点
		Node* granparent = parent->_parent;

		//具体调整情况主要看叔节点

		//父节点在爷结点的左边
		if (parent == granparent->_left)
		{
			Node* uncle = granparent->_right;
			//情况3：叔叔节点存在且为红，矛盾转移至爷结点
			if (uncle && uncle->_color == RED)
			{
				//修改颜色，继续向上检查
				granparent->_color = RED;
				parent->_color = uncle->_color = BLACK;

				cur = granparent;
				parent = cur->_parent;
			}
			else//情况4和5：叔叔节点不存在或者存在且为黑
			{
				//情况4：左单旋(三代节点为斜线)+变色
				if (cur == parent->_left) {
					RotateR(granparent);

					granparent->_color = RED;
					parent->_color = BLACK;
				}
				//情况5：双旋(三代节点为折线)+变色
				else {
					RotateL(parent);
					RotateR(granparent);
					cur->_color = BLACK;
					granparent->_color = RED;
				}
				//旋转后不需再向上调整了
				break;
			}
		}

		//父节点在爷结点的右边，实际操作与上面类似
		else
		{
			Node* uncle = granparent->_left;
			if (uncle && uncle->_color == RED)
			{
				parent->_color = uncle->_color = BLACK;
				granparent->_color = RED;

				cur = granparent;
				parent = cur->_parent;
			}
			else
			{
				if (cur == parent->_right) {
					RotateL(granparent);
					parent->_color = BLACK;
					granparent->_color = RED;
				}
				else {
					RotateR(parent);
					RotateL(granparent);
					cur->_color = BLACK;
					granparent->_color = RED;
				}
				break;
			}
		}
	}

	//确保根节点为黑
	_root->_color = BLACK;
	curSize++;
	return  true;
}
/************************************************
* 删除结点：
* 基本过程：①看孩子情况 ②看自己颜色 ③看兄弟颜色 ④看兄弟孩子红色分布情况 ⑤调整颜色
* 1. 有一个孩子：孩子变黑，孩子上位
* 2. 没有孩子，自己是红色：直接删除
* 3. 没有孩子，自己是黑，兄弟是黑，兄弟有同方向/两红子：兄弟上位，交换颜色，红子染黑，双黑减去一层黑
* 4. 没有孩子，自己是黑，兄弟是黑，兄弟有反方向红子：红子上位，交换颜色，转换成情况3
* 5. 没有孩子，自己是黑，兄弟是黑，兄弟没红子：兄弟变红，双黑脱去一层黑，父节点加上一层黑，问题转移至父节点
* 6. 没有孩子，自己是黑，兄弟是红：兄弟上位，交换颜色，返回情况3/4/5的其中一种情况
* 7. 有两个孩子：替换法删除，按照二叉搜索树，递归找到其直接后继，再处理那个点
************************************************/
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::Erase(const KeyType& key)
{
	//用于遍历二叉树
	Node* parent = nullptr;
	Node* cur = _root;
	//用于标记实际的待删除结点及其父结点
	Node* delParentPos = nullptr;
	Node* delPos = nullptr;

	//寻找待删除的结点
	while (cur)
	{
		if (key < cur->_key) //所给key值小于当前结点的key值
		{
			//往该结点的左子树走
			parent = cur;
			cur = cur->_left;
		}
		else if (key > cur->_key) //所给key值大于当前结点的key值
		{
			//往该结点的右子树走
			parent = cur;
			cur = cur->_right;
		}
		else //找到了待删除结点
		{
			//情况1：待删除结点的左子树为空
			if (cur->_left == nullptr)
			{
				if (cur == _root) //待删除结点是根结点
				{
					_root = _root->_right; //让根结点的右子树作为新的根结点
					if (_root != nullptr)
					{
						_root->_parent = nullptr;
						_root->_color = BLACK; //根结点为黑色
					}
					delete cur; //删除原根结点
					curSize--;
					return true;
				}
				else
				{
					delParentPos = parent; //标记实际删除结点的父结点
					delPos = cur; //标记实际删除的结点
				}
				break; //进行红黑树的调整以及结点的实际删除
			}
			//情况1：待删除结点的右子树为空
			else if (cur->_right == nullptr)
			{
				if (cur == _root) //待删除结点是根结点
				{
					_root = _root->_left; //让根结点的左子树作为新的根结点
					if (_root)
					{
						_root->_parent = nullptr;
						_root->_color = BLACK; //根结点为黑色
					}
					delete cur; //删除原根结点
					curSize--;
					return true;
				}
				else
				{
					delParentPos = parent; //标记实际删除结点的父结点
					delPos = cur; //标记实际删除的结点
				}
				break; //进行红黑树的调整以及结点的实际删除
			}
			//情况7：待删除结点有两个孩子：转移矛盾
			else
			{
				//寻找待删除结点右子树当中直接后继(key值最小的结点作为实际删除结点)
				Node* minParent = cur;
				Node* minRight = cur->_right;
				while (minRight->_left)
				{
					minParent = minRight;
					minRight = minRight->_left;
				}
				cur->_key = minRight->_key; //将待删除结点的key改为minRight的key
				cur->_data = minRight->_data; //将待删除结点的value改为minRight的value
				delParentPos = minParent; //标记实际删除结点的父结点
				delPos = minRight; //标记实际删除的结点
				break; //进行红黑树的调整以及结点的实际删除
			}
		}
	}

	//delPos没有被修改过，说明没有找到待删除结点
	if (delPos == nullptr)
		return false;

	//记录待删除结点及其父结点（用于后续实际删除）
	Node* del = delPos;
	Node* delP = delParentPos;

	//情况2：没有孩子，自己是红色，则直接删除
	if (delPos->_color == RED && delPos->_left == nullptr && delPos->_right == nullptr) {
		if (del == delP->_left) //实际删除结点是其父结点的左孩子
			delP->_left = nullptr;
		else //实际删除结点是其父结点的右孩子
			delP->_right = nullptr;
		delete del;
		curSize--;
		return true;
	}

	//删除的是黑色结点
	if (delPos->_color == BLACK)
	{
		//情况1续：待删除结点有一个红色的左孩子（不可能是黑色）
		if (delPos->_left)
		{
			//将这个红色的左孩子变黑即可
			delPos->_left->_color = BLACK;
		}
		//情况1续：待删除结点有一个红色的右孩子（不可能是黑色）
		else if (delPos->_right)
		{
			delPos->_right->_color = BLACK; //将这个红色的右孩子变黑即可
		}
		//情况3/4/5/6：待删除结点的左右均为空
		else
		{
			while (delPos != _root) //可能一直调整到根结点
			{
				//待删除结点是其父结点的左孩子
				if (delPos == delParentPos->_left)
				{
					//兄弟结点是其父结点的右孩子
					Node* brother = delParentPos->_right;
					//情况6：brother为红色
					if (brother->_color == RED)
					{
						delParentPos->_color = RED;
						brother->_color = BLACK;
						RotateL(delParentPos);
						//需要继续处理
						brother = delParentPos->_right; //更新brother（否则在本循环中执行其他情况的代码会出错）
					}
					//情况5：brother为黑色，且其左右孩子都是黑色结点或为空
					if (((brother->_left == nullptr) || (brother->_left->_color == BLACK))
						&& ((brother->_right == nullptr) || (brother->_right->_color == BLACK)))
					{
						brother->_color = RED;
						if (delParentPos->_color == RED)
						{
							delParentPos->_color = BLACK;
							break;
						}
						//需要继续处理
						delPos = delParentPos;
						delParentPos = delPos->_parent;
					}
					else
					{
						//情况4：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
						if ((brother->_right == nullptr) || (brother->_right->_color == BLACK))
						{
							brother->_left->_color = BLACK;
							brother->_color = RED;
							RotateR(brother);
							//需要继续处理
							brother = delParentPos->_right; //更新brother（否则执行下面情况四的代码会出错）
						}
						//情况3：brother为黑色，且其右孩子是红色结点
						brother->_color = delParentPos->_color;
						delParentPos->_color = BLACK;
						brother->_right->_color = BLACK;
						RotateL(delParentPos);
						break; //情况四执行完毕后调整一定结束
					}
				}
				//待删除结点是其父结点的右孩子(与上面类似)
				else
				{
					Node* brother = delParentPos->_left; //兄弟结点是其父结点的左孩子
					//情况6：brother为红色
					if (brother->_color == RED) //brother为红色
					{
						delParentPos->_color = RED;
						brother->_color = BLACK;
						RotateR(delParentPos);
						//需要继续处理
						brother = delParentPos->_left; //更新brother（否则在本循环中执行其他情况的代码会出错）
					}
					//情况5：brother为黑色，且其左右孩子都是黑色结点或为空
					if (((brother->_left == nullptr) || (brother->_left->_color == BLACK))
						&& ((brother->_right == nullptr) || (brother->_right->_color == BLACK)))
					{
						brother->_color = RED;
						if (delParentPos->_color == RED)
						{
							delParentPos->_color = BLACK;
							break;
						}
						//需要继续处理
						delPos = delParentPos;
						delParentPos = delPos->_parent;
					}
					else
					{
						//情况4：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
						if ((brother->_left == nullptr) || (brother->_left->_color == BLACK))
						{
							brother->_right->_color = BLACK;
							brother->_color = RED;
							RotateL(brother);
							//需要继续处理
							brother = delParentPos->_left; //更新brother（否则执行下面情况四的代码会出错）
						}
						//情况5：brother为黑色，且其左孩子是红色结点
						brother->_color = delParentPos->_color;
						delParentPos->_color = BLACK;
						brother->_left->_color = BLACK;
						RotateR(delParentPos);
						break; //情况四执行完毕后调整一定结束
					}
				}
			}
		}
	}

	//进行实际删除
	if (del->_left == nullptr) //实际删除结点的左子树为空
	{
		//实际删除结点是其父结点的左孩子
		if (del == delP->_left)
		{
			delP->_left = del->_right;
			if (del->_right)
				del->_right->_parent = delP;
		}
		//实际删除结点是其父结点的右孩子
		else
		{
			delP->_right = del->_right;
			if (del->_right)
				del->_right->_parent = delP;
		}
	}
	else //实际删除结点的右子树为空
	{
		//实际删除结点是其父结点的左孩子
		if (del == delP->_left)
		{
			delP->_left = del->_left;
			if (del->_left)
				del->_left->_parent = delP;
		}
		//实际删除结点是其父结点的右孩子
		else
		{
			delP->_right = del->_left;
			if (del->_left)
				del->_left->_parent = delP;
		}
	}
	delete del; //实际删除结点
	curSize--;
	return true;
}


template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::OutPut()
{
	_OutPut(_root);
}
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::_OutPut(Node* cur)
{
	if (cur == nullptr)
		return;
	_OutPut(cur->_left);
	cout << cur->_data;
	_OutPut(cur->_right);

}






#endif // !_RBTREE_H_

/*DataBase 数据库类*/
#ifndef _DATABASE_H_ 
#define _DATABASE_H_

#define MAX_INT 10000000

enum GENDER
{
	GENDER_MALE,
	GENDER_FEMALE
};
class Student
{
private:
	int _id;
	String _name;
	int _gender; //使用枚举可以便于理解
	int _age;
	String _kind;

public:
	Student() : _id(0), _name(), _gender(0), _age(0), _kind() {}
	~Student() {}
	int getID() const { return _id; }
	String getName() const { return _name; }
	int getGender() const { return _gender; }
	int getAge() const { return _age; }
	String getKind() const { return _kind; }

	void CheckInput_Int(int& num, String info);
	void CheckInput_Gender(int& gender);
	friend istream& operator>>(istream& is, Student& student);
	friend ostream& operator<<(ostream& os, const Student& student);

	friend class RBT_DataBase;
	template <class Type>
	friend class List;

	void operator=(Student& ob)
	{
		_id = ob.getID();
		_name = ob.getName();
		_gender = ob.getGender();
		_age = ob.getAge();
		_kind = ob.getKind();
	};
};
void Student::CheckInput_Int(int& num, String info)
{
	bool fail = 0;
	while (true)
	{
		cin >> num;
		if (cin.fail() || num < 0 || num >= MAX_INT)
		{
			cout << info << "输入错误，"
				<< "请输入一个小于" << MAX_INT << "正整数！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			fail = 1;
		}
		else if (fail == 1)
		{
			cout << "请重新输入后续信息" << endl;
			break;
		}
		else
			break;
	}
}
void Student::CheckInput_Gender(int& gender)
{
	while (true)
	{
		String instr;
		cin >> instr;
		if (instr == "男")
		{
			_gender = GENDER_MALE;
			break;
		}
		else if (instr == "女")
		{
			_gender = GENDER_FEMALE;
			break;
		}
		cout << "性别信息输入错误,请重新输入男或女，并重新输入后续信息。" << endl;
		cin.ignore(65536, '\n');
	}

}
istream& operator>>(istream& is, Student& student)
{

	student.CheckInput_Int(student._id, "考号");
	is >> student._name;
	student.CheckInput_Gender(student._gender);
	student.CheckInput_Int(student._age, "年龄");
	is >> student._kind;
	//清空缓冲区，避免因为输入过多对于后续的影响
	cin.ignore(65535, '\n');

	return is;
}
ostream& operator<<(ostream& os, const Student& student)
{
	//格式化输出
	printf("%-10d%-10s%-10s%-10d%-14s\n", student._id, student._name.getString(),
		(student.getGender() == GENDER_MALE ? "男" : "女"), student._age, student._kind.getString());
	return os;
}


#ifndef _RBT_DATABASE_
#define _RBT_DATABASE_
class RBT_DataBase
{
private:
	//就是单链表的表头
	RBTree<int, Student> table;
	int gender[2] = { 0,0 };
public:
	RBT_DataBase() {};
	~RBT_DataBase() {};

	void Initialise();//完成对信息表的建立
	void PrintTable();//打印信息表

	void Insert();//按键1：输入一个位置，在该位置插入考生信息
	void Delete();//按键2：删除该考号的学生
	void Search();//按键3：查找该人信息
	void Change();//按键4：根据考号修改考生信息
	void Census();//按键5：统计，把所有人的信息输出来
	void Cancel();//按键0：取消操作

	void Wait();									//等待下一步指示
	bool IsRepeated(int ID);						//查看该考号是否重复了
	bool IsEmpty() { return table.IsEmpty(); }//看表是否空了
	int	Size() { return table.curSize; }			//计算系统中一共有几个考生
	void CheckInput_Int(int& num);					//检查输入的数字是否符合规定
};
//检查输入的数字是否符合规定
void RBT_DataBase::CheckInput_Int(int& num) {
	while (true) {
		cin >> num;
		if (cin.fail() || num < 0 || num >= MAX_INT) {
			cout << "请输入一个小于" << MAX_INT << "正整数！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
//完成对信息表的建立
void RBT_DataBase::Initialise()
{
	int num = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：" << endl;
	//循环输入，直到输入合理正整数
	CheckInput_Int(num);

	gender[GENDER_MALE] = gender[GENDER_FEMALE] = 0;

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	for (int i = 0; i < num; ++i) {
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID())) {
			cout << "该考号对应的考生已存在,请重新输入！" << endl;
			i--;//重新输入该元素
		}
		else {
			table.Insert(temp.getID(), temp);//还是从头结点的下一个节点开始
			gender[temp.getGender()]++;
		}

	}
	PrintTable();
}
//打印信息表
void RBT_DataBase::PrintTable()
{
	//打印横线的lambda函数	
	auto PrintLine = []() {
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "─";
		cout << endl;
	};
	if (table.IsEmpty()) { cout << "报名系统内暂无数据！\n"; }
	else {
		cout << endl;
		PrintLine();
		cout << "考号      姓名      性别      年龄      报考类别\n";
		PrintLine();

		table.OutPut();

		PrintLine();
	}
}
//按键1：输入一个位置，在该位置插入考生信息
void RBT_DataBase::Insert()
{
	while (true) {
		cout << "请输入该考生考号，姓名，性别，年龄及报考类别！" << endl;
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID()))
			cout << "该考号对应的考生已存在,请重新输入！" << endl;
		else {
			table.Insert(temp.getID(), temp);
			gender[temp.getGender()]++;
			break;
		}
	}

}
//按键2：删除该考号的学生
void RBT_DataBase::Delete()
{
	int ID;
	cout << "请选择您要删除的考生的考号：";
	CheckInput_Int(ID);
	if (ID == 0) { cout << "操作已取消" << endl; return; }
	if (IsEmpty()) {
		cout << "该表为空表，不能删除！" << endl;
		return;
	}
	if (!IsRepeated(ID))
	{
		cout << "找不到考号为 " << ID << " 的考生" << endl;
		return;
	}
	RBTreeNode<int, Student>* temp;
	cout << "您删除的考生信息是：";
	temp = table.Find(ID);
	gender[temp->_data.getGender()]--;
	cout << temp->_data;
	table.Erase(ID);
}
//按键3：查找该人信息
void RBT_DataBase::Search()
{
	cout << "请输入要查找的考生的考号：";
	int ID;
	CheckInput_Int(ID);
	if (ID == 0) { cout << "操作已取消" << endl; return; }
	//查找
	RBTreeNode<int, Student>* temp = table.Find(ID);
	if (temp == nullptr)
		cout << "查无此人!" << endl;
	else {
		cout << "考号      姓名      性别      年龄      报考类别" << endl;
		cout << temp->_data;
	}
}
//按键4：根据考号修改考生信息
void RBT_DataBase::Change()
{
	int ID;
	cout << "请选择您要修改的考生的考号：";
	CheckInput_Int(ID);
	if (ID == 0) { cout << "操作已取消" << endl; return; }
	//查找
	RBTreeNode<int, Student>* temp = table.Find(ID);
	if (temp == nullptr)
		cout << "查无此人!" << endl;
	else {
		cout << "考号      姓名      性别      年龄      报考类别\n";
		cout << temp->_data;
		gender[temp->_data.getGender()]--;
		cout << "请依次输入要修改的考生的考号，姓名，性别，年龄及报考类别！" << endl;
		Student change;
		cin >> change;
		if (change.getID() != ID) {
			if (table.Find(change.getID()) != nullptr) {
				cout << "考号已存在，此次修改错误" << endl;
				return;
			}
			table.Erase(ID);
			table.Insert(change.getID(), change);
		}
		else
			temp->_data = change;
		gender[change.getGender()]++;
	}
}
//按键5：统计，目前是把所有人的信息输出来
void RBT_DataBase::Census()
{
	//PrintTable();
	auto PrintLine = []() {
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "-";
		cout << endl;
	};
	cout << endl;
	PrintLine();
	cout << "考生总数：" << table.curSize << endl;
	PrintLine();
	cout << "性别统计：" << endl;
	cout << "男生总数：" << gender[GENDER_MALE] << endl;
	cout << "女生总数：" << gender[GENDER_FEMALE] << endl;
	PrintLine();
}
//按键0：取消操作
void RBT_DataBase::Cancel()
{
	cout << "该操作已经取消" << endl;
	Wait();
}
//查看该考号是否重复了
bool RBT_DataBase::IsRepeated(int ID)
{
	return table.Find(ID) != nullptr;
}
//等待下一步指示
void RBT_DataBase::Wait()
{
	cout << endl << "回车键继续操作" << endl;
	cin.clear();
	cin.ignore(1024, '\n');
	cin.get();
	return;
}
#endif // !_RBT_DATABASE_


#ifndef _LIST_DATABASE_
#define _LIST_DATABASE_
class List_DataBase
{
private:
	//就是单链表的表头
	List<Student> table;
	int gender[2] = { 0,0 };

public:
	List_DataBase() {};
	~List_DataBase() {};

	void Initialise(); //完成对信息表的建立
	void PrintTable(); //打印信息表

	void Insert(); //按键1：输入一个位置，在该位置插入考生信息
	void Delete(); //按键2：删除该考号的学生
	void Search(); //按键3：查找该人信息
	void Change(); //按键4：根据考号修改考生信息
	void Census(); //按键5：统计，把所有人的信息输出来
	void Cancel(); //按键0：取消操作

	void Wait();										   //等待下一步指示
	bool IsRepeated(int ID);							   //查看该考号是否重复了
	bool IsEmpty() { return (this->table.Length() == 0); } //看表是否空了
	int Size() { return table.Length(); }				   //计算系统中一共有几个考生
	int FindLocation(int ID);							   //根据ID找到对应考号的链表位置
	void CheckInput_Int(int& num);						   //检查输入的数字是否符合规定
};
//完成对信息表的建立
void List_DataBase::Initialise()
{
	int num = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：" << endl;
	//循环输入，直到输入合理正整数
	CheckInput_Int(num);

	gender[0] = gender[1] = 0;

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	for (int i = 0; i < num; ++i)
	{
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID()))
		{
			cout << "该考号对应的考生已存在,请重新输入！" << endl;
			i--; //重新输入该元素
		}
		else {
			table.Insert(i, temp); //还是从头结点的下一个节点开始
			gender[temp.getGender()]++;
		}
	}
	PrintTable();
}
//打印信息表
void List_DataBase::PrintTable()
{
	//打印横线的lambda函数
	auto PrintLine = []()
	{
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "─";
		cout << endl;
	};

	if (table.IsEmpty())
	{
		cout << "报名系统内暂无数据！\n";
	}
	else
	{
		cout << endl;
		PrintLine();
		cout << "考号      姓名      性别      年龄      报考类别\n";
		PrintLine();
		int num = Size();
		//一开始是头结点
		for (int i = 0; i < num; ++i)
		{
			cout << *table.getData(i + 1);
		}
		PrintLine();
	}
}
//按键1：输入一个位置，在该位置插入考生信息
void List_DataBase::Insert()
{
	cout << "请输入要插入的考生的位置：";
	int pos;
	int maxPos = Size();
	//输入处理，不能越界，可以取消操作
	while (true)
	{
		CheckInput_Int(pos);
		if (pos == 0)
		{
			cout << "操作已取消" << endl;
			return;
		}
		else if (pos <= 0 || pos > maxPos + 1)
		{
			cout << "该位置越界，输入的位置应该为不超过" << maxPos << "的正整数，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	while (true)
	{
		cout << "请输入该考生考号，姓名，性别，年龄及报考类别！" << endl;
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID()))
			cout << "该考号对应的考生已存在,请重新输入！" << endl;
		else
		{
			table.Insert(pos - 1, temp); //是插在pos-1个元素的后面
			gender[temp.getGender()]++;
			break;
		}
	}
}
//按键2：删除该考号的学生
void List_DataBase::Delete()
{
	int ID;
	cout << "请选择您要删除的考生的考号：";
	CheckInput_Int(ID);
	if (ID == 0)
	{
		cout << "操作已取消" << endl;
		return;
	}
	if (IsEmpty())
	{
		cout << "该表为空表，不能删除！" << endl;
		return;
	}
	if (!IsRepeated(ID))
	{
		cout << "找不到考号为 " << ID << " 的考生" << endl;
		return;
	}
	int loc = FindLocation(ID);
	Student temp;
	table.Remove(loc, temp);
	gender[temp.getGender()]--;
	cout << "您删除的考生信息是：";
	cout << temp;
}
//按键3：查找该人信息
void List_DataBase::Search()
{
	cout << "请输入要查找的考生的考号：";
	int ID;
	CheckInput_Int(ID);
	if (ID == 0)
	{
		cout << "操作已取消" << endl;
		return;
	}
	//查找
	LinkNode<Student>* ptr = table.getHead();
	while (ptr != NULL)
	{
		if (ptr->data.getID() == ID)
		{
			cout << "考号      姓名      性别      年龄      报考类别" << endl;
			cout << ptr->data;
			return;
		}
		ptr = ptr->link;
	}
	cout << "查无此人!" << endl;
}
//按键4：根据考号修改考生信息
void List_DataBase::Change()
{
	int ID;
	cout << "请选择您要修改的考生的考号：";
	CheckInput_Int(ID);
	if (ID == 0)
	{
		cout << "操作已取消" << endl;
		return;
	}
	int pos = FindLocation(ID);
	if (pos == 0)
	{
		cout << "找不到考号为 " << ID << " 的考生" << endl;
		return;
	}
	cout << "请依次输入要修改的考生的考号，姓名，性别，年龄及报考类别！" << endl;
	gender[table.getData(pos)->getGender()]--;
	Student temp;
	cin >> temp;
	if (FindLocation(temp.getID()) != 0) {
		cout << "考号已存在，此次修改错误" << endl;
		gender[temp.getGender()]++;
		return;
	}
	gender[temp.getGender()]++;
	table.setData(pos, temp);
}
//按键5：统计，目前是把所有人的信息输出来
void List_DataBase::Census()
{
	//PrintTable();
	auto PrintLine = []() {
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "-";
		cout << endl;
	};
	cout << endl;
	PrintLine();
	cout << "考生总数：" << table.Length() << endl;
	PrintLine();
	cout << "性别统计：" << endl;
	cout << "男生总数：" << gender[GENDER_MALE] << endl;
	cout << "女生总数：" << gender[GENDER_FEMALE] << endl;
	PrintLine();
}
//按键0：取消操作
void List_DataBase::Cancel()
{
	cout << "该操作已经取消" << endl;
	Wait();
}
//查看该考号是否重复了
bool List_DataBase::IsRepeated(int ID)
{
	LinkNode<Student>* ptr = table.getHead();
	while (ptr != NULL)
	{
		if (ptr->data.getID() == ID)
			return true;
		ptr = ptr->link;
	}
	return false;
}
//查找该元素出现的位置，若找不到则返回0
int List_DataBase::FindLocation(int ID)
{
	if (IsRepeated(ID) == 0)
	{
		return 0;
	}
	LinkNode<Student>* cur = table.getHead();
	int pos = 0;
	while (cur != NULL)
	{
		if (cur->data.getID() == ID)
		{
			return pos;
		}
		pos++;
		cur = cur->link; //少了这一句，陷入死循环
	}
	return 0;
}
//等待下一步指示
void List_DataBase::Wait()
{
	cout << endl
		<< "回车键继续操作" << endl;
	cin.clear();
	cin.ignore(1024, '\n');
	cin.get();
	return;
}
//检查输入的数字是否符合规定
void List_DataBase::CheckInput_Int(int& num)
{
	while (true)
	{
		cin >> num;
		if (cin.fail() || num < 0 || num >= MAX_INT)
		{
			cout << "请输入一个小于" << MAX_INT << "正整数！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
#endif // !_LIST_DATABASE_

#endif // !_DATABASE_H_