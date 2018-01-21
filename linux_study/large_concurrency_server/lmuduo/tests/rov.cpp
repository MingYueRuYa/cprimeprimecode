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
    // result:只有一次构造函数和析构函数的调用
    // Object ctor...
    // ~Object dtor...

    return 0;
}
