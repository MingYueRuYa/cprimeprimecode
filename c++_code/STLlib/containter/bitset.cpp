/*
 * 二进制容器
 * */

#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int main01()
{
	//	   8位， 215代表构造的数据
	bitset<8> bs(215);
	//最高位存储在第七位
	for (int i = 7; i >= 0; i--) {
		cout << bs[i];
	}
	cout << "\n";
	return 0;
}

int main()
{
	int num = -5;
	bitset<32> bs(num);
	for (int i = 31; i >= 0; i--) {
		cout << bs[i];
	}
	cout << "\n";
	string str = bs.to_string();
	cout << str << "\n";
	unsigned int data;
	//转为无符号
	data = bs.to_ulong();
	cout << data << "\n";

	bitset<8> bset(255);
	//operate binary 
	bset.set(7, 0);
	bset.set(0, 0);
	for (int i = 7; i >= 0; i--) {
		cout << bset[i];
	}
	cout << "\n" << bset.size() << "\n";
	//bset.reset();全部清0操作
	return 0;
}

