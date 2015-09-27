#include <iostream>
#include "myarray.h"
#include "myarray.cpp"
using namespace std;

int main()
{
    MyArray<int> array(5);
    array.print();
    return 0;
}

