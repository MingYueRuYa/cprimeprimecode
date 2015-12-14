/**
 * 文本和二进制的读写
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct MyStruct
{
	char *p = "上海是魔都";
	int num = 20;
	double db = 10.98;
	char ch = 'a';
};

struct binarystr
{
	double db = 1.01;
	int i = 4;
};

int main01()
{
	MyStruct struct1;
	ofstream fwrite("1.txt");	
	fwrite << struct1.p << " "<< struct1.num << " "<< struct1.db << " " << struct1.ch << "\n";
	fwrite.close();
	ifstream fread("1.txt");
	char str[100] = {0};
	fread.getline(str, 100, 0);
	cout << str << "\n";
	return 0;
}

//按照块的方式读取二进制文件
int main02()
{
	MyStruct struct1;
	ofstream fwrite("1.bin", ios::binary);
	//写入文件的内存的首地址, 写入的长度
	fwrite.write((char *)&struct1, sizeof(MyStruct));
	fwrite.close();
	MyStruct struct2;
	ifstream fread("1.bin", ios::binary);
	fread.read((char *)&struct2, sizeof(MyStruct));
	cout << struct2.p << " " << struct2.num << "\n";	
	return 0;
}

//按照字节的方式读取
int main03()
{
	ifstream fread("appold", ios::binary);
	ofstream fwrite("newapp", ios::binary);
	if (! fread || ! fwrite) {
		cout << "open app file fail.\n";
		return -1;	
	}
	cout << "start copy file......\n";
	char binarych = 0;
	while (fread.get(binarych)) {
		fwrite.put(binarych);	
	}
	cout << "end copy file......\n";
	return 0;
}

int main()
{
	ofstream fwrite("big.txt", ios::binary);	
	struct binarystr struct02[5];	
	fwrite.write((char *)struct02, sizeof(binarystr) * 5);
	fwrite.close();
	
	binarystr *pstruct = new binarystr[5];
	ifstream fread("big.txt", ios::binary);
	fread.read((char *)pstruct, sizeof(binarystr) * 5);	
	fread.close();
	for (int i = 0; i < 5; i++) {
		cout << pstruct[i].db << "  " << pstruct[i].i << "\n";
	}
	return 0;
}

