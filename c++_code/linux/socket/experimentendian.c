/*
 * 测试机器是大端还是小端
 * 小端：低位放在低位的位置
 * 大端：正好和小端刚好是相反的
 * x86平台都为小端
 * motorola 6800是大端
 * ARM字节序是可以配置的
 * 网络字节序都是为大端模式的
 * */
#include <stdio.h>

int main(void)
{
	int i = 0;
	int smallendian = 0x12345678;
	char *ch = &smallendian;
	for (; i < 4; ++i) {
		printf("%x ", ch[i]);
	}
	//result out
	//78 56 34 12--------->为小端
	printf("\n");
	return 0;
}
