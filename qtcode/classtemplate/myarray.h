#ifndef MYARRAY_H
#define MYARRAY_H

template<class T, int length>
class MyArray
{
public:

    MyArray(T a);

    MyArray();

    int size();

    T Get(int pPos);

    void Set(T data, int pPos);

    void print();

  private:

    T *a;

    int length;
};

#endif // MYARRAY_H



