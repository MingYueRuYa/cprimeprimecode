#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace std;
using namespace boost;

int main(void)
{
	for (int i = 0; i < 10000; ++i) {
		//unique_ptr<int>	int_ptr(new int());
		//shared_ptr<int> p(new int(2));
		shared_ptr<int> ptr = make_shared<int>(2);
	}
	return 0;
}
