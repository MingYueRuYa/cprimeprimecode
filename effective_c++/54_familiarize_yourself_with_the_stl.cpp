#include <iostream>
#include <memory>

using std::cout;
using std::endl;

/*
 * 测试智能指针，环形引用的解决方案
 * */

namespace test_share_ptr
{
class B;

class A 
{
public:
    A() { cout << "A ctor..." << endl; }
    ~A() { cout << "~A dtor..." << endl; }

public:
    std::shared_ptr<B> mBPtr;

};

class B
{
public:
    B() { cout << "B ctor..." << endl; }
    ~B() { cout << "~B dtor..." << endl; }

public:
    std::shared_ptr<A> mAPtr;
};

void test_share_ptr()
{
    std::shared_ptr<A> aptr = std::make_shared<A>();
    std::shared_ptr<B> bptr = std::make_shared<B>();

    aptr->mBPtr = bptr;
    bptr->mAPtr = aptr;
}

}

namespace test_weak_ptr
{
class B;

class A 
{
public:
    A() { cout << "A ctor..." << endl; }
    ~A() { cout << "~A dtor..." << endl; }

public:
    std::weak_ptr<B> mBPtr;

};

class B
{
public:
    B() { cout << "B ctor..." << endl; }
    ~B() { cout << "~B dtor..." << endl; }

public:
    std::weak_ptr<A> mAPtr;
};

void test_weak_ptr()
{
    std::shared_ptr<A> aptr = std::make_shared<A>();
    std::shared_ptr<B> bptr = std::make_shared<B>();

    aptr->mBPtr = bptr;
    bptr->mAPtr = aptr;
}

}

int main(int argc, char *argv[])
{
    test_share_ptr::test_share_ptr();
    // result: 造成资源泄漏，A，B都为调用析够函数
    // A ctor...
    // B ctor...

    test_weak_ptr::test_weak_ptr();
    // result: 在造成环形引用的时候用weak_ptr代替shared_ptr
    // 从而避免资源没有释放的
    // A ctor...
    // B ctor...
    // ~B dtor...
    // ~A dtor...

    return 0;
}

