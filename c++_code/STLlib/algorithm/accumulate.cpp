/*
 * 累加
 * */

#include <iostream>
#include <algorithm>

using namespace std;

int myaccumulate(int x, int y)
{
	cout << x << " " << y << endl;
	return y + 2;
}

class AccumulateClass
{
public:
	int operator() (int x, int y) 
	{
		return x + y;
	}
};


int main(void)
{
	int array[] = {1, 2, 3, 4, 5};	
	int sum = accumulate(begin(array), end(array), 0);
	sum = accumulate(begin(array), end(array), 0, myaccumulate);
	sum = accumulate(begin(array), end(array), 0, AccumulateClass());
	cout << sum << endl;	

	vector<string> vectorstr;
	vectorstr.push_back("unix");
	vectorstr.push_back("linux");
	vectorstr.push_back("windows");
	
	//"" 不能写成 C-style风格形式
	string sumstr = accumulate(vectorstr.begin(), vectorstr.end(), string(""));
	cout << sumstr << endl;

	return 0;
}
