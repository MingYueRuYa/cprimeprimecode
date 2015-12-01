#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	std::string str01, str02;
	/*
		 while (cin >> str01 >> str02) {
		 if (str01 == str02) {
		 cout << "The Two strings are equal." << endl;
		 }
		 else {
		 cout << "The large string is " << (str01 > str02 ? str01 : str02) << endl;
		 }
		 }
		 cout << (str01 > str02) ? str01 : str02;
		 */
	/*
		 while (cin >> str01) {
		 str02 += str01;
		 }
		 cout << str02 << endl;
		 */

	/*
		 std::string str("a simple string");
		 for (char &c : str) {
		 c = 'X';
		 }
		 */
	/*
	//first function
	decltype(str.size()) i = 0;
	while (i < str.size()) {
	str[i] = 'X';
	++i;
	}
	*/
	/*
		 for (int i = 0; i < str.size(); i++) {
		 str[i] = 'Y';
		 }
		 fist function good.
		 cout << str << endl;
		 */

	std::string s;
	cout << "Enter a string of characters including puncuation." << endl;
	while (getline(cin, s)) {
		for (auto i : s) {
			//ispunct 判断是否是点符号
			if (!ispunct(i)) {
				cout << i;
			}
		}
		cout << endl;
	}

	return 0;
}
