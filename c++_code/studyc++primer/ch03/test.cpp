#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

int main(int argc, char *argv[])
{
	//vector<int> iv(10, 1);
	//vector<int> iv{1, 2};
	//vector<string> iv{10, "hi"};
	vector<string> iv{"hello", "hi"};
	for (auto i : iv) {
		std::cout << i << std::endl;
	}
	return 0;
}

