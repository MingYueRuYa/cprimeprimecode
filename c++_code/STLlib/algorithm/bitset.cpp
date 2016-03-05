/*
 * bitset 针对与位操作
 * */

#include <iostream>
#include <algorithm>
#include <bitset>
#include <iterator>
#include <functional>
#include <cmath>

using namespace std;

int main(void)
{
	bitset<32> bset(255);
	cout << bset << endl;
	//全置1
	bset.set();
	cout << bset << endl;
	//全置1
	bset.reset();
	cout << bset << endl;
	cout << endl;
	//利用bitset找出1-100的质数
	const int number = 100;
	const int loopcount = ((int)sqrt((double)number));
	bitset<number + 1> primeset;
	primeset.set();
	//1不是质数也不是偶数
	primeset[1] = 0;
	/*
	for (int i(1); i <= 100; ++i) {
		if (primeset[i]) {
			for (int j(i * 2); j <= number; j += i) {
				primeset[j]	 = 0;
			}
		}
	}
	for (int i(1); i <= number; ++i) {
		if (primeset[i]) {
			//cout << primeset[i] << " ";
			cout << i << " ";
		}
	}
	*/
	//下面的这段代码是对上面注释的优化 这样处理大数据，效率会非常高的
	for (int i(1); i < loopcount + 1; ++i) {
		if (primeset[i]) {
			for (int j(i * i); j < number + 1; j += i) {
				primeset[j]	 = 0;
			}
		}
	}
	for (int i(1); i <= number; ++i) {
		if (primeset[i]) {
			//cout << primeset[i] << " ";
			cout << i << " ";
		}
	}
	cout << endl;
	cout << "prime number count: " << primeset.count() << endl;
	cout << endl;
	return 0;
}
