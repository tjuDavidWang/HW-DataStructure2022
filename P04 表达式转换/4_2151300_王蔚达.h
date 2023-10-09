#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string.h>
using namespace std;

/*String字符串类*/
#ifndef _STRING_H_
#define _STRING_H_

using namespace std;
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
#endif

/*Stack栈类*/
#ifndef _STACK_H_
#define _STACK_H_

//链表结点类的定义
template <class Type>
struct LinkNode {
	Type data;				//数据域
	LinkNode<Type>* link;	//链指针域
	//两种构造函数，看是否有数据对其进行初始化
	LinkNode(LinkNode<Type>* ptr = NULL) :link(ptr) {}
	LinkNode(const Type& item, LinkNode<Type>* ptr = NULL) :data(item), link(ptr) {}
};

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

#endif // !_STACK_H_