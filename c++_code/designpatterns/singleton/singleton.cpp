#include <iostream>

#include "singleton.h"

using std::cout;
using std::endl;

//饿汉模式
//Singleton *Singleton::mThis = new Singleton();
//
//Singleton *Singleton::GetInstance()
//{
//	return mThis;
//}
//
//Singleton::Singleton()
//{
//	cout << "Singleton Initiallize..." << endl;
//}
//
//Singleton::~Singleton()
//{
//	cout << "Singleton Finalization..." << endl;
//}
//

//懒汉模式
Singleton *Singleton::mThis = NULL;
std::mutex *Singleton::mMutex = new std::mutex();

Singleton *Singleton::GetInstance()
{
	//这里存在 double-check，是为了提高效率
	if (mThis == NULL) {
		mMutex->lock();		//多线程访问控制
		//再判断一次是否为空
		if (mThis == NULL) {
			mThis = new Singleton();
		}
		mMutex->unlock();
	}
	return mThis;
}

Singleton::Singleton()
{
	cout << "Singleton Initiallize..." << endl;
}

Singleton::~Singleton()
{
	cout << "Singleton Finalization..." << endl;
	if (mMutex) {
		delete mMutex;
		mMutex = NULL;
	}
	if (mThis) {
		delete mThis;
		mThis = NULL;
	}
}

