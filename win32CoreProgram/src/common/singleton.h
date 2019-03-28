/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef singleton_h
#define singleton_h

#include <mutex>

using std::mutex;

// 所谓的单例模式，还是无法完全禁止用创建对象
// 比如：

// DemoSingleton *s = (DemoSingleton *)malloc(sizeof(DemoSingleton));
// s->showName();
// s->~DemoSingleton();	//手动调用析构函数
// free(s);
// s = nullptr;
// 

/*
	usage:
	Singleton<DemoSingleton>::Instance("liushixiong");
	SINGLETON_GET_INSTANCE(DemoSingleton).showName();
*/

namespace XIBAO {

#define SINGLETON_INHERIT(CLASSNAME) \
								public XIBAO::singleton::Singleton<CLASSNAME>

#define SINGLETON_GET_INSTANCE(CLASSNAME) \
					XIBAO::singleton::Singleton<CLASSNAME>::GetInstance()

#define SINGLETON_INSTANCE(CLASSNAME) \
					XIBAO::singleton::Singleton<CLASSNAME>::Instance()

#define DECLARE_FRIEND_SINGLETON(CLASSNAME)	\
						private: \
							friend class XIBAO::singleton::Singleton<CLASSNAME>;

#define DECLARE_PRIVATE_CONSTRUCTOR(CLASSNAME, INIT_FUNCTION) 	\
				private: \
				CLASSNAME() { INIT_FUNCTION(); } \
				CLASSNAME(const CLASSNAME &) {} \
				CLASSNAME& operator =(const CLASSNAME &) { return *this; }

namespace singleton
{
template <typename T>
class Singleton
{
public:
	/*
    static T& Instance()
    {
        if (NULL == mInstance )
        {
            mMutex.lock();
            if (NULL == mInstance) {
                mInstance = new T();
                atexit(Destroy); 
            }
            mMutex.unlock();
            return *mInstance;
        }
        return *mInstance;
    }
	*/

	template<typename... Args>
	static T& Instance(Args&&... args)
	{
        if (NULL == mInstance )
        {
            mMutex.lock();
            if (NULL == mInstance) {
                mInstance = new T(std::forward<Args>(args)...);
                atexit(Destroy); 
            }
            mMutex.unlock();
            return *mInstance;
        }
        return *mInstance;
	}

	static T& GetInstance()
	{
		if (nullptr == mInstance) {
			throw std::logic_error("the instance is not init, "\
									"please initialize the instance first");
		}

		return *mInstance;
	}

protected:
    Singleton(void) {}
    virtual ~Singleton(void) {}

private:
    Singleton(const Singleton& rhs) {}
    Singleton& operator= (const Singleton& rhs) { return *this; }

    static void Destroy()
    {
        if (mInstance == NULL) { return; }

        delete mInstance;
        mInstance = NULL;
    }

    static T* volatile mInstance;
    static mutex mMutex;
};

template <typename T>
T* volatile Singleton<T>::mInstance = NULL;

template <typename T>
mutex Singleton<T>::mMutex;
}
}

#endif //singleton_h