
#include <stdio.h>

//example code, where is have leak memeory.

void test(int **pp)
{
	*pp = (int *)malloc(sizeof(int));
	printf("test %0x.\n", *pp);
}

void test01(int *p)
{
	p = (int *)malloc(sizeof(int));
	printf("test01 %0x.\n", p);
}

int main(void)
{
	int num = 1;
	int *p = &num;
	printf("%0x \n", p);
	//test01(p);
	test(&p);
	printf("%0x \n", p);
}
