#include "thread.h"

Thread::Thread(const ThreadFunc &Func)
	: mFunc(Func), mAutoDelete(false)
{
}

void Thread::Start()
{
	pthread_create(&mThreadID, NULL, ThreadRoutine, this);
}

void Thread::Join()
{
	pthread_join(mThreadID, NULL);
}

void Thread::SetAutoDelete(bool autoDelete)
{
	mAutoDelete = autoDelete;
}

void *Thread::ThreadRoutine(void *arg)
{
	Thread *thread = (Thread *)(arg);
	thread->Run();
	if (thread->mAutoDelete) {
		delete thread;
	}
	return NULL;
}

void Thread::Run()
{
	mFunc();
}
