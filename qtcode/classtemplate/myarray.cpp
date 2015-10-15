#include "myarray.h"
#include <iostream>
using namespace std;

template<class T, int length>
MyArray<T>::MyArray(int length )
{
    this->length = length;
    a = new T[length];
}


template<class T, int length>
void MyArray<T>::print()
{								
    for (int i = 0; i < length; i++) {
       std::out << a[i] << std::endl;
    }
}


template<class T, int length>
void MyArray<T>::size()
{
     this->length;
}

template<class T ,int length>
void MyArray<T>::Set(T data, int pPos)
{
    if (pPos < 0 || pPos > this->length) {
       return;
    }
    a[pPos] = data;
}


template<class T ,int length>
T MyArray<T>::Get(int pPos)
{
    if (pPos < 0 || pPos > this->length) {
       //return ;
    }

    return *(a + pPos);

}
