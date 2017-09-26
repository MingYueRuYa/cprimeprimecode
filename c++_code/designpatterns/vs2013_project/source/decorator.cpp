/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 装饰者模式：动态的给子类添加功能。避免继承带来的膨胀问题
*
*
*/

#ifndef decorator_h
#define decorator_h

#include <iostream>
#include <string>

using std::cout;
using std::endl;

namespace decorator
{
class Phone
{
public:
    Phone() {}

    ~Phone() {}

    virtual void Show() {}

};

class IPhone : public Phone
{
public:
    IPhone() {}

    ~IPhone() {}

    virtual void Show() 
    {
        cout << "this is iphone show." << endl;
    }
};

class FirefoxPhone : public Phone
{
public:
    FirefoxPhone() {}

    ~FirefoxPhone() {}

    virtual void Show() 
    {
        cout << "this is Firefox phone show." << endl;
    }
};

class DecoratorPhone : public Phone
{
public:
    DecoratorPhone() {}

    ~DecoratorPhone() {}

    virtual void Show() {}

protected:
    Phone *mPhone;

};

class PendantPhone : public DecoratorPhone
{
public:
    PendantPhone(Phone *pPhone)
    {
        mPhone = pPhone;
    }

    ~PendantPhone() {}

    virtual void Show()
    {
        cout << "add pendant...";
        mPhone->Show();
    }
};

class StickersPhone : public DecoratorPhone
{
public:
    StickersPhone(Phone *pPhone)
    {
        mPhone = pPhone;
    }

    ~StickersPhone() {}

    virtual void Show()
    {
        cout << "add stickers...";
        mPhone->Show();
    }
};

    static void test_decorator()
    {
        cout << "######################################\n" \
                "##  this is decorator demo...       ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        IPhone *iphone = new IPhone();
        PendantPhone *pendantphone = new PendantPhone(iphone); //给IPhone加上配件
        pendantphone->Show();

        StickersPhone *stickerphone = new StickersPhone(pendantphone); //加上配件和贴纸
        stickerphone->Show();
    }

};

#endif //decorator_h
