#include <stdio.h>

int main(int argc, char *argv)
{
	int arr[5] = {2, 4, 5, 1, 3};
	for (int i = 0; i < 5; ++i) {
		//注意循环的次数 5 - i
		for (int j = 0; j < 5 - i; ++j) {
			//注意比较的对象，是相邻的位置
			if (arr[j] < arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	
	for (int i = 0; i < 5; ++i) {
		printf("%d ", arr[i]);
	}

	printf("\n");

	return 0;
}
