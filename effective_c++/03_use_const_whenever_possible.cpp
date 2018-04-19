/*
 * 	尽量使用const，const非常强大，因为它可以修饰的对象非常多
 * 	指针、引用(和指向的对象)，变量，成员函数
 * 	用non-const成员函数调用const成员函数
 * */
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Text
{
public:

	char &operator[](std::size_t position) {
		// 1.static_cast转换为const调用const operator[]
		// 2.const_cast去掉const属性
		return const_cast<char &>(static_cast<const Text &>(*this)[position]);
	}

	const char &operator[](std::size_t position) const {
		return mText[position];
	}

private:
	string mText;
};

int main(int argc, char *argv[])
{
	return 0;
}
