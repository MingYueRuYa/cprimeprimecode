/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 单例模式：全局保持唯一实例
* 饿汗：提前分配内存，但是会造成启动稍微延迟。但是是多线程安全的
* 懒汉：调用到的时候才会分配内存，延迟分配内存的，多线程不安全
* 全局变量，全局静态变量，静态的成员变量都是在主程序之前就已经初始化完成，所谓的静态初始化
* 但是局部静态变量（包括自定义类型），是在第一次调用的时候再会进行初始化操作
* 局部静态变量为什么线程不安全：这是由局部静态变量的实际实现所决定的。
* 为了能满足局部静态变量只被初始化一次的需求，很多编译器会通过一个全局的标志位记录该静态变量是否已经被初始化的信息下面是伪代码
* bool flag = false;
* if (!flag)
* {
*     flag = true;
*     staticVar = initStatic();
* }

*#ifndef SINGLETON_DIFINE_H_
*#define SINGLETON_DIFINE_H_
*
*单例模式宏
*   #define SINGLETON(_CLASS_)                  \
*   public:                                     \
*   inline static _CLASS_& GetInstance()    \
*   {                                       \
*       static _CLASS_ s_instance;              \
*       return s_instance;                      \
*    }                                       \
*   private:                                    \
*   _CLASS_();                              \
*   _CLASS_(_CLASS_ const&){}               \
*   _CLASS_& operator= (_CLASS_ const&){return *this;}  \
*   ~_CLASS_();                             \
*
*   单例模式默认构造函数与析构函数（配合单例模式宏使用）
*   #define SINGLETON_C_D(_CLASS_)      \
*   _CLASS_::_CLASS_(){}            \
*   _CLASS_::~_CLASS_(){}           \
*
*   #endif //SINGLETON_DIFINE_H_
*   用法：
*       class Example
*       {
*           SINGLETON(Example);
*       };
*/

#ifndef singleton_h
#define singleton_h

#include <string>
#include <mutex>
#include <iostream>

using std::cout;
using std::endl;
using std::mutex;
using std::string;

namespace singleton
{
template <typename T>
class Singleton
{
public:
	// 1.为什么返回引用类型 --> 
	// 此内存是由Singleton自己管理，外界不需要知道具体的细节问题
    static T& Instance()
    {
        if (NULL == mInstance )
        {
            mMutex.lock();
            if (NULL == mInstance) {
                mInstance = new T();
				// 3.为什么调用atexit函数 --> 
				// 一是为了能释放资源，二是减轻用户责任不要用户在手动调用释放资源的函数
                atexit(Destroy); 
            }
            mMutex.unlock();
            return *mInstance;
        }
        return *mInstance;
    }

protected:
    Singleton(void) {}
    virtual ~Singleton(void) {}

private:
    Singleton(const Singleton& rhs) {}
    Singleton& operator = (const Singleton& rhs) { return *this; }

    static void Destroy()
    {
        if (mInstance == NULL) { return; }

        delete mInstance;
        mInstance = NULL;
    }

	// 2.为什么加上volatile关键字 --> 
	// 确保多线程每次从内存中取值，而不是从寄存器中取值
    static T* volatile mInstance;
    static mutex mMutex;
};

template <typename T>
T* volatile Singleton<T>::mInstance = NULL;

template <typename T>
mutex Singleton<T>::mMutex;

#define SINGLETON_INHERIT(CLASSNAME) singleton::Singleton<CLASSNAME>
#define SINGLETON_INSTANCE(CLASSNAME)  \
								singleton::Singleton<CLASSNAME>::Instance()
#define DECLARE_FRIEND_SINGLETON(CLASSNAME)	\
						private: friend class singleton::Singleton<CLASSNAME>;
#define DECLARE_PRIVATE_CONSTRUCTOR(CLASSNAME, INIT_FUNCTION) 	\
					private: \
					CLASSNAME() { INIT_FUNCTION(); } \
					CLASSNAME(const CLASSNAME &) = delete; \
					CLASSNAME& operator =(const CLASSNAME &) = delete;

class DemoSingleton : public SINGLETON_INHERIT(DemoSingleton)
{
	// 如果不想传递初始化函数，可以传递void
	DECLARE_PRIVATE_CONSTRUCTOR(DemoSingleton, Initialiaze)
	DECLARE_FRIEND_SINGLETON(DemoSingleton)

public:
	~DemoSingleton() {}
    void Show() { cout << "this is demo singleton." << endl; }
    void Test() { cout << "this is test test demo singleton." << endl; }
	void Initialiaze() { cout << "I am init." << endl; }
};
    
    static void test_singleton()
    {
        cout << "######################################\n" \
                "##  this is singleton demo...       ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

		SINGLETON_INSTANCE(DemoSingleton).Test();
    }
};

#endif //singleton_h
