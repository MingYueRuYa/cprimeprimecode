#include <list>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::list;

int main(int argc, char *argv[])
{
	list<int> intlist;		
	for (int i=0; i<10; ++i) {
		intlist.push_back(i);
	}


	list<int>::iterator ibeg = intlist.begin();
	for (; ibeg != intlist.end(); ++ibeg) {
		cout << *ibeg << " ";
	}
	cout << endl;

	ibeg = intlist.begin();
	std::advance(ibeg, 3);	

	int step = 0;
	step = std::distance(intlist.begin(), ibeg);
	cout << "distance:" << step << endl;

	step = std::distance(intlist.begin(), intlist.end());
	cout << "distance:" << step << endl;

	cout << "size:" << intlist.size() << endl;

	return 0;
}

