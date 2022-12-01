#include<iostream>
#include"KeyActivity.h"
using namespace std;

int main() {
	AOE_Net solution;
	solution.Initialize();
	solution.GetTopoSequence();
	solution.CalculateTime();
	solution.OutputResult();
}