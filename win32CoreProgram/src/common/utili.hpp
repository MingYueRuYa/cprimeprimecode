/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include <memory>

using std::shared_ptr;

namespace std
{

// 自定义数组shared_ptr
template <typename T>
shared_ptr<T> make_shared_array(size_t size)
{
    //default_delete是STL中的默认删除器
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}


// 对指针解引用进行判断大小
template <typename T>
struct LessDerefrence : 
    public std::binary_function<const T *, const T *, bool>
{
    bool operator()(const T * param1, const T *param2) const
    {
        return *param1 < *param2;
    }
};


// 对指针对象进行解引用
struct Derefrence
{
    template <typename T>
    const T& operator()(const T *ptr) const
    {
        return *ptr;
    }
};


}; // std