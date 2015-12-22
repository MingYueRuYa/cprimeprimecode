#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
	vector<string> text;
	for (string line; getline(cin, line);) {
		text.push_back(line);
	}
	for (vector<string>::iterator sbeg = text.begin(); sbeg != text.end() && !sbeg->empty(); ++sbeg) {
		for (char &c : *sbeg) { c = toupper(c); }
		cout << *sbeg << endl;
	}
	return 0;
}
