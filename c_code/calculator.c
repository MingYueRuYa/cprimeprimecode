/*
 *	简易计算器
 * */
#include <stdio.h>
#include <stdlib.h>


void test()
{
	printf("hello world!.\n");
}

void test01()
{
	printf("hello world!.\n");
}

void test02()
{
	printf("hello world!.\n");
}

int main()
{
	int num;
	if (EOF == scanf("%d",&num)) {
		printf("input number\n");
	} else if (0 == scanf("%d",&num)){
		printf("Please input correct number.\n");
	} else {
		printf("%d\n", num);
	}
	printf("%d\n", num);
	return 0;
}
