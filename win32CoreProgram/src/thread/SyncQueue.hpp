/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef syncqueue_h
#define syncqueue_h

#include <list>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

using std::cout;
using std::endl;
using std::list;
using std::mutex;
using std::thread;
using std::lock_guard;
using std::unique_lock;
using std::condition_variable;

template <typename T>
class SyncQueue
{
public:
	SyncQueue(int size) : mSize(size) {}

	void Put(const T &data)
	{
//		lock_guard<mutex> lock(mMutex);
//		while (IsEmpty()) {
//			cout << "Sync queue is full" << endl;
//			mNotFullCondVar.wait(mMutex);
//		}

		unique_lock<mutex> locker(mMutex);
		// 这种lambda表达式，每次都会执行
		// 而上面的while循环，并不是每次都会执行里面的循环体
		mNotFullCondVar.wait(locker, [this] { 
			return ! IsFull(); 
		});
		mList.push_back(data);
		mNotEmptyCondVar.notify_one();
	}

	void Take(T &data)
	{
//		lock_guard<mutex> lock(mMutex);
//		while (IsEmpty()) {
//			cout << "Sync queue is empty" << endl;
//			mNotEmptyCondVar.wait(mMutex);
//		}
		unique_lock<mutex> locker(mMutex);
		// 这种lambda表达式，每次都会执行
		// 而上面的while循环，并不是每次都会执行里面的循环体
		mNotEmptyCondVar.wait(locker, [this] {
			return ! IsEmpty();
		});

		data = mList.front();
		mList.pop_front();
		mNotFullCondVar.notify_one();
	}

	size_t Size()
	{
		lock_guard<mutex> lock(mMutex);
		return mList.size();
	}

	size_t Count()
	{
		return mList.count();
	}

	bool Empty()
	{
		lock_guard<mutex> lock(mMutex);
		return IsEmpty();
	}

	bool Full()
	{
		lock_guard<mutex> lock(mMutex);
		return IsFull();
	}

private:
	bool IsFull()
	{
		return mList.size() == mSize;
	}

	bool IsEmpty()
	{
		return mList.empty();
	}

private:
	int			mSize;
	list<T>		mList;
	mutex		mMutex;
	condition_variable  mNotFullCondVar;
	condition_variable  mNotEmptyCondVar;
};

SyncQueue<int> syncQueue(5);

void PutDatas()
{
	for (int i = 0; i < 20; ++i) {
		syncQueue.Put(i);	
	}
}

void TakeDatas()
{
	int x = 0;
	for (int i = 0; i < 20; ++i) {
		syncQueue.Take(x);
		cout  << x << endl;
	}
}

void TestSyncQueue()
{
	thread t1(PutDatas);
	thread t2(TakeDatas);

	t1.join();
	t2.join();

}

#endif // syncqueue_h
