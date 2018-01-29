#include <iostream>
#include <set>

int main(int argc, char *argv[])
{
	int a[] = {1, 2, 3, 4, 5};
	std::set<int> test_set(a, a+5);

	// lower_bound 不小于value的值
	std::cout << *test_set.lower_bound(2) << std::endl;
	// 第一个>val的元素
	std::cout << *test_set.upper_bound(2) << std::endl;

	return 0;
}
