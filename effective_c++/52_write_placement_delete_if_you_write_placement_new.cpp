#include <iostream>
#include <new>

using std::cout;
using std::endl;

namespace test_placement_new 
{

class Widget
{
public:
    Widget() { cout << "widget ctor..." << endl; }
    ~Widget() { cout << "~widget dtor..." << endl; }
    
    // normal operator new
    static void *operator new(size_t size) 
    {
        cout << "normal op new" << endl;
        return ::operator new(size);
    }

    // normal operator delete
    static void operator delete(void *pMemory, size_t size) 
    {
        cout << "normal op delete" << endl;
        ::operator delete(pMemory);
    }

    static void *operator new(size_t size, void *pMemory)
    {
        cout << "placement new (size_t size, void *pMemory)" << endl;
        return pMemory;
    }

    static void operator delete(void *pStart, void *pMemory)
    {
        cout << "placement delete(void *pStart, void *pMemory)" << endl;
        return ::operator delete(pStart);
    }

    static void *operator new(size_t size, std::ostream &logstream)
    {
        cout << "placement new (size_t size, std::ostream &logstream)" 
            << endl;
        return ::operator new(size);
    }

    static void operator delete(void *pStart, std::ostream &logstream)
    {
        cout << "placement delete(void *pStart, std::ostream &logstream)" 
            << endl;
        return ::operator delete(pStart);
    }

};

void test_placement_new()
{
    Widget *widget = new Widget();
    delete widget;
    widget = NULL;

    Widget tempwidget;
    Widget *placement_widget = new (&tempwidget) Widget();

    Widget *placemet_widget2 = new (std::cerr) Widget();
    delete placemet_widget2;

    // result:
    // normal op new
    // widget ctor...
    // ~widget dtor...
    // normal op delete

    // widget ctor...
    // placement new (size_t size, void *pMemory)
    // widget ctor...

    // placement new (size_t size, std::ostream &logstream)
    // widget ctor...
    // ~widget dtor...
    // normal op delete
    // ~widget dtor...
}

}

namespace base_name_cover
{
/*! 
 *  如果提供了placement new，就必须提供placement delete
 *  防止在分配内存的时候发生异常，可以调用placement delete
 *  同时placement new会把正常的new隐藏掉，即也要提供normal delete
 * */
class Base
{
public:
    Base() { cout << "base ctor..." << endl; }
    ~Base() { cout << "~base dtor..." << endl; }

    static void *operator new (size_t size, std::ostream &logStream)
    {
        cout << "base operator placement new " << endl;
        return ::operator new(size);
    }

    static void operator delete (void *pStart, std::ostream &logStream)
    {
        cout << "base operator delete void *pStart, std::ostream &logStream" 
             << endl;
        ::operator delete(pStart);
    }

    static void *operator new (size_t size)
    {
        cout << "base operator normal new " << endl;
        return ::operator new(size);
    }

    static void operator delete (void *pStart, size_t size) 
    {
        cout << "base operator delete void *pStart, size_t size" 
             << endl;
        ::operator delete(pStart);
    }
};

class Drive : public Base
{
public:
    // 让Base的operator new函数可见
    using Base::operator new;
    using Base::operator delete;

    Drive() { cout << "drive ctor..." << endl; }
    ~Drive() { cout << "~drive dtor..." << endl; }

    static void *operator new(size_t size) throw(std::bad_alloc)
    {
        cout << "drive operator new" << endl;
        return ::operator new(size);
    }

    static void operator delete(void *pMemory, size_t size) throw()
    {
        cout << "drive operator delete" << endl;
        ::operator delete(pMemory);
    }
};

void test_base_name_cover()
{
    // error:
    // matching function for call to 
    // ‘base_name_cover::Base::operator new(sizetype)
    // Base *base = new Base();

    // correct:
    Base *base = new (std::clog) Base();
    delete base; base = NULL;

    // error: 因为Base的placement new被隐藏
    // Drive *drive = new (std::clog)Drive();
    
    Base *base1 = new Drive();
    delete base1; base1 = NULL;

    // 在Drive中加入116-117两行代码
    Base *base2 = new (std::clog)Drive();
    delete base2; base2 = NULL;

    // result:
    // base operator placement new 
    // base ctor...
    // ~base dtor...
    // base operator delete void *pStart, size_t size

    // drive operator new
    // base ctor...
    // drive ctor...
    // ~base dtor...
    // base operator delete void *pStart, size_t size

    // base operator placement new 
    // base ctor...
    // drive ctor...
    // ~base dtor...
    // base operator delete void *pStart, size_t size
}

}

/*! 
 * 重载任何形似的new，都会隐藏global作用域下的oprator new
 * void *operator new(std::size_t) throw(std::bad_alloc)    normal new
 * void *operator new(std::size_t, void *) throw()          placement new
 * void *operator new(std::size_t, const std::nothrow_t&) throw() nothrow new
 * */
namespace solve_hide_new_problem
{
class StandardNewDeleteForm
{
public:
    // normal new/delete
    static void *operator new(std::size_t size) throw(std::bad_alloc)
    { return ::operator new(size); }
    static void operator delete(void *pMemory) throw()
    { return ::operator delete(pMemory); }

    // placement new/delete
    static void *operator new(std::size_t size, void *pMemory) 
        throw(std::bad_alloc)
    { return ::operator new(size, pMemory); }
    static void operator delete(void *start, void *pMemory) throw()
    { return ::operator delete(start, pMemory); }
    
    // nothrow new/delete
    static void *operator new(std::size_t size, const std::nothrow_t &nt) 
        throw()
    { return ::operator new(size, nt); }
    static void operator delete(void *start, const std::nothrow_t &nt) throw()
    { return ::operator delete(start, nt); }

};

class Widget : public StandardNewDeleteForm
{
public:
    using StandardNewDeleteForm::operator new;
    using StandardNewDeleteForm::operator delete;

        static void *operator new (size_t size, std::ostream &logStream)
    {
        cout << "Widget operator placement new " << endl;
        return ::operator new(size);
    }

    static void operator delete (void *pStart, std::ostream &logStream)
    {
        cout << "Widget operator delete void *pStart, std::ostream &logStream" 
             << endl;
        ::operator delete(pStart);
    }

};

void solve_hide_new_problem()
{
    // normal new
    Widget *widget = new Widget(); 
    delete widget; widget = NULL;

    // placement new
    Widget tempwidget;
    Widget *widget1 = new (&tempwidget)Widget(); 

    Widget *widget2 = new (std::clog)Widget(); 
    delete widget2; widget2 = NULL;
    // result:
    // Widget operator placement new
}

}

int main(int argc, char *argv[])
{
    // test_placement_new::test_placement_new();
    // base_name_cover::test_base_name_cover();
    // solve_hide_new_problem::solve_hide_new_problem();
    return 0;
}
