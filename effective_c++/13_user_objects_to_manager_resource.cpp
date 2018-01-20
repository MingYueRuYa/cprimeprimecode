/*
 * item 13 以对象管理资源
 * */

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

namespace test_circle_reference
{

class ObjA;
class ObjB;

class ObjA
{
public:
    ObjA() { cout << "ObjA ctor..." << endl; }
    ~ObjA() { cout << "ObjA dtor..." << endl; }
public:
    std::shared_ptr<ObjB> mObjBPtr;
};

class ObjB
{
public:
    ObjB() { cout << "ObjB ctor..." << endl; }
    ~ObjB() { cout << "ObjB dtor..." << endl; }
public:
    std::shared_ptr<ObjA> mObjAPtr;
};

void test_circle_reference()
{
    std::shared_ptr<ObjA> objAPtr(new ObjA());
    std::shared_ptr<ObjB> objBPtr(new ObjB());

    objAPtr->mObjBPtr = objBPtr;
    objBPtr->mObjAPtr = objAPtr;
}

}

namespace test_shared_ptr
{

class Resource
{
public:
    Resource() { cout << "resource ctor..." << endl; }
    ~Resource() { cout << "resource dtor..." << endl; }
};

Resource *CreateResource()
{
    return new Resource();
}

void test_share_pointer()
{
    std::shared_ptr<Resource> resptr(CreateResource());
}

}
int main(int argc, char *argv[])
{
    test_shared_ptr::test_share_pointer();

    test_circle_reference::test_circle_reference();

    //TODO notice ObjA ObjB是circle reference 析构函数没有被调用
    // 所以就有了weak_ptr指针
    //result:     
    // resource ctor...
    // resource dtor...
    // ObjA ctor...
    // ObjB ctor...
    return 0;
}
