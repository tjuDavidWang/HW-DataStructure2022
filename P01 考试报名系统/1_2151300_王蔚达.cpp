#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "1_2151300_王蔚达.h"
using namespace std;

int main()
{
	//红黑树，有序数据库
	RBT_DataBase sStudentSystem;
	//单链表，无序数据库
	List_DataBase rStudentSystem;

	int type;

	//选择数据库排序类型
	while (1)
	{
		cout << "请输入学生系统考号排列类型(1为无序，2为有序)" << endl;
		cin >> type;
		if ((type != 1 && type != 2) || cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "输入错误" << endl;
		}
		else
			break;
	}

	//根据数据库类型的不同调用不同的库
	type == 1 ? rStudentSystem.Initialise() : sStudentSystem.Initialise();

	char operation;
	bool quit = false;
	while (!quit)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）\n\n";
		cout << "请选择您要进行的操作：";
		cin >> operation;
		//对应操作的6中选项
		switch (operation)
		{
		case '0':
			quit = true;
			cout << "操作已经取消，程序退出，以下为本次信息汇总结果！" << endl;
			break;
		case '1':
			type == 1 ? rStudentSystem.Insert() : sStudentSystem.Insert();
			break;
		case '2':
			type == 1 ? rStudentSystem.Delete() : sStudentSystem.Delete();
			break;
		case '3':
			type == 1 ? rStudentSystem.Search() : sStudentSystem.Search();
			break;
		case '4':
			type == 1 ? rStudentSystem.Change() : sStudentSystem.Change();
			break;
		case '5':
			type == 1 ? rStudentSystem.Census() : sStudentSystem.Census();
			break;
		default:
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "未知操作,请重新输入" << endl;
			break;
		}

		type == 1 ? rStudentSystem.PrintTable() : sStudentSystem.PrintTable();
		cout << "当前系统内共有 " << (type == 1 ? rStudentSystem.Size() : sStudentSystem.Size()) << " 条数据" << endl << endl;
	}

	return 0;
}