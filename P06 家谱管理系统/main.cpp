#define _CRT_SECURE_NO_WARNINGS 
#include"FamilyTree.h"
using namespace std;

int main()
{
	cout << "==================================================" << endl;
	cout << "**                 家谱管理系统                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA --- 完善家谱\t\t\t**" << endl;
	cout << "**\t\tB --- 添加家庭成员\t\t**" << endl;
	cout << "**\t\tC --- 解散局部家庭\t\t**" << endl;
	cout << "**\t\tD --- 更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE --- 退出程序\t\t\t**" << endl;
	cout << "==================================================" << endl;

	char operation;
	bool exitFlag = false;	//用于判断是否退出
	FamilyTree tree;		
	tree.InitializeTree();
	while (!exitFlag)
	{
		int faultFlag = false;//用于判断是否输入错误
		cout << endl << "请选择要执行的操作：";
		cin >> operation;
		switch (operation)
		{
		case 'A':
		case 'a':
			tree.BuildFamily();
			break;
		case 'B':
		case 'b':
			tree.AddFamilyMember();
			break;
		case 'C':
		case 'c':
			tree.DelFamily();
			break;
		case 'D':
		case 'd':
			tree.RenameFamilyMember();
			break;
		case 'E':
		case 'e':
			exitFlag = true;
			break;
		default:
			faultFlag = true;
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "请输入合法的执行操作符" << endl;
		}
		if (!faultFlag) {
			cout << endl;
			tree.Show();
		}
			
		if (exitFlag)
			cout << "程序已经退出..." << endl;
	}

	return 0;
}
