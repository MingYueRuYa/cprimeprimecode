/*
 * 转义字符
 * */

#include <iostream>
#include <string>
#include <stdlib.h>

int main()
{
	//在linux下路径都是45度的斜杠
	std::string path = "~/code/c_code/a.out";	
	//在windows下
	//path = R"(c:\program Files\Tencent\QQ\...)";
	system(path.c_str());
	double dou = 1.2;
	std::cout << ++dou <<std::endl;
	return 0;
}
