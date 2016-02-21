#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	vector<string> vectorstr01(10, "hi");	
	vector<string> vectorstr02(20, "hehe");	
	swap(vectorstr01, vectorstr02);
	for (auto ibeg = vectorstr01.begin(); ibeg != vectorstr01.end(); ++ibeg) {
	  	cout << *ibeg << endl;
	}
 	for (auto ibeg = vectorstr02.begin(); ibeg != vectorstr02.end(); ++ibeg) {
	  	cout << *ibeg << endl;
	}
return 0;
}
