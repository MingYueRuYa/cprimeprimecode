/*
 * 测试对象返回时是否会做优化
 * */

#include <iostream>

using std::cout;
using std::endl;

class Object
{
public:
    Object() { cout << "Object ctor..." << endl; }
    ~Object() { cout << "~Object dtor..." << endl; }
};

Object RetObj()
{
    Object obj;
    return obj;
}

int main(int argc, char *argv[])
{
    RetObj();
    return 0;
}
