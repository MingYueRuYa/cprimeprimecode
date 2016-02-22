/*!
 * 反向迭代器
 * forward_list 和 stream iterator 不支持反向迭代器
 * */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> intvec{2, 1, 5, 6, 3, 7};
	//反向迭代器，可以从小到达排序
	sort(intvec.rbegin(), intvec.rend());
	for_each(intvec.begin(), intvec.end(), [](int num){ cout << num << endl; });
	return 0;
}
