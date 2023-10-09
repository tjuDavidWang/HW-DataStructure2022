#include<iostream>
using namespace std;
#include"2_2151300_王蔚达.h"
#define END_OF_INPUT -1
#define MAX_INT 10000000

//检查读入数据是否正确、序列是否读完
bool IsEndOfInput(int& num) {
	//检查是否输入正确
	while (true)
	{
		cin >> num;
		if (cin.fail() || num >= MAX_INT || (num <= 0 && num != END_OF_INPUT))
		{
			cout << "输入错误，" << "请输入一个小于" << MAX_INT << "正整数！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	//检查是否读到序列队尾
	if (num == END_OF_INPUT)
		return true;
	return false;
}
int main()
{
	List<int> inList1, inList2, outList;

	cout << "****************************************************" << endl;
	cout << "输入说明：" << endl
		<< "1. 输入分2行;" << endl
		<< "2. 分别在每行给出由若干个正整数构成的非降序序列;" << endl
		<< "3. 用-1表示序列的结尾;" << endl
		<< "4. 数字用空格间隔。" << endl;

	cout << "******************下面开始你的输入******************" << endl;
	
	int input_num;

	//读入两链表中的数据
	while (IsEndOfInput(input_num) == false) {
		inList1.push_back(input_num);
	}
	while (IsEndOfInput(input_num) == false) {
		inList2.push_back(input_num);
	}

	LinkNode<int>* ptr1 = inList1.getHead()->link;
	LinkNode<int>* ptr2 = inList2.getHead()->link;

	//求交集过程
	while (ptr1 != NULL && ptr2 != NULL) {
		if (ptr1->data == ptr2->data) {
			outList.push_back(ptr1->data);
			ptr1 = ptr1->link;
			ptr2 = ptr2->link;
		}
		else if (ptr1->data < ptr2->data)
			ptr1 = ptr1->link;
		else
			ptr2 = ptr2->link;
	}

	cout << "******************他们的交集如下********************" << endl;
	outList.Output();
	cout << endl;
}