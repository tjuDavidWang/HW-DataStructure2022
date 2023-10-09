#ifndef _SORT_H_
#define _SORT_H_

#include <cstdlib>
#include <cstring>
#include <time.h>

namespace Opearation
{
	template <typename T>
	void swap(T& t1, T& t2)
	{
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
}

struct SortData
{
	long long moveTimes = 0;
	long long compareTimes = 0;
};

namespace Sequence
{

	//产生随机数组
	void randomArray(int* arr, int num, int seed = 0)
	{

		srand(seed != 0 ? seed : (unsigned int)(time(NULL)));
		for (int i = 0; i < num; i++)
		{
			arr[i] = rand() % num;
		}
	}
	//产生升序数组
	void ascendArray(int* arr, int num)
	{
		for (int i = 0; i < num; ++i)
			arr[i] = i;
	}
	//产生降序数组
	void descendArray(int* arr, int num)
	{
		for (int i = 0; i < num; ++i)
			arr[i] = num - i;
	}
	//产生同序数组
	void equalArray(int* arr, int num)
	{
		for (int i = 0; i < num; ++i)
			arr[i] = 0;
	}

};
/**********************
 * 冒泡排序
 ***********************/
void BubbleSort(int* arr, int num, SortData& data)
{
	bool disorderFlag = true; //如果false则未发生交换，此次有序，是有序的就直接跳出来结束
	for (int i = 0; i < num && disorderFlag; ++i)
	{
		// i从前往后，j从后往前，引入标识flag，查看是否已经有序
		disorderFlag = false;
		for (int j = num - 1; j > i; --j)
		{
			if (arr[j - 1] > arr[j])
			{
				Opearation::swap(arr[j - 1], arr[j]);
				data.moveTimes += 3;
				disorderFlag = true;
			}
			++data.compareTimes;
		}
	}
}
/**********************
 * 快速排序
 ***********************/
void quickSort(int* arr, int left, int right, SortData& data)
{
	if (left < right)
	{

		//采用三路取中对算法进行优化
		int ptrLeft = left, ptrRight = right;
		int mid = (left + right) / 2, smallestOfThree = left;
		if (arr[mid] < arr[smallestOfThree])
			smallestOfThree = mid;
		if (arr[right] < arr[smallestOfThree])
			smallestOfThree = right;
		if (smallestOfThree != right)
			Opearation::swap(arr[smallestOfThree], arr[right]); //三者最小值放到最右端
		if (arr[mid] < arr[left])
			Opearation::swap(arr[mid], arr[left]); //次小值放最左端

		//找到pivot应该放置的位置
		int pivot = arr[left]; // left位置为空缺,直接可以赋值
		while (ptrLeft < ptrRight)
		{

			while (ptrLeft < ptrRight && arr[ptrRight] >= pivot)
			{
				--ptrRight;
				++data.compareTimes;
			}
			arr[ptrLeft] = arr[ptrRight];
			++data.moveTimes;

			while (ptrLeft < ptrRight && arr[ptrLeft] <= pivot)
			{
				++ptrLeft;
				++data.compareTimes;
			}
			arr[ptrRight] = arr[ptrLeft];
			++data.moveTimes;

			data.compareTimes += 2;
		}
		arr[ptrLeft] = pivot;
		++data.moveTimes;

		// pivot左右分治
		quickSort(arr, left, ptrLeft - 1, data);
		quickSort(arr, ptrLeft + 1, right, data);
	}
}
void QuickSort(int* arr, int num, SortData& data)
{
	quickSort(arr, 0, num - 1, data);
}
/**********************
 * 直接插入排序
 ***********************/
void straightInsertSort(int* arr, int num, SortData& data)
{
	for (int i = 1; i < num; ++i)
	{
		if (arr[i] < arr[i - 1])
		{ //相当于是要调整的标记
			int temp = arr[i];
			++data.moveTimes;

			int j = i - 1;
			for (; j >= 0 && arr[j] > temp; --j)
			{ // j>=0要放在前面，可以直接跳过
				//向后挪位置
				arr[j + 1] = arr[j];
				++data.compareTimes;
			}
			++data.compareTimes;

			//复制到插入位置
			arr[j + 1] = temp;
			++data.moveTimes;
		}
	}
}
/**********************
 * 折半插入排序
 ***********************/
void binaryInsertSort(int* arr, int num, SortData& data)
{
	int mid, left, right;

	// i用于指示插入的元素原来的位置
	for (int i = 1; i < num; ++i)
	{
		int temp = arr[i];
		++data.moveTimes;

		//二分查找过程，最后应该插在right+1的位置
		left = 0;
		right = i - 1;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (arr[mid] > temp)
				right = mid - 1;
			else
				left = mid + 1;
			++data.compareTimes;
		}

		for (int j = i - 1; j >= left; --j)
		{
			arr[j + 1] = arr[j];
			++data.moveTimes;
		}

		arr[left] = temp;
		++data.moveTimes;
	}
}
/**********************
 * 希尔排序
 ***********************/
void ShellSort(int* arr, int num, SortData& data)
{
	//改变每一次分组的大小
	for (int gap = num / 2; gap >= 1; gap /= 2)
	{
		for (int i = gap; i < num; ++i)
		{
			if (arr[i] < arr[i - gap])
			{
				int temp = arr[i];
				++data.moveTimes;
				++data.compareTimes;

				int j = i - gap;
				for (; j >= 0 && arr[j] > temp; j -= gap)
				{
					++data.compareTimes;
					arr[j + gap] = arr[j];
					++data.moveTimes;
				}

				arr[j + gap] = temp;
				++data.moveTimes;
			} // if
		}	  // for (int i = step; i < num; ++i)
	}		  // for (int step = num / 2; step >= 1; step /= 2)
}
/**********************
 * 选择排序
 ***********************/
void SelectSort(int* arr, int num, SortData& data)
{
	for (int i = 0; i < num - 1; ++i)
	{ //最后一次可以不用再比较
		int minIndex = i;
		for (int j = i + 1; j < num; ++j)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
			++data.compareTimes;
		}
		if (minIndex != i)
		{
			Opearation::swap(arr[i], arr[minIndex]);
			data.moveTimes += 3;
		}
	}
}
/**********************
 * 堆排序
 ***********************/
template <class Type>
bool Compare_Max(Type a, Type b)
{
	return a > b;
}
typedef bool (*comp)(int, int);
static void FilterDown(int* heap, int end, int parent, SortData& data)
{ //堆调整(最大堆)
	comp Comp = Compare_Max;
	int child = 2 * parent + 1;
	while (child < end)
	{
		if (child + 1 < end)
		{
			++data.compareTimes;
			if (Comp(heap[child + 1], heap[child]))
				child++; // 找较大的子节点
		}
		++data.compareTimes;
		if (Comp(heap[parent], heap[child]))
			break;
		Opearation::swap(heap[parent], heap[child]);
		data.moveTimes += 3;
		parent = child;
		child = 2 * parent + 1;
	}
}
void HeapSort(int* heap, int num, SortData& data)
{
	//初始化堆,从倒数第二层(向上)开始修复
	for (int i = (num - 2) / 2; i >= 0; i--)
		FilterDown(heap, num, i, data);

	for (int i = num - 1; i > 0; i--)
	{

		Opearation::swap(heap[i], heap[0]); //把最大的与最后的交换位置
		data.moveTimes += 3;
		FilterDown(heap, i, 0, data); //调整剩下的堆
	}
}
/**********************
 * 归并排序
 ***********************/
void merge(int* temp, int* arr, int left, int mid, int right, SortData& data)
{
	for (int i = left; i <= right; ++i)
	{
		temp[i] = arr[i];
		++data.moveTimes;
	}
	int ptrLeft = left, ptrRight = mid + 1;
	int ptrRes = left;
	while (ptrLeft <= mid && ptrRight <= right)
	{
		++data.moveTimes;
		++data.compareTimes;
		if (temp[ptrLeft] <= temp[ptrRight])
			arr[ptrRes++] = temp[ptrLeft++];
		else
			arr[ptrRes++] = temp[ptrRight++];
	}
	while (ptrLeft <= mid)
	{
		arr[ptrRes++] = temp[ptrLeft++];
		++data.moveTimes;
	}
	while (ptrRight <= right)
	{
		arr[ptrRes++] = temp[ptrRight++];
		++data.moveTimes;
	}
}
void mergeSort(int* temp, int* arr, int left, int right, SortData& data)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(temp, arr, left, mid, data);
		mergeSort(temp, arr, mid + 1, right, data);
		merge(temp, arr, left, mid, right, data);
	}
	return;
}
void MergeSort(int* arr, int num, SortData& data)
{
	int* temp = new int[num];
	mergeSort(temp, arr, 0, num - 1, data);
	delete[] temp;
}
/**********************
 * 计数排序
 ***********************/
void CountSort(int* arr, int num, SortData& data)
{

	int max = arr[0], min = arr[0];
	for (int i = 1; i < num; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
		data.compareTimes += 2;
	}

	int* temp = new int[max - min + 1];
	memset(temp, 0, (max - min + 1) * sizeof(int)); //置零:头文件<cstring>

	for (int i = 0; i < num; ++i)
	{
		++temp[arr[i] - min];
		++data.moveTimes;
	}

	int pos = 0;
	for (int i = 0; i < max - min + 1; ++i)
	{
		while (temp[i])
		{
			arr[pos++] = i + min;
			--temp[i];
			++data.moveTimes;
		}
	}
}
/**********************
 * LSD基数排序[10进制]
 ***********************/
void LSDRadixSort(int* arr, int num, SortData& data)
{

	//求最大位数
	int maxDigit = 0, curMaxNum = arr[0];
	for (int i = 1; i < num; ++i)
	{
		if (arr[i] > curMaxNum)
			curMaxNum = arr[i];
	}
	while (curMaxNum)
	{
		curMaxNum /= 10;
		++maxDigit;
	}

	int radix = 1;
	int* count = new int[10];
	int* temp = new int[num];

	for (int i = 1; i <= maxDigit; ++i)
	{
		//分配前清空每个计数器
		memset(count, 0, 10 * sizeof(int));
		//统计每个桶中的记录数
		for (int j = 0; j < num; ++j)
		{
			int k = (arr[j] / radix) % 10;
			++count[k];
		}
		//分配temp中的位置(最右边)
		count[0] = count[0];
		for (int j = 1; j < 10; ++j)
			count[j] = count[j - 1] + count[j];
		//将元素放到对应的方块内
		for (int j = num - 1; j >= 0; --j)
		{
			int k = (arr[j] / radix) % 10;
			temp[--count[k]] = arr[j];
			++data.moveTimes;
		}
		//将temp中的元素赋值给arr准备下一轮的比较
		for (int j = 0; j < num; ++j)
		{
			arr[j] = temp[j];
			++data.moveTimes;
		}

		radix *= 10;
	}
}
/**********************
 * MSD基数排序[16进制]
 ***********************/
static int getDigitBase16(int x, int Digit)
{
	// Digit表示位数-1
	// y=Digit<<2   Digit*4,表示x要移动的位数
	// z=x>>y       表示x/(pow(2,y))
	// z&0xF        表示对除后的结果取模，求得余数

	return x >> (Digit << 2) & 0xF;
}
static void msdRadixSort(int* arr, int begin, int end, int maxDigit, const int radix, SortData& data)
{
	const int n = end - begin;

	//如果该桶中最多有1个数字/该桶中最大位数<0，则结束递归
	if (n <= 1 || maxDigit < 0)
		return;

	int* temp = new int[n];
	memset(temp, -1, n * sizeof(int));

	int* count = new int[radix]; //对应0-0xf的数组
	memset(count, 0, radix * sizeof(int));

	for (int i = begin; i < end; i++)
		++count[getDigitBase16(arr[i], maxDigit)];

	//分配temp中的位置(最右边)
	for (int i = 1; i < radix; i++)
		count[i] += count[i - 1];

	for (int i = begin; i < end; i++)
	{
		temp[--count[getDigitBase16(arr[i], maxDigit)]] = arr[i];
		++data.moveTimes;
	}

	//将temp赋值给arr[begin]及以后的位置
	memcpy(arr + begin, temp, n * sizeof(int));
	data.moveTimes += 2 * n;

	for (int i = 0; i < radix; i++)
	{
		int add = (i == radix - 1 ? n : count[i + 1]); //判断i是否是最后一个桶,来确定其末尾的位置
		//递归
		msdRadixSort(arr, begin + count[i], begin + add, maxDigit - 1, radix, data);
	}
	delete[] count;
	delete[] temp;
}

void MSDRadixSort(int* arr, int n, SortData& data)
{
	int curMaxNum = arr[0]; //数组中最大值
	int maxDigit = -1;		//最大位数-1

	//获得最大值
	for (int i = 1; i < n; i++)
		if (arr[i] > curMaxNum)
			curMaxNum = arr[i];

	//获得最大值16进制的位数
	while (curMaxNum)
	{
		curMaxNum >>= 4;
		maxDigit++;
	}

	msdRadixSort(arr, 0, n, maxDigit, 16, data);
}
#endif // !_SORT_H_
