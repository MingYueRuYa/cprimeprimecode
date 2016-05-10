#include <iostream>
#include <memory>

using namespace std;

int main(void)
{
	for (int i = 0; i < 10000; ++i) {
		unique_ptr<int>	int_ptr(new int());
	}
	return 0;
}
