#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<chrono>
#include"Sort.h"
using namespace std;

#define MAX_NUM 100000000
#define MAX_SORT_NUM 10000

//默认排序结果为非递减的有序序列
/**************************************
* 1.读入产生随机数个数
* 2.构造随机数组：无序、顺序、逆序
* 3.进行不同的排序方法排序，输出结果
**************************************/

void Sort(int* arr, int num, const char* funcName, void(*sort)(int*, int, SortData&)) {

	//将arr中的元素复制给temp
	int* temp = new int[num];
	memcpy(temp, arr, num * sizeof(int));

	SortData data;

	printf("%-15s", funcName);

	//采用实际设计中常用库<chrono>来计算耗时
	auto start = chrono::steady_clock::now();

	sort(temp, num, data);

	auto end = chrono::steady_clock::now();
	chrono::duration<double, std::milli>elapsed = end - start;

	printf("\t%10.0lfms", elapsed.count());
	printf("\t%15lld", data.compareTimes);
	printf("\t%15lld\n", data.moveTimes);

	delete[]temp;


}
void SortProcess(int* arr, int num, const char* name) {
	cout << endl;
	cout << "===============================================================" << endl;
	cout << "**                         " << name << "                         **" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "算法名称                时间           比较次数        移动次数" << endl;
	if (num > MAX_SORT_NUM) {
		cout << "冒泡排序              已跳过" << endl;
		cout << "选择排序              已跳过" << endl;
		cout << "直接插入排序          已跳过" << endl;
		cout << "折半插入排序          已跳过" << endl;
	}
	else {
		Sort(arr, num, "冒泡排序", BubbleSort);
		Sort(arr, num, "选择排序", SelectSort);
		Sort(arr, num, "直接插入排序", straightInsertSort);
		Sort(arr, num, "折半插入排序", binaryInsertSort);
	}
	Sort(arr, num, "希尔排序", ShellSort);
	Sort(arr, num, "快速排序", QuickSort);
	Sort(arr, num, "堆排序", HeapSort);
	Sort(arr, num, "归并排序", MergeSort);
	Sort(arr, num, "计数排序", CountSort);
	Sort(arr, num, "MSD基数排序", MSDRadixSort);
	Sort(arr, num, "LSD基数排序", LSDRadixSort);
	cout << "===============================================================" << endl;


}

int main()
{
	//展示界面
	cout << "====================================================" << endl;
	cout << "**                  排序算法比较                  **" << endl;
	cout << "====================================================" << endl;
	cout << "**                  1.冒泡排序                    **" << endl;
	cout << "**                  2.选择排序                    **" << endl;
	cout << "**                  3.直接插入排序                **" << endl;
	cout << "**                  4.折半插入排序                **" << endl;
	cout << "**                  5.希尔排序                    **" << endl;
	cout << "**                  6.快速排序                    **" << endl;
	cout << "**                  7.堆排序                      **" << endl;
	cout << "**                  8.归并排序                    **" << endl;
	cout << "**                  9.计数排序                    **" << endl;
	cout << "**                  10.MSD基数排序                **" << endl;
	cout << "**                  11.LSD基数排序                **" << endl;
	cout << "====================================================" << endl;
	cout << endl;
	cout << "请输入要产生随机数的个数：";
	int num;
	while (1) {
		cin >> num;
		if (cin.fail() || num < 0 || num > MAX_NUM) {
			cout << "请输入一个不超过" << MAX_NUM << "的正整数" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else break;
	}

	int* arr = new int[num];
	GetArray _array;

	_array.randomArray(arr, num);
	cout << "含" << num << "个元素的随机序列已生成" << endl;

	SortProcess(arr, num, "随机序列");

	_array.ascendArray(arr, num);
	SortProcess(arr, num, "升序序列");

	_array.descendArray(arr, num);
	SortProcess(arr, num, "降序序列");



}
