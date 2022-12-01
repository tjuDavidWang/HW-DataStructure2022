#include"Bank.h"
using namespace std;

#define MAX_N 1000

#define SPEED_A 2
#define SPEED_B 1


/**************************************************
* 1. 输入处理
* 2. 将编号是奇数的放到A，偶数的放到B，数字之间空格分隔
* 3. 先进先出，采用队列进行处理数据
**************************************************/

int main() {

	cout << "请输入一行正整数，第一个数字为顾客总数，之后的为N位客户的编号" << endl;

	int N, num;
	LinkedQueue<int>queueA, queueB;
	//总数N输入检查
	while (1) {
		cout << "输入：";
		cin >> N;
		if (N <= 0 || N > MAX_N || cin.fail()) {
			cout << "N为一个不超过" << MAX_N << "的正整数，请重新输入!" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else
			break;
	}
	//编号num输入检查
	for (int i = 0; i < N; ++i) {
		while (1) {
			cin >> num;
			if (num <= 0 || cin.fail()) {
				cout << "num为一个正整数，请重新输入所有编号!" << endl;
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else
				break;
		}
		//放入对应队列中
		if (num % 2 == 1)
			queueA.EnQueue(num);
		else
			queueB.EnQueue(num);
	}
	/*多种情况：
	* 1.每次出2个A，就进1个B,使用两个flag进行标记
	* 2.当A为空则直接出完B
	* 3.当B为空则直接出完A
	*/
	int flagA = 0, flagB = 0;
	cout << "输出：";
	for (int i = 0; i < N; ++i)
	{
		if (i != 0)cout << ' ';//最后一个编号不可以有空格
		if (queueA.IsEmpty()) {//A队列为空
			cout << queueB.DeQueue();
			continue;
		}
		if (queueB.IsEmpty()) {//B队列为空
			cout << queueA.DeQueue();
			continue;
		}
		if (flagA < SPEED_A) {//A队列未输出完2个
			cout << queueA.DeQueue();
			flagA++;
		}
		else if (flagA == SPEED_A) {
			if (flagB != SPEED_B) {
				cout << queueB.DeQueue();
				flagB++;
			}
			else {//即flagB==SPEED_B
				flagB = flagA = 0;		//标记置零，开始下一轮
				--i;
				cout << '\b';//本轮没有输出编号
			}
		}
	}
	cout << endl;

}