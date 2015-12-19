/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef taesclass_h 
#define taesclass_h 

#include "aesencrypt.h"

class TAesClass
{
 public:
    TAesClass();

    ~TAesClass();

    /*!
    *AES 密钥初始化
    * */
    void InitializePrivateKey(DWORD KeySize, UCHAR *KeyBytes); 

    /*!
    * AES 加密数据
    * */
    DWORD OnAesEncrypt(LPVOID InBuffer, DWORD InLength, LPVOID OutBuffer);            

    /*!
     * AES 解密数据
     * */
    DWORD OnAesUncrypt(LPVOID InBuffer, DWORD InLength, LPVOID OutBuffer);            

private:
    AesEncrypt *mAes;

};


#endif //taesclass_h 
