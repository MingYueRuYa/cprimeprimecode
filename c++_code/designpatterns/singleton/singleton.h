/*
 * 单例模式
 * */
#include <mutex>

class Singleton
{
public:
	static Singleton *GetInstance();

private:
	Singleton();

	~Singleton();

private:
	static Singleton *mThis;

	static std::mutex *mMutex;

private:
	std::mutex mTempMutex;
};

