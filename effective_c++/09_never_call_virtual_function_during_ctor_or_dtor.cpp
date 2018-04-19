#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
 * 不要在父类的构造和析构函数中调用虚函数
 * */
namespace CallVirutalInBase
{

class Base
{
public:
    Base() 
    {
        LogInfo();
    }

    ~Base() 
    {
        LogInfoDtor();
    }

    virtual void LogInfo()
    {
        cout << "base log info." << endl;
    }

    virtual void LogInfoDtor()
    {
        cout << "base log info for dctor." << endl;
    }

};

class Drive : public Base
{
public:
    explicit Drive() 
    {
    }
    ~Drive() {}

    virtual void LogInfo()
    {
        cout << "drive log info." << endl;
    }

    virtual void LogInfoDtor()
    {
        cout << "drive log info." << endl;
    }
};

void test_call_virtual_in_base()
{
    Drive drive;
    // base log info
    // base log info for dtor

}

}

/*
 * 但是有时候需要在父类中调用一些函数，此时不要将函数声明为虚函数
 * */
namespace CallInBase
{
class Base
{
public:
    Base(const string& pLogInfo)
    {
        LogInfo(pLogInfo);
    }

    ~Base() {}

     void LogInfo(const string& pLogInfo) const
    {
        cout << pLogInfo << endl;
    }

};

class Drive : public Base
{
public:
    Drive() : Base(CreateLogInfo())
    {
    }

    ~Drive() {}

private:
    // 声明为static是为了避免base未构造完成，drive内部成员也肯定是
    // 没有构造好，不能使用drive内部成员变量
    static string CreateLogInfo()
    {
        return "create by drive log info.";
    }

};

void test_call_in_base()
{
    Drive drive;
    // create by drive log info.
}

}


int main(int argc, char *argv[])
{
    // CallVirutalInBase::test_call_virtual_in_base();

    CallInBase::test_call_in_base();

    return 0;
}
