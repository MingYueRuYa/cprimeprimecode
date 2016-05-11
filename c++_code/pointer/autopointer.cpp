#include <iostream>
#include <memory>
#include <tr1/memory>

using namespace std;
using namespace std::tr1::shared_ptr;

int main(void)
{
	for (int i = 0; i < 10000; ++i) {
		//unique_ptr<int>	int_ptr(new int());
		shared_ptr<int> p;
	}
	return 0;
}
