/****************************************************************
 **
 ** Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <stdio.h>

void QuickSort(int pFront, int pTear, int *pArr)
{
	//退出的条件
	if (pFront >= pTear || pFront < 0) {
		return;
	}

	//记录开始的头部，尾部的位置
	int front = pFront, tear = pTear;

	int keyvalue = pArr[pFront];
	while (pFront < pTear) {
		//从尾部开始，找出尾部的位置
		while (pFront < pTear) {
			if (pArr[pTear] >= keyvalue) {
				--pTear;	
			}	
			else {
				break;
			}
		}

		//从头部开始，找出头部的位置
		while (pFront < pTear) {
			if (keyvalue >= pArr[pFront]) {
				++pFront;
			}	
			else {
				break;
			}
		}
		
		int swapvalue = pArr[pFront];	
		if (pFront < pTear) {
			pArr[pFront] = pArr[pTear];
			pArr[pTear] = swapvalue;
		}
		else if (pFront == pTear) { //如果相遇了，则交换keyvalue与头(尾)的值，注意此时头和尾指向的位置是一样的
			pArr[pFront] = keyvalue;
			pArr[front] = swapvalue;
		}
		else {
			//TODO nothing to do.
		}
	}	

	QuickSort(0, pFront - 1, pArr);
	QuickSort(pFront + 1, tear, pArr);
}

int main(int argc, char *argv[])
{
	//int arr[10] = {5, 2, 3, 4, 1, 10, 9, 6, 8, 7};
	int arr[10] = {5, 5, 5, 5, 5, 50, 5, 5, 5, 5};
	//int arr[5] = {50, 5, 65, 5, 5};

	int front = 0, tear = sizeof(arr) / sizeof(int);

	printf("sort previous...\n");
	for (int i = 0; i < tear; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	QuickSort(front, tear - 1, arr);

	printf("sort behind...\n");
	for (int i = 0; i < tear; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
