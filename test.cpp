#include <stdio.h>
#include <iostream>

int main()
{
	int a = 0["abc" + 53];
	printf("a = %d\n", a);
	printf("  %d\n", "abc" + 53);
	for (int i = 53; i < 63; i++) {
		printf("%d ", *("abc" + i));
	}
	int a1 = 3["abc" + 53];
	printf("a = %d\n", a1);
}
