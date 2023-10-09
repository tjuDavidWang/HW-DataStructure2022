#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <assert.h>
#include <iostream>
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
	void clear(); //清空字符串

	//运算符重载
	String& operator()(int pos, int len);
	int operator==(const String& ob) const { return strcmp(str, ob.getString()) == 0; }
	int operator!=(const String& ob) const { return strcmp(str, ob.getString()) != 0; }
	friend istream& operator>>(istream& in, String& instr);
	friend ostream& operator<<(ostream& out, String& outstr);
	int operator!() const { return Length() == 0; }

	String& operator=(const String& ob);
	String& operator=(char* ob);
	String operator+(char ch);
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
int String::Length() const
{
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
	delete[] str;
	maxLen = MAX_LENGTH;
	curLen = 0;
	str = new char[maxLen + 1];
	if (str == NULL)
	{
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
	else
	{
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
#endif // ! _STRING_H_

/*Stack链式栈类*/
#ifndef _STACK_H_
#define _STACK_H_

//链表结点类的定义
template <class Type>
struct LinkNode
{
	Type data;			  //数据域
	LinkNode<Type>* link; //链指针域
	//两种构造函数，看是否有数据对其进行初始化
	LinkNode(LinkNode<Type>* ptr = NULL) : link(ptr) {}
	LinkNode(const Type& item, LinkNode<Type>* ptr = NULL) : data(item), link(ptr) {}
};

//链式栈的定义:使用之前定义过的单链表
template <class Type>
class Stack
{
private:
	LinkNode<Type>* top; //栈顶指针
public:
	Stack() : top(NULL) {}	  //构造函数
	~Stack() { makeEmpty(); } //析构函数
	bool IsEmpty() const;	  //检查栈是否为空
	void makeEmpty();		  //将栈清空
	Type getTop() const;	  //得到栈顶元素

	void Push(const Type& x); //将元素压入栈顶
	Type Pop();				  //将栈顶元素弹出
	bool Pop(Type& x);		  //将栈顶元素弹出
	int size() const;		  //获得栈中元素的多少
};
//检查栈是否为空
template <class Type>
bool Stack<Type>::IsEmpty() const
{
	if (top == NULL)
		return true;
	else
		return false;
}
//获得栈中元素的多少
template <class Type>
int Stack<Type>::size() const
{
	LinkNode<Type>* ptr = top;
	int cnt = 0;
	while (top != NULL)
	{
		top = top->link;
		cnt++;
	}
	return cnt;
}
//将栈清空
template <class Type>
void Stack<Type>::makeEmpty()
{
	LinkNode<Type>* del;
	while (top != NULL)
	{
		del = top;
		top = top->link;
		delete del;
	}
}
//将元素压入栈顶
template <class Type>
void Stack<Type>::Push(const Type& x)
{
	top = new LinkNode<Type>(x, top); //将新进来的link指向top
	if (top == NULL)
	{
		cout << "存储分配错误！" << endl;
		exit(1);
	}
}
//将栈顶元素弹出
template <class Type>
Type Stack<Type>::Pop()
{
	if (IsEmpty() == true)
		exit(1);
	LinkNode<Type>* del = top;
	Type x = top->data;
	top = top->link;
	delete del;
	return x;
}
template <class Type>
bool Stack<Type>::Pop(Type& x)
{
	if (IsEmpty() == true)
		return false;
	LinkNode<Type>* del = top;
	top = top->link;
	x = del->data;
	delete del;
	return true;
}
//得到栈顶元素
template <class Type>
Type Stack<Type>::getTop() const
{
	if (IsEmpty() == true)
		exit(1);
	return top->data;
}

#endif // !_STACK_H_

/*FamliyTree二叉树类*/
#ifndef _FAMILY_H_
#define _FAMILY_H_

//森林节点
struct FamilyTreeNode
{
public:
	String name;
	int level;
	FamilyTreeNode* firstChild, * nextSibling;
	FamilyTreeNode(const String& name, int lv = 0, FamilyTreeNode* fc = NULL, FamilyTreeNode* ns = NULL)
		: name(name), level(lv), firstChild(fc), nextSibling(ns) {};

private:
	friend class FamilyTree;
};
//森林
class FamilyTree
{
private:
	FamilyTreeNode* root; //树的根节点
public:
	FamilyTree() : root(NULL) {};
	~FamilyTree() { DeleteFamilyTree(root); }
	void InitializeTree();	   //初始化家谱(创建祖先)--A
	void BuildFamily();		   //完善家谱--A
	void AddFamilyMember();	   //添加家庭成员--B
	void DelFamily();		   //局部解散家庭--C
	void RenameFamilyMember(); //更改家庭成员姓名--D
	void Show();			   //展示族谱
private:
	FamilyTreeNode* Search(const String& name) const; //查找对应成员位置
	void DeleteSubTree(FamilyTreeNode* ptr);		  //删除其子树
	void DeleteFamilyTree(FamilyTreeNode* ptr);		  //删除整棵树
};
void printChild(FamilyTreeNode* node)
{
	FamilyTreeNode* ptr = node->firstChild;
	while (ptr != NULL)
	{
		cout << ptr->name << " ";
		ptr = ptr->nextSibling;
	}
	cout << endl;
}
//查找对应成员位置,需要赋初始root值为根节点,返回NULL表示查无此人,前序遍历
FamilyTreeNode* FamilyTree::Search(const String& name) const
{
	Stack<FamilyTreeNode*> S;
	FamilyTreeNode* ptr;
	S.makeEmpty();
	ptr = root; //初始化
	while (ptr || !S.IsEmpty())
	{
		if (ptr)
		{
			if (ptr->name == name)
				return ptr;
			S.Push(ptr);
			ptr = ptr->firstChild;
		}
		else
		{
			S.Pop(ptr);
			ptr = ptr->nextSibling;
		}
	}
	return NULL;
}
//删除其子树
void FamilyTree::DeleteSubTree(FamilyTreeNode* curNode)
{
	FamilyTreeNode* ptr = curNode->firstChild;
	curNode->firstChild = NULL; //要先指向NULL否则会胡乱赋值
	if (ptr == NULL)
		return;
	else
	{
		while (ptr != NULL)
		{
			FamilyTreeNode* del = ptr;
			if (ptr->firstChild != NULL)
				return DeleteSubTree(ptr); //通过递归将其完全删除
			ptr = ptr->nextSibling;
			delete del;
		}
		return;
	}
}
//删除整棵树
void FamilyTree::DeleteFamilyTree(FamilyTreeNode* ptr)
{
	if (ptr == NULL)
		return;
	DeleteFamilyTree(ptr->firstChild);
	DeleteFamilyTree(ptr->nextSibling);
	delete ptr;
}
//初始化家谱--A
void FamilyTree::InitializeTree()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	String name;
	cin >> name;
	FamilyTreeNode* newNode = new FamilyTreeNode(name, 0);
	root = newNode;
	cout << "此家谱的祖先是：" << root->name << endl;
}
//完善家谱--A
void FamilyTree::BuildFamily()
{
	cout << "请输入要建立家庭的人的姓名：";
	String parent_name; //父亲节点
	cin >> parent_name;
	FamilyTreeNode* subFamily = Search(parent_name);
	if (subFamily == NULL)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	if (subFamily->firstChild != NULL) //该成员已经有了家庭
	{
		cout << "该成员已经建立过家庭！" << endl;
		return;
	}

	int children_num;
	cout << "请输入" << parent_name << "的儿女个数：";
	cin >> children_num;
	if (cin.fail() || children_num < 0)
	{
		cout << "请输入一个正整数！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		return;
	}
	cout << "请依次输入" << parent_name << "的儿女的姓名:";
	FamilyTreeNode* ptr = subFamily;
	bool isFirstChild = true;
	//输入child_num个孩子的名字
	while (children_num--)
	{
		String child_name;
		cin >> child_name;
		if (!Search(child_name))
		{
			FamilyTreeNode* newNode = new FamilyTreeNode(child_name, subFamily->level + 1);
			assert(newNode != NULL);
			if (isFirstChild)
			{
				ptr->firstChild = newNode;
				isFirstChild = false;
				ptr = ptr->firstChild;
			}
			else
			{
				ptr->nextSibling = newNode;
				ptr = ptr->nextSibling;
			}
		}
		else
		{
			cout << "姓名为" << child_name << "的成员已存在！" << endl; //没有再次插入
			return;
		}
	}
	cout << parent_name << "的第一代子孙是：";
	printChild(subFamily);
}
//添加家庭成员--B
void FamilyTree::AddFamilyMember()
{
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	String parent_name;
	cin >> parent_name;
	FamilyTreeNode* parent_point = Search(parent_name);
	if (parent_point == NULL)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}

	String new_child_name;
	cout << "请输入" << parent_name << "新添加儿子（或女儿）的姓名：";
	cin >> new_child_name;
	if (!Search(new_child_name))
	{
		FamilyTreeNode* newNode = new FamilyTreeNode(new_child_name, parent_point->level + 1);
		assert(newNode != NULL);
		FamilyTreeNode* ptr = parent_point->firstChild;
		if (ptr == NULL)
		{
			parent_point->firstChild = newNode;
		}
		else
		{
			while (ptr->nextSibling != NULL)
				ptr = ptr->nextSibling;
			ptr->nextSibling = newNode;
		}
		cout << parent_name << "的第一代子孙是：";
		printChild(parent_point);
	}
	else
		cout << "姓名为" << new_child_name << "的成员已存在！" << endl;
}
//局部解散家庭--C
void FamilyTree::DelFamily()
{
	cout << "请输入要解散家庭的人的姓名:";
	String parent_name;
	cin >> parent_name;
	FamilyTreeNode* parent_point = Search(parent_name);
	if (parent_point == NULL)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << parent_name << endl;
	if (parent_point->firstChild == NULL)
		cout << parent_name << "没有儿女" << endl;
	else
	{
		cout << parent_name << "的第一代子孙是：";
		printChild(parent_point);
		DeleteSubTree(parent_point);
	}
}
//更改家庭成员姓名--D
void FamilyTree::RenameFamilyMember()
{
	cout << "请输入要更改姓名的人的目前姓名：";
	String parent_name; //父亲节点
	cin >> parent_name;
	FamilyTreeNode* parent_point = Search(parent_name);
	if (parent_point == NULL)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	String parent_new_name;
	cin >> parent_new_name;
	if (Search(parent_new_name) == NULL)
	{
		parent_point->name = parent_new_name; //别忘了改名
		cout << parent_name << "已更名为" << parent_new_name << endl;
	}
	else
		cout << "姓名为" << parent_new_name << "的成员已存在！" << endl;
}
void FamilyTree::Show()
{
	//打印函数
	auto visit = [](FamilyTreeNode* temp, FamilyTreeNode* root)
	{
		bool isLast = temp->nextSibling == NULL;
		if (temp != root)
		{
			for (int i = 1; i < temp->level; i++)
				cout << "│   ";

			if (isLast)
				cout << "└── ";
			else
				cout << "├── ";
		}
		cout << temp->name << endl;
	};

	cout << "族谱如下：" << endl;
	Stack<FamilyTreeNode*> S;
	FamilyTreeNode* ptr;
	//前序遍历，打印内容
	S.makeEmpty();
	ptr = root; //初始化
	while (ptr || !S.IsEmpty())
	{
		if (ptr)
		{
			visit(ptr, root);
			S.Push(ptr);
			ptr = ptr->firstChild;
		}
		else
		{
			S.Pop(ptr);
			ptr = ptr->nextSibling;
		}
	}
}
#endif // !__FAMILY_H_
