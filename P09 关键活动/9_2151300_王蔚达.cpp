#include<iostream>
#include"9_2151300_王蔚达.h"
using namespace std;

/*********************************************
* 1.活动拓补排序,顺便得到其逆拓补排序
* 2.求出顶点的ve，vl，计算边的e,l
* 3.将l-e==0的输出
**********************************************/
int main() {
	AOE_Net solution;
	solution.Initialize();
	solution.GetTopoSequence();
	solution.CalculateTime();
	solution.OutputResult();
}