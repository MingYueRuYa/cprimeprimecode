/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 代理模式：为其他对象提供代理以控制这个对象的访问。远程代理，虚代理，保护代理，智能引用
* 考虑一个可以在文档中嵌入图形对象的文档编辑器。有些图形对象的创建开销很大。但是打开文档必须很迅速，
* 因此我们在打开文档时应避免一次性创建所有开销很大的对象。
* 这里就可以运用代理模式，在打开文档时，并不打开图形对象，而是打开图形对象的代理以替代真实的图形。待到真正需要打开图形时，仍由代理负责打开
*/

#ifndef proxy_h
#define proxy_h

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

namespace proxy
{
class Image
{
public:
    Image(const string &pName) : mName(pName) {}

    virtual ~Image() {}

    virtual void Show() {}

protected:
    string mName;
};

class BigImage : public Image
{
public:
    BigImage(const string &pName) : Image(pName) {}

    ~BigImage() {}

    void Show()
    {
        cout << "show big image, " << this->mName << endl;
    }
};

class ImageProxy : public Image
{
public:
    ImageProxy(const string &pName) : Image(pName) 
    {
        mImage = new BigImage(pName);
    }

    virtual ~ImageProxy() 
    {
        if (NULL == mImage) { return; }
        delete mImage;
        mImage = NULL;
    }

    void Show()
    {
        if (NULL == mImage) { return; }
        mImage->Show();
    }

private:
    Image *mImage;
};


    static void test_proxy()
    {
        cout << "######################################\n" \
                "##  this is proxy demo...           ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        Image *test_image = new ImageProxy("big image proxy.");
        test_image->Show();
    }

};

#endif //proxy_h