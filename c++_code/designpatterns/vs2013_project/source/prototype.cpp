/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
 * 原型模式： 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
 * Prototype 的意义在于，你拿到一个 Base* ，它指向某个 Derived 对象，你想克隆出 Derived 对象，
 * 但代码中不写出 Derived 的具体类型，因为有很多派生类，这种情况下你用构造函数是搞不定的，type-switch 是 bad smells
 * 1、为什么不用new直接新建对象，而要用原型模式？
 * 首先，用new新建对象不能获取当前对象运行时的状态，其次就算new了新对象，在将当前对象的值复制给新对象，效率也不如原型模式高。
 * 2、为什么不直接使用拷贝构造函数，而要使用原型模式？
 * 原型模式与拷贝构造函数是不同的概念，拷贝构造函数涉及的类是已知的，原型模式涉及的类可以是未知的（基类的拷贝构造函数只能复制得到基类的对象）。
 * 原型模式生成的新对象可能是一个派生类。拷贝构造函数生成的新对象只能是类本身。
 * 原型模式是描述了一个通用方法(或概念)，它不管是如何实现的，而拷贝构造则是描述了一个具体实现方法。
 * 三、使用场景
    1、资源优化场景类初始化需要消化非常多的资源，这个资源包括数据、硬件资源等。
    2、性能和安全要求的场景通过new产生一个对象需要非常繁琐的数据准备或访问权限，则可以使用原型模式。
    3、一个对象多个修改者的场景一个对象需要提供给其他对象访问，而且各个调用者可能都需要修改其值时，可以考虑使用原型模式拷贝多个对象供调用者使用。
    4、结合使用在实际项目中，原型模式很少单独出现，一般是和工厂方法模式一起出现，通过clone的方法创建一个对象，然后由工厂方法提供给调用者。原型模式已经与Java融为浑然一体，大家可以随手拿来使用。
   四、缺点
    1、配备克隆方法需要对类的功能进行通盘考虑，这对于全新的类不是很难，但对于已有的类不一定很容易，特别当一个类引用不支持串行化的间接对象，或者引用含有循环结构的时候。 
    2、实现原型模式每个派生类都必须实现 Clone接口。 
    3、逃避构造函数的约束。
 */

#ifndef prototype_h
#define prototype_h

#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

namespace prototype 
{
class Resume
{
public:
    Resume() {}

    Resume(const Resume &pResume) = delete;

    Resume &operator=(const Resume &pResume) = delete;

    virtual ~Resume() 
    {
        cout << "resume ctor..." << endl;
        if (NULL == name) {
            return;
        }
        delete []name;
        name = NULL;
    }

    virtual Resume *Clone() = 0;

    char *GetName()
    {
        return name;
    }

protected:
    char *name;

};

class ResumeA : public Resume
{
public:
    ResumeA(const char *pName)
    {
        if (NULL == pName) {
            name = new char[1];
            *name = '\0';
        } else {
            int length = strlen(pName) + 1;
            name = new char[length];
            strncpy(name, pName, length);
        }
    }

    ResumeA(const ResumeA &pResume)
    {
        if (NULL == pResume.name) {
            name = new char[1];
            *name = '\0';
        } else {
            int length = strlen(pResume.name) + 1;
            name = new char[length];
            strncpy(name, pResume.name, length);
        }
    }

    ResumeA &operator=(const ResumeA &pResume) = delete;

    ~ResumeA() 
    {
        cout << name << " ctor..." << endl;
        if (NULL == name) {
            return;
        }
        delete []name;
        name = NULL;
    }

    ResumeA *Clone()
    {
        return new ResumeA(*this);
    }

};

class ResumeB : public Resume
{
public:
    ResumeB(const char *pName)
    {
        if (NULL == pName) {
            name = new char[1];
            *name = '\0';
        }
        else {
            int length = strlen(pName) + 1;
            name = new char[length];
            strncpy(name, pName, length);
        }
    }

    ResumeB(const ResumeB &pResume)
    {
        if (NULL == pResume.name) {
            name = new char[1];
            *name = '\0';
        }
        else {
            int length = strlen(pResume.name) + 1;
            name = new char[length];
            strncpy(name, pResume.name, length);
        }
    }

    ResumeB &operator=(const ResumeB &pResume) = delete;

    ~ResumeB()
    {
        cout << name << " ctor..." << endl;

        if (NULL == name) {
            return;
        }
        delete[]name;
        name = NULL;
    }

    ResumeB *Clone()
    {
        return new ResumeB(*this);
    }

};

static void test_prototype()
{
    cout << "######################################\n" \
            "##  this is prototype demo..        ##\n" \
            "##                                  ##\n" \
            "######################################"   \
        << endl;

    Resume *resume_a = new ResumeA("resume_a");
    cout << "resume_a name:" << resume_a->GetName() << endl;    

    Resume *resume_a2 = resume_a->Clone();
    cout << "resume_a2 name:" << resume_a2->GetName() << endl;    

    delete resume_a;
    resume_a = NULL;
    delete resume_a2;
    resume_a2 = NULL;

    Resume *resume_b = new ResumeB("resume_b");
    cout << "resume_b name:" << resume_b->GetName() << endl;    

    Resume *resume_b2 = resume_b->Clone();
    cout << "resume_b2 name:" << resume_b2->GetName() << endl;    

    delete resume_b;
    resume_b = NULL;
    delete resume_b2;
    resume_b2 = NULL;
}
};

#endif //prototype_h
