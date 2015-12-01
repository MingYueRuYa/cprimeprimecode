#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	vector<int> v1;
	cout << "{\n \"v1\":{\"size\":\"" << v1.size() << "\", \"value\":[";
	for (int i : v1) {
		cout << i << ",";
	}
	if (! v1.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	vector<int> v2(10);
	cout << " \"v2\":{\"size\":\"" << v2.size() << "\", \"value\":[";
	for (int i : v2) {
		cout << i << ",";
	}
	if (! v2.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	vector<int> v3(10, 42);
	cout << " \"v3\":{\"size\":\"" << v3.size() << "\", \"value\":[";
	for (int i : v3) {
		cout << i << ",";
	}
	if (! v3.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	vector<int>	v4{10};
	cout << " \"v4\":{\"size\":\"" << v4.size() << "\", \"value\":[";
	for (int i : v4) {
		cout << i << ",";
	}
	if (! v4.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	vector<int> v5{10, 42};
	cout << " \"v5\":{\"size\":\"" << v5.size() << "\", \"value\":[";
	for (int i : v5) {
		cout << i << ",";
	}
	if (! v5.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	//vector<string> v6{10};
	vector<string> v6(10, "hello");
	cout << " \"v6\":{\"size\":\"" << v6.size() << "\", \"value\":[";
	for (string i : v6) {
		if (i.empty()) {
			cout << "(null)" << ",";
		}
		else {
			cout << i << ",";
		}
	}
	if (! v6.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	vector<string> v7{10, "hi"};
	cout << " \"v7\":{\"size\":\"" << v7.size() << "\", \"value\":[";
	for (string i : v7) {
		if (i.empty()) {
			cout << "(null)" << ",";
		}
		else {
			cout << i << ",";
		}
	}
	if (! v7.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	vector<string> v8{"hello", "hi"};
	cout << " \"v8\":{\"size\":\"" << v8.size() << "\", \"value\":[";
	for (string i : v8) {
		if (i.empty()) {
			cout << "(null)" << ",";
		}
		else {
			cout << i << ",";
		}
	}
	if (! v8.empty()) {
		cout << "\b";
	}
	cout << "]}\n";

	cout << "}\n";
	return 0;
}
