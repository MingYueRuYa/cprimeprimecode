/****************************************************************
 **
 ** Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <stdio.h>

/*
 * 桶排序算法，一个数字就是一个桶用来占位，同样的数字就放到一个桶中
 * 桶的起始位置是从1开始算来的
 * */
void BucketSort(int *pArr, int pSize, int *pSortArr)
{
	if (NULL == pArr || NULL == pSortArr) {
		return;
	}
		
	for (int i = 0; i < pSize; ++i) {
		pSortArr[pArr[i]]++;
	}	
}

int main(int argc, char *argv[])
{
	int arr[10] = {1, 5, 2, 4, 6, 7, 8, 9, 10, 3};
	//桶的数量要比实际的数组容量多1，因为桶的位置要从1算起
	int sortarr[11] = {0};
	int size = sizeof(arr) / sizeof(int);
	BucketSort(arr, size, sortarr);

	for (int i = 0; i < 11; ++i) {
		//找出这个桶中存放了多少个同样的数字
		for (int j = 0; j < sortarr[i]; ++j) {
			printf("%d ", i);
		}
	}	
	printf("\n");

	return 0;
}

