#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool Check(int pElement, int pElement1)
{
	return pElement = pElement1 * 2;
}

int main(void)
{
	vector<int> intvector;
	intvector.push_back(1);
	intvector.push_back(2);
	intvector.push_back(3);
	intvector.push_back(3);
	intvector.push_back(4);
	intvector.push_back(8);
	
	vector<int>::iterator ifind = adjacent_find(intvector.begin(), intvector.end());	
	if (ifind != intvector.end()) {
		cout << "index " << distance(intvector.begin(), ifind);
	}

	ifind = adjacent_find(intvector.begin(), intvector.end(), Check);	
	if (ifind != intvector.end()) {
		cout << "index " << distance(intvector.begin(), ifind);
	}
	return 0;
}
