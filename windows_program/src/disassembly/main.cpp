// 打印处hello world
/*
void print()
{
	// TODO 在此处填写代码打印出hello word
}

void main()
{
}

*/

// 解题思路，就是改变exe的入口地址，并将打印hello world 语句
// 地址传递到main函数，再通过mainCRTStartup调用main函数
// 如果直接在print中函数调用printf函数，会调用失败因为io等等
// 都没有做初始化的操作

#include <iostream>

extern "C" int __cdecl mainCRTStartup(void);

int print()
{
	#pragma comment(linker, "/entry:print")	// 设置入口处
	#pragma comment(linker, "/SECTION:.text,ERW")	//设置代码可读可写可执行
	#pragma comment(lib, "msvcrt.lib")	// 连接c运行时库
	int mainCRTStartup();	//声明 mainCRTStartup main 函数
	void main();

	__asm
	{
		MOV EAX, OFFSET main
		MOV BYTE PTR[EAX], 0xB8 //MOV EAX, 0x      //mov
		MOV DWORD PTR[EAX + 1], OFFSET SHOWSTRING    //将printf语句地址放在eax+1处
		MOV WORD PTR[EAX + 5], 0xE0FF // JMP EAX
	}

	mainCRTStartup();

	__asm
	{
		leave
		ret
	}

SHOWSTRING:
	printf("hello,world!\n");
	__asm
	{
		xor eax, eax
		ret
	}
}

int main()
{
}