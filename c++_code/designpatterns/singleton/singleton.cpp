/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

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
//

//以静态的局部变量，效率较高，同时没有多线程的问题，这种方式的单例模式最简单高效的
Singleton& Singleton::GetInstance()
{
	static Singleton singleton;
	return singleton;
}

//懒汉模式
//Singleton *Singleton::mThis = NULL;
//std::mutex *Singleton::mMutex = new std::mutex();

//Singleton *Singleton::GetInstance()
//{
//	//这里存在 double-check，是为了提高效率
//	if (mThis == NULL) {
//		mMutex->lock();		//多线程访问控制
//		//再判断一次是否为空
//		if (mThis == NULL) {
//			mThis = new Singleton();
//		}
//		mMutex->unlock();
//	}
//	return mThis;
//}
//
Singleton::Singleton()
{
	cout << "Singleton Initiallize..." << endl;
}

Singleton::~Singleton()
{
	cout << "Singleton Finalization..." << endl;
//	if (mMutex) {
//		delete mMutex;
//		mMutex = NULL;
//	}
//	if (mThis) {
//		delete mThis;
//		mThis = NULL;
//	}
}

Singleton::Singleton(const Singleton &pSingleton)
{
}

Singleton& Singleton::operator=(const Singleton &pSingleton)
{
	return *this;
}
