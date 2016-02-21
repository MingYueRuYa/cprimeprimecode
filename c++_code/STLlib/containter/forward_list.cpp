include <iostream>
#include <forward_list>
#include <algorithm>

using namespace std;

int main(void)
{
	forward_list<int> fllist = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto prev = fllist.before_begin();
	auto curr = fllist.begin();
	while (curr != fllist.end()) {
		if (*curr % 2) {
			curr = fllist.erase_after(prev);	
		}
		else {
			prev = curr;
			++curr;
		}
	}
	for_each(fllist.begin(), fllist.end(), [](int even){ cout << even << endl;});
	return 0;
}
