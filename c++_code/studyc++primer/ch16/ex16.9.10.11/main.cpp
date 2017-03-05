/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename ElementType>
class ListItem;


template <typename ElementType>
class List
{
public:
	List<ElementType>();

	List<ElementType>(const List<ElementType> &pList);

	List<ElementType> operator=(const List<ElementType> &pList);

	~List<ElementType>();

	void Insert(ListItem<ElementType> *pListItem, ElementType pValue);

private:
	ListItem<ElementType> *front, *end;

};

int main(int argc, char *argv[])
{
	
	return 0;
}
