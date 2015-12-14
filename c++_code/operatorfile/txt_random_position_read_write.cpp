/*
 * 文本文件随机位置读写
 * */

#include <iostream>
#include <fstream>

using namespace std;
//随机读取txt
int main01(int argc, char **argv)
{
	ofstream fwrite("1.txt");
	fwrite << "123456789abcdefghijk";	
	fwrite.close();
	ifstream fread("1.txt");
	//从尾部倒数第9个位置开始读取
	//fread.seekg(-9, ios::end);
	//从开始往前9个
	fread.seekg(9, ios::beg);
	char ch;
	while (fread.get(ch)) {
		cout << ch;
	}
	fread.close();
	return 0;
}

//随机写入txt
int main(int argc, char **argv)
{
	ofstream fwrite("1.txt", ios::in | ios::out);	
	char str[] = "linux windows unix";
	//注意读取的时候是seekg,写入的时候是seekp
	fwrite.seekp(0, ios::end);
	//当前位置距离begin还有多少字节，这样可以获取文件的大小
	long size = fwrite.tellp();
	cout << size << endl;
	//从尾部追加str
	fwrite << str;
	fwrite.close();
	return 0;
}

