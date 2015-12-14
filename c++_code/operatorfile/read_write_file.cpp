/*
 *读写文件
 * */
#include <iostream>
#include <fstream>

using namespace std;

int main01()
{
  	//输出文件
  	ofstream fout;
	//打开文件
	fout.open("1.txt");
	//写入文件
	fout << "linux unix\n";
	fout << "windows freeBSD\n";
	fout.close();
  	return 0;
}

int main02()
{
  	ifstream filein("1.txt");
	string content;
	filein >> content;
	filein.close();
	cout << content << "\n";
  	return 0;
}

int main03()
{
  	//按行读取
	ifstream fin("1.txt");
	for (int i = 0; i < 2; i++) {
	  	char str[50]  = {0};
		fin.getline(str, 50);
		cout << str << endl;
	}
	fin.close();
  	return 0;
}

int main04()
{
  	//TODO 以fstream方式写文件不成功
  	//读写模式，表示可读可写
  	fstream fio("./4.txt", ios::in | ios::out);
	cout << "start....\n";
	fio << "linux" << endl;
	/*
	fio << "windows" << endl;
	fio << "unix" << endl;
	fio << "freeBSD" << endl;
	fio << "aixs" << endl;
	fio.close();
	*/
	cout << "end....\n";
  	return 0;
}

int main05()
{
	ifstream input("1.txt");
	ofstream output("2.txt");
	if (! input || ! output) {
		return -1;
	}
	cout << "start......\n";
	char ch = 0;	
	while (output && input.get(ch)) {
	  	//写入一个字节
	  	output.put(ch);	
	}
	input.close();	
	output.close();
	cout << "end......\n";
  	return 0;
}

int main()
{
  	//追加方式
  	ofstream fout("2.txt", ios::app);	
	fout << "ubuntu";
	fout.close();
 	return 0;
}
