#define _CRT_SECURE_NO_WARNINGS 
#include"Expression.h"
using namespace std;

#define MAX_EXPREESION_SIZE 20
#define MAX_LENGTH 128
enum CHAR_TYPE { INGNORE, DIGIT, OPERATOR, DOT };


//得到栈内优先级,数字越大越先进栈
int getInStackPriority(char ch) {
	switch (ch) {
	case'#':return 0;
	case'(':return 1;
	case'*':
	case'/':
	case'%':return 5;
	case'+':
	case'-':return 3;
	case')':return 6;
	default:return -1;
	}
}
//得到栈外优先级,数字越大越先出栈
int getInComingPriority(char ch) {
	switch (ch) {
	case'#':return 0;
	case'(':return 6;
	case'*':
	case'/':
	case'%':return 4;
	case'+':
	case'-':return 2;
	case')':return 1;
	default:return -1;
	}
}
//判断字符的类型
CHAR_TYPE getCharType(char ch) {
	if (ch >= '0' && ch <= '9')
		return DIGIT;
	else if (ch == '#' || ch == '(' || ch == ')' || ch == '*' || ch == '/' || ch == '%' || ch == '+' || ch == '-')
		return OPERATOR;
	else if (ch == '.')
		return DOT;
	else
		return INGNORE;
}
//读入字符串，并初步判断是否输入正确
void getInput(String& res) {
	while (1) {
		cout << "请输入一个长度不超过" << MAX_EXPREESION_SIZE << "的中缀表达式:" << endl;
		res.clear();

		char input[MAX_LENGTH];
		cin.getline(input, MAX_LENGTH);
		cout << endl << "输入的中缀表达式为：";
		cout << input << endl;

		int size = 0;
		for (; size < MAX_LENGTH; size++)
			if (input[size] == '\0')break;
		//match用于观察括号是否匹配，cnt用于计数，fail看是否有非法字符，error检查两个符号相连
		int match = 0, cnt = 0, j = 0;
		bool fail = 0, error = 0;
		bool reNumber = 0;//检测数值连续出现两次

		res[j++] = '#';
		for (int i = 0; i < size; ++i) 
		{
			//括号匹配
			if (input[i] == '(') match++;
			if (input[i] == ')') match--;
			if (getCharType(input[i]) != INGNORE) {
				//数字情况
				if (getCharType(input[i]) == DIGIT) {
					//处理数值连续出现两次
					while (getCharType(input[i]) == DIGIT || getCharType(input[i]) == DOT) {
						res[j++] = input[i];
						cnt++;
						i++;
					}
					if (input[i] == ' ' && getCharType(input[i + 1]) == DIGIT) {
						reNumber = true;
						break;
					}
					else
						i--;
				}
				//操作符情况
				else {
					cnt++;
					res[j++] = input[i];
				}

			}
			else if (input[i] != ' ')
				fail = 1;
			if (i < size - 1 && (getCharType(input[i]) == OPERATOR && input[i] != '(' && input[i] != ')')
				&& (getCharType(input[i + 1]) == OPERATOR && input[i + 1] != '(' && input[i + 1] != ')'))
				error = 1;//处理连续输入两个非括号运算符的情况
			
		}
		res[j++] = '#';
		res[j] = '\0';
		if (match)
			cout << "输入的括号不匹配！请重新输入！" << endl;
		else if (fail)
			cout << "输入的表达式中有无效字符！请重新输入！" << endl;
		else if (error)
			cout << "输入的表达式中有两个非括号运算符连着的情况！请重新输入！" << endl;
		else if (cnt > MAX_EXPREESION_SIZE || cnt == 0)
			cout << "输入的表达式不符合要求！请重新输入！" << endl;
		else if (reNumber)
			cout << "输入的表达式中有两个数连着！请重新输入！" << endl;
		else break;
	}
}
//将中缀表达式转化成后缀表达式，并输出
void TransIntoPostfix(String input, String& output)
{
	Stack<char> stack;
	char top_op, cur_op;
	stack.Push('#');//栈底放入一个'#'作为标记

	int pos = 1;
	for (; stack.IsEmpty() == false; pos++) {
		//处理输入是数字的情况
		if (getCharType(input[pos]) == DIGIT) {
			for (; getCharType(input[pos]) != OPERATOR; pos++)//处理小数的情况
			{
				output = output + input[pos];
				cout << input[pos];
			}
			cout << ' ';
			output = output + ' ';
			pos--;//下一次是运算符进栈
		}
		//处理输入是操作符的情况
		else {
			top_op = stack.getTop();
			cur_op = input[pos];
			//处理单目运算符'-'考虑负号及取反情况
			if (cur_op == '-' && (input[pos - 1] == '#' || input[pos - 1] == '(') && (input[pos + 1] >= '0' && input[pos + 1] <= '9')) {
				output = output + cur_op;
				cout << cur_op;
				continue;
			}
			//处理单目运算符'+'
			if (cur_op == '+' && (input[pos - 1] == '#' || input[pos - 1] == '('))
				continue;
			//栈内小于栈外优先级,进栈
			if (getInStackPriority(top_op) < getInComingPriority(cur_op))
				stack.Push(cur_op);
			//栈内大于栈外优先级，出栈
			else if (getInStackPriority(top_op) > getInComingPriority(cur_op)) {
				stack.Pop();
				output = output + top_op + ' ';
				cout << top_op << ' ';
				pos--;//下一轮依旧是这个运算符
			}
			//即出现左右括号栈内外的情况与两个#的情况
			else {
				stack.Pop();
				if (top_op == '(' && cur_op == ')');//则括号里面的已经处理完了，直接进下一个
				else break;//还剩下两个#的情况，直接栈空，退出
			}
		}
	}
	cout << '\b';//消除最后一个空格
	cout << endl;

}
//将字符串转化成整数
int stringToInt(String org)
{
	int res = 0;
	bool minusFlag = false;
	int i = 0;
	//单目运算符判断
	if (org[0] == '-') {
		minusFlag = true;
		i++;
	}
	else if (org[0] == '+') {
		i++;
	}
	//数值处理部分
	for (; i < org.Length(); ++i)
		res = res * 10 + (org[i] - '0');
	return minusFlag ? -res : res;
}
//将字符串转换成小数
double stringToDouble(String org)
{
	double res = 0, doublepart = 0;
	bool minusFlag = false;
	int i = 0;

	//单目运算符判断
	if (org[0] == '-') {
		minusFlag = true;
		i++;
	}
	else if (org[0] == '+') {
		i++;
	}
	//整数部分
	for (; i < org.Length(); ++i) {
		if (org[i] == '.')
			break;
		res = res * 10 + (org[i] - '0');
	}
	//小数部分
	for (int j = org.Length() - 1; j > i; j--) {
		doublepart = doublepart * 0.1 + (org[j] - '0') * 0.1;
	}
	res = res + doublepart;

	return minusFlag ? -res : res;
}
//计算后缀表达式的值
void CalculatePostfix(String input)
{
	//先将字符串分割成一个一个的String
	//用栈的结构，计算每一个的取值，之后入栈
	//直至数字栈中只有一个元素

	bool doubleFlag = false;
	double result;
	Stack<double> nums;
	for (int i = 0; i < input.Length(); ++i)
	{
		//数值
		if (getCharType(input[i]) == DIGIT || ((input[i] == '-' || input[i] == '+') && (i < input.Length() - 1 && getCharType(input[i + 1]) == DIGIT)))
		{
			String temp;
			//处理单目运算符
			if (input[i] == '-' || input[i] == '+')
				temp = temp + input[i++];
			for (; input[i] != ' ' && getCharType(input[i]) != OPERATOR; i++)//处理小数的情况
			{
				//是小数的情况
				if (getCharType(input[i]) == DOT)
					doubleFlag = true;
				temp = temp + input[i];
			}
			if (doubleFlag)
			{
				double tempNum = stringToDouble(temp);
				nums.Push(tempNum);
			}
			else
			{
				int tempNum = stringToInt(temp);
				nums.Push(tempNum);
			}

		}
		//运算符
		else if (getCharType(input[i]) == OPERATOR)
		{
			char cal = input[i];
			double right = nums.Pop();
			double left = nums.Pop();
			double res;
			switch (cal)
			{
			case '+':
				res = left + right;
				break;
			case '-':
				res = left - right;
				break;
			case '*':
				res = left * right;
				break;
			case '/':
				res = left / right;
				break;
			case '%':
				res = (int)(left) % (int)(right);
				break;
			}
			nums.Push(res);
			result = res;
		}
		//空格
		else;
	}

	result = nums.getTop();
	cout << result << endl;
}
/***********************************************
* 1.得到字符串（同时判断正误）
* 2.对字符串进行入栈和出栈处理
* 3.将处理结果输出，融合在2中
***********************************************/
int main()
{
	String input, output;

	getInput(input);
	cout << "对应的后缀表达式为：";
	TransIntoPostfix(input, output);
	cout << "计算结果为：";
	CalculatePostfix(output);
}
