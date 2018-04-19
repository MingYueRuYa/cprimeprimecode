/*
 * item 13 以对象管理资源
 * TODO: 1.注意copy and copy assign 行为
 *       2.A.不允许copy，B.采用reference counting
 *       3.RAII技术
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

/*
 * 1.返回值无所谓 2.必须要有一个参数
 * 自定义shared_ptr deleter
 * 因为shared_ptr默认的是delete pointer，但是有时候我们管理的资源并不是
 * 指针类型的数据，比如mutex...
 * */
bool test_custom_shared_deleter(Resource *pResource)
{
    cout << "customer deleter..." << endl;
    delete pResource;
    pResource = NULL;
}

void test_share_pointer()
{
    std::shared_ptr<Resource> resptr(CreateResource());
    std::shared_ptr<Resource> cusresptr(CreateResource(), 
                                        test_custom_shared_deleter);
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
