#include <iostream>
#include <string>
#include <iterator>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void check(const vector<int> &pIvec)
{
	if (pIvec.empty()) {
		cout << "size: 0; no values." << endl;
	}
	else {
		cout << "size: " << pIvec.size() << "; vlaues:";
		for (vector<int>::const_iterator ibeg = pIvec.begin(); ibeg != pIvec.end(); ++ibeg) {
			cout << *ibeg << ",";	
		}
		cout << "\b." << endl;
	}
}

void check(const vector<string> &pIvec)
{
	if (pIvec.empty()) {
		cout << "size: 0; no values." << endl;
	}
	else {
		cout << "size: " << pIvec.size() << "; vlaues:";
		for (vector<string>::const_iterator ibeg = pIvec.begin(); ibeg != pIvec.end(); ++ibeg) {
			cout << *ibeg << ",";	
		}
		cout << "\b." << endl;
	}
}

int main(int argc, char *argv[])
{
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3{10, 20};
	vector<int> v4(10, 20);

	vector<string> v5(1, "hello");
	vector<string> v6{10, "hi"};
	vector<string> v7{"linux", "hi"};

	check(v1);
	check(v2);
	check(v3);
	check(v4);

	check(v5);
	check(v6);
	check(v7);
	return 0;
}

