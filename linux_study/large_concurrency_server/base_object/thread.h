#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <boost/function.hpp>

class Thread
{
public:
	typedef boost::function<void ()> ThreadFunc;
	explicit Thread(const ThreadFunc &Func);

	void Start();
	void Join();

	void SetAutoDelete(bool autoDelete);

private:
	static void *ThreadRoutine(void *arg);
	void Run();

private:
	ThreadFunc mFunc;
	pthread_t mThreadID;
	bool mAutoDelete;

};

#endif //_THREAD_H_
