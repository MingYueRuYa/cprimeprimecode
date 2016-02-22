
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main(void)
{
	vector<int> myvector;
	//不能这样写, myvector 为空 里面没有元素
	//fill_n(myvector.begin(), 10, 0);

	fill_n(back_inserter(myvector), 10, 1);
	vector<int>::iterator ibeg = myvector.begin();
	while (ibeg != myvector.end()) {
		cout << *ibeg << " ";
		++ibeg;
	}
	cout << endl;
	return 0;
}
