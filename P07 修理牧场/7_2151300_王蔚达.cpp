#include<iostream>
#include"7_2151300_王蔚达.h"
using namespace std;

#define MAX_PIECES_NUM 10000
#define MAX_NUM 100000

/***************************************
* 1.输入一共要切成的块数
* 2.输入每一块对应的花费
* 3.输出最小花费
****************************************/
int main()
{
	int pieces;
	//输入木块总数
	while (1) {
		cin >> pieces;
		if (pieces<=0 || pieces>MAX_PIECES_NUM || cin.fail()) {
			cout << "请输入一个不超过" << MAX_PIECES_NUM << "的正整数" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else break;
	}
	//建立优先队列
	PriorityQueue<int> PQueue(pieces);
	//若只需要一块木头则不需要再锯了
	//bool noCut = (pieces == 1);
	//获得每块木块的长度
	while (pieces--) {
		int num;
		cin >> num;
		if (num<0 || num>MAX_NUM || cin.fail()) {
			cout << "输入错误，程序退出！" << endl;
			return -1;
		}
		//进入队列中
		PQueue.push(num);
	}

	////一块木头不需要锯
	//if (noCut) {
	//	cout << "木头不需要锯，花费为0" << endl;
	//	return 0;
	//}
		
	//进行队列处理：取出两块最小的，放入求和后的
	int cost = 0;
	if (PQueue.size() == 1)	PQueue.pop(cost);
	while (PQueue.size() > 1) {
		int num1, num2, sum;
		PQueue.pop(num1);
		PQueue.pop(num2);
		sum = num1 + num2;
		PQueue.push(sum);
		cost += sum;
		//PQueue.Print();
	}
	cout << cost << endl;
}