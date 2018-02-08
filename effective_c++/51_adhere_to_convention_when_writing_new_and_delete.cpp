#include <iostream>

using std::cout;
using std::endl;
using std::string;

namespace rules_new_delete
{
class Widget
{
public:
    Widget () { cout << "widget ctor..." << endl; }
    ~Widget () { cout << "~widget dtor..." << endl; }

    // 两个要点：
    // 1.不断循环试图获取内存
    // 2.调用new_handler通知客户，如果客户没有设置new_handler报出异常
    static void *operator new(size_t size)
    {
        // your operator new might take additional params
        using namespace std;

        if (0 == size) { size = 1; }

        void *start = NULL;
        while (true) {
            if (NULL != (start = ::operator new(size))) { return start; } 

            new_handler global_handler = set_new_handler(0);
            set_new_handler(global_handler);

            if (NULL != global_handler) { (*global_handler)(); }
            else { throw std::bad_alloc(); }
        }
    }

    static void operator delete(void *start, size_t size)
    {
        // 回收内存处理

        //这里简单的将内存还给系统
        ::operator delete(start);
    }

};

class Base
{
public:
    Base() { cout << "base ctor..." << endl; }
    virtual ~Base() { cout << "~base dtor..." << endl; }

    static void *operator new(size_t size)
    {
        cout << "Base operator new" << endl;
        if (size != sizeof(Base)) { 
            cout << "new drive." << endl;
            return ::operator new(size); 
        }
        
        // 从内存池中获取内存，这里简单处理
        void *start = NULL;
        return start = ::operator new(size);
    }

    static void operator delete(void *start, size_t size)
    {
        cout << "Base operator delete" << endl;
        if (size != sizeof(Base)) {  
            cout << "delete drive." << endl;
            ::operator delete(start); 
            return;
        }

        // 回收到内存池中，这里简单处理
        ::operator delete(start); 
    }

private:
    int age;

};

class Drive : public Base
{
public:
    Drive() { cout << "drive ctor..." << endl; }
    ~Drive() { cout << "~drive dtor..." << endl; }

private:
    string name;
};

void test_new_delete()
{
    cout << "Base size: " << sizeof(Base) << endl;
    cout << "Drive size: " << sizeof(Drive) << endl;

    Drive *drive = new Drive();
    delete drive; drive = NULL;
    // result: 如果父类重载new，delete，子类会调用父类的new，delete 函数
    // Base size: 8
    // Drive size: 12
    // Base operator new
    // new drive.
    // base ctor...
    // drive ctor...
    // ~drive dtor...
    // ~base dtor...
    // Base operator delete
    // delete drive.

}

}

int main(int argc, char *argv[])
{
    rules_new_delete::test_new_delete();


    return 0;
}
