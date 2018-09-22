/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <iostream>

using std::cout;
using std::endl;

/*
 * 为每个class定制自己的new_handler
 * */

namespace test_formal_handler
{
void OutOfMem()
{
    std::cerr << "Unable to satisfy request of for memory\n";
    std::abort();
}

void test_out_of_mem()
{
    std::set_new_handler(OutOfMem);

    int *pBigDataArray = new int[300000000];
}

}

namespace normal_handler
{
class A
{
public:
    A() {}
    ~A() {}

    static void *operator new (size_t size)
    {
        // 1.设置全局new_handler
        std::new_handler oldhandler = std::set_new_handler(new_handler);
        // 2.分配内存
        void *start = ::operator new(size);
        // 测试代码，故意爆出异常
        int *pBigDataArray = new int[300000000];
        // 3.设置返回之前的全局new_handler
        std::set_new_handler(oldhandler);
        return start;
    }

    static void new_handler()
    {
        std::cerr << "Unable to satisfy request of for memory to A class\n";
        std::abort();
    }
};

class B
{
public:
    B() {}
    ~B() {}

    static void *operator new (size_t size)
    {
        // 1.设置全局new_handler
        std::new_handler oldhandler = std::set_new_handler(new_handler);
        // 2.分配内存
        void *start = ::operator new(size);
        // 3.设置返回之前的全局new_handler
        int *pBigDataArray = new int[300000000];
        std::set_new_handler(oldhandler);
        return start;
    }

    static void new_handler()
    {
        std::cerr << "Unable to satisfy request of for memory to B class\n";
        std::abort();
    }
};

class Normal
{
public:
    Normal() {}
    ~Normal() {}

    static void *operator new (size_t size)
    {
        // 1.设置全局new_handler
        std::new_handler oldhandler = std::set_new_handler(new_handler);
        // 2.分配内存
        void *start = ::operator new(size);
        // 3.设置返回之前的全局new_handler
        std::set_new_handler(oldhandler);
        return start;
    }

    static void operator delete(void *start, size_t size)
    {
        cout << "normal operator delete " << endl;
        ::operator delete(start);
    }

    static void new_handler()
    {
        std::cerr << "Unable to satisfy request of for "
                     "memory to Normal class\n";
        std::abort();
    }
};

void test_A_normal_handler()
{
    A *a = new A();
    delete a;
    a = NULL;
}

void test_B_normal_handler()
{
    Normal *normal = new Normal();
    delete normal;
    normal = NULL;
    B *a = new B();
}

}

/*
 * 加强版 new_handler处理
 * */
namespace enhance_new_handler
{
class NewHandlerHolder
{
public:
    NewHandlerHolder(std::new_handler pNewHandler) : mCurHandler(pNewHandler)
    {
    }

    ~NewHandlerHolder()
    {
        std::set_new_handler(mCurHandler);
    }

private:
    // 阻止拷贝和赋值构造
    NewHandlerHolder(const NewHandlerHolder &);
    NewHandlerHolder& operator=(const NewHandlerHolder &);

private:
    std::new_handler mCurHandler;

};

class Widget
{
public:
    Widget() {}
    ~Widget() {}

    static void *operator new(size_t size)
    {
        NewHandlerHolder handlerholder(std::set_new_handler(OutOfMem));
        return ::operator new(size);
    }

    static void OutOfMem()
    {
        std::cerr << "Unable to satisfy request of "
                     "for memory to widget class\n";
        abort(); 
    }

};

void test_enhance_new_handler()
{
    Widget *widget = new Widget();
    delete widget;
    widget = NULL;
}

}

/*
 * 利用模板，让每个class轻松指定自己的new_handler
 * 循环模板模式，Do it for me
 * */
namespace template_new_handler
{
class NewHandlerHolder
{
public:
    NewHandlerHolder(std::new_handler pNewHandler) : mCurHandler(pNewHandler)
    {
    }

    ~NewHandlerHolder()
    {
        std::set_new_handler(mCurHandler);
    }

private:
    // 阻止拷贝和赋值构造
    NewHandlerHolder(const NewHandlerHolder &);
    NewHandlerHolder& operator=(const NewHandlerHolder &);

private:
    std::new_handler mCurHandler;

};

template <typename T>
class NewHandlerSupport
{
public:
    static std::new_handler set_new_handler(std::new_handler p) throw()
    {
        std::new_handler oldhandler = mCurrentHandler;
        mCurrentHandler = p;
        return oldhandler;
    }

    static void *operator new(size_t size)
    {
        NewHandlerHolder holder(std::set_new_handler(mCurrentHandler)); 
        return ::operator new(size);
    }

private:
    static std::new_handler mCurrentHandler;

};

template <typename T>
std::new_handler NewHandlerSupport<T>::mCurrentHandler = NULL;

class Widget : public NewHandlerSupport<Widget>
{
public:
    Widget() { set_new_handler(OutOfMem); } // 调用继承模板的函数

    ~Widget() {}

    static void OutOfMem()
    {
        std::cerr << "Unable to satisfy request of for "
                     "memory to widget class\n";
        std::abort();
    }

private:
    int mID;
};

void test_new_handler_fun()
{
    abort();
}

void test_template_new_handler()
{
    Widget::set_new_handler(test_new_handler_fun);
    Widget *widget = new Widget(); 
}

}

int main(int argc, char *argv[])
{
    // test_formal_handler::test_out_of_mem();

    // normal_handler::test_A_normal_handler();

    // normal_handler::test_B_normal_handler();

    // enhance_new_handler::test_enhance_new_handler();

    template_new_handler::test_template_new_handler();

    return 0;
}
