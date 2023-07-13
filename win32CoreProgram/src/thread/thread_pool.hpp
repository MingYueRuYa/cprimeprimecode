/****************************************************************************
**
** Copyright (C) 2023 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

// 1、如何封装一个any类型
// 2、线程间如何通信
// 3、万能的函数如何封装

#include <mutex>

namespace ThreadPool
{
// any类型
class Any
{
public:
    Any() = default;
    ~Any() = default;
    Any(const Any&) = delete;
    Any& operator=(const Any&) = delete;
   /* Any(Any&& any) = default;
    Any& operator=(Any&&) = default;*/

    template<typename T>
    Any(T data) : base_(std::make_unique<Derive<T>>(data))
    {
    }

    template<typename T>
    T cast_()
    {
		Derive<T>* pd = dynamic_cast<Derive<T> *>(base_.get());
        if (pd == nullptr)
        {
            throw "type is unmatch";
        }

        return pd->data_;
    }

private:
    class Base
    {
    public:
        virtual ~Base() = default;
    };


    template<typename T>
    class Derive : public Base 
    {
    public:
        Derive(T data) : data_(data)
        {}
        T data_;
    };

private:
    std::unique_ptr<Base> base_;
};

void test_any()
{
    Any any_1(10);
    int value = any_1.cast_<int>();

    Any any_2(std::string("linux"));
    std::string str = any_2.cast_<std::string>();
}

}