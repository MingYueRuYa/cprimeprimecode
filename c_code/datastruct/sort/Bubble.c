#include <stdio.h>

int main(int argc, char *argv)
{
	int arr[5] = {2, 4, 5, 1, 3};
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5 - i; ++j) {
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
