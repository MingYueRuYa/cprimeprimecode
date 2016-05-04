/*
 * array pointer
 * point array
 * */
#include <stdio.h>

int main(void)
{
	int array[2] = {1, 2};
	int *pArray[2] = {array, array + 1};
	int i;
	for (i = 0; i < 2; ++i) {
		printf("%d ", **(pArray + i));
	}
	int (*ppArrya)[2] = array;
	printf(" %d \n", *((*ppArrya)));
	printf(" %d \n", *((*ppArrya) + 1));
	//printf(" %d ", );
	return 0;
}
