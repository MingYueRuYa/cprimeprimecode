/*
 * resiz funcion
 * */

#include <iostream>
#include <list>
#include <vector>

using std::list;

int main()
{
  	list<int> intlist(10, -1);
	auto iben = intlist.begin();
	while (iben != intlist.end()) {
	  //std::cout << *iben++ << std::endl;
	  iben++;
	}
	intlist.resize(20, 0);
	iben = intlist.begin();
	while (iben != intlist.end()) {
	  std::cout << *iben++ << std::endl;
	}
/*for (int i = 0; i < intlist.size(); ++i) {
	  std::cout << intlist.at(i) << std::endl;
	}
	*/
	return 0;
}


