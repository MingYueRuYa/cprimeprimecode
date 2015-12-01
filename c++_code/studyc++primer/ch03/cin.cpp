#include <iostream>
#include <string>
/*
 * ctrl + d is end of file.
 * */
using namespace std;

int main(int argc, char *argv[])
{
//	string word;	
// read only word.
//	while (cin >> word) {
//		cout << word <<endl;
//	}
//

	string line;
	while (getline(cin, line)) {
		cout << line << endl;
	}
	return 0;
}
