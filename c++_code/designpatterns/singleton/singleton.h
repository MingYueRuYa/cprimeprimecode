/*
 * 单例模式
 * */
//#include <mutex>

class Singleton
{
public:
	//static Singleton *GetInstance();

	static Singleton &GetInstance();

	~Singleton();

private:
	Singleton();

	Singleton(const Singleton &pSingleton);

	Singleton& operator=(const Singleton &pSingleton);

//private:
//	static Singleton *mThis;
//
//	static std::mutex *mMutex;

//private:
//	std::mutex mTempMutex;
};

