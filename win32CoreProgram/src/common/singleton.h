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

namespace XIBAO {

#define SINGLETON_INHERIT(CLASSNAME) \
								public XIBAO::singleton::Singleton<CLASSNAME>

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