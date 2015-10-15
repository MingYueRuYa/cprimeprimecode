/*
 * 输出流
 * */

#include <iostream>
//控制输出流
#include <iomanip>

int main01()
{
	std::cout.put('A').put('B').put('C');
	char str[] = "12345678910abcdefg";
	std::cout.write(str, 10);
	std::cin.get();
	return 0;
}


using namespace std;
int main02()
{
	//dec, oct, hex 都是格式控制
	int num = 01070;
	cout << num << endl;//默认是十进制
	//十六进制强制标识符endl结束不了
	cout << hex;
	cout << num << "----" << num << endl;
	//八进制强制标识，endl结束不了
	cout << oct;
	cout << num << "----" << num << endl;
	cout << oct;
	//十进制强制标识
	cout << dec;
	cout << num << "----" << num << endl;
	return 0;
}


int main03()
{
	double db = 3.14159265401925345678;
	//cout << db << endl;小数点后面六位
	//小数点显示精度
	cout << setprecision(25) << db << "\n";
	return 0;
}

int main()
{
	//设定先是的宽度
	cout.width(40);
	//填充字符
	cout.fill('&');
	//输出的内容左对齐
	cout.setf(ios::left);
	cout << "hello world" << endl;

	//设定显示的宽度，如果实际长度hello world超过了20，按照实际的长度输出
	cout.width(20);
	//填充的字符
	cout.fill('*');
	cout.setf(ios::right, ios::left);
	cout << "hello world" << endl;
	return 0;
}

