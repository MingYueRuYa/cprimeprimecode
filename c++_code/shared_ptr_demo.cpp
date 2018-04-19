/*
 * 测试shared_ptr 编译时需要指定-std=c++11
 * http://www.myexception.cn/cpp/1986024.html
 * 使用注意事项：
 * 条款1：不要把一个原生指针给多个shared_ptr管理
 * 条款2：不要把this指针给shared_ptr
 * 条款3：不要让shared_ptr的循环引用.
 * 条款4：不要在函数实参里创建shared_ptr
 *   function ( shared_ptr<int>(new int), g( ) );  //有缺陷
 *   可能的过程是先new int，然后调g( )，g( )发生异常，shared_ptr<int>没有创建
 *   ，int内存泄露
 * shared_ptr<int> p(new int());
 * f(p, g());  //Boost推荐写法
 * 条款5：对象内部生成shared_ptr
 * boost::shared_ptr<Y> spy(new Y)
 * boost::shared_ptr<Y> p =  spy->GetSelf(); //OK
 * 条款6 ：处理不是new的对象要小心。
 *  int* pi = (int*)malloc(4)
 *  shared_ptr<int> sp( pi ) ; //delete马嘴不对malloc驴头。
 * 条款7：多线程对引用计数的影响。
 * 条款8：对象数组用shared_array
 * 条款9：学会用删除器
 * 条款10：学会用分配器
 * 条款11: weak_ptr在使用前需要检查合法性。
 * 条款12: 不要new shared_ptr<T>
 * 条款13:  尽量不要get
 * 条款14: 不要memcpy shared_ptr
 * 条款15: 使用BOOST预定义的宏去改变shared_ptr行为。
 * 条款16: 构造函数里调用shared_from_this抛例外
 *
 *
 * 总结：专一
 *      1.拿到指针就不要轻易的暴露出来
 *      2.只接管new出来的指针，不是malloc内存地址
 *      3.自定义deleter
 *      4.多线程对写是不安全的
 * */
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;

class Test
{
public:
    Test(const int pID) : mID(pID)
    {
        cout << "Test ctor" << endl;
    }

    ~Test()
    {
        cout << "~Test dtor" << endl;
    }

    void SetID(const int pID)
    {
        mID = pID;
    }

    void PrintID()
    {
        cout << "Test ID " << mID << endl;
    }

private:
    int mID;

};

shared_ptr<Test> g_test;

shared_ptr<Test> test1()
{
    g_test = make_shared<Test>(5);
    return g_test;
}

void test2()
{
    shared_ptr<Test> ptr1 = test1();
    cout << "use count " << ptr1.use_count() << endl;

    ptr1->SetID(1);
    cout << "ptr1 ID" << endl;
    ptr1->PrintID();
    cout << "g_test ID" << endl;
    g_test->PrintID();
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}
