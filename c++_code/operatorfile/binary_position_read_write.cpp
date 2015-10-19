/*
 * 二进制文件随机位置读写
 * */

#include <iostream>
#include <fstream>

using namespace std;
//随机读取二进制
int main(int argc, char **argv)
{
	double db[10] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1};
	ofstream fwrite("1.bin", ios::binary);
	fwrite.write((char *)db, sizeof(db) * 10);
	fwrite.close();
	double *newdb = new double[10];
	ifstream fread("1.bin", ios::binary);
	fread.read((char *)newdb, sizeof(double) * 10);
	fread.close();
	for (int i = 0; i = 10; i++) {
		cout << newdb[i] << "\n";	
	}
	return 0;
}

//随机写入二进制
int main01(int argc, char **argv)
{
	return 0;
}

