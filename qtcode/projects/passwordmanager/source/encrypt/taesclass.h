#ifndef TAESCLASS_H
#define TAESCLASS_H

#include "aes.h"


class TAesClass
 {
 public:
     TAesClass();
     ~TAesClass();
   void InitializePrivateKey(DWORD KeySize,UCHAR *KeyBytes); //AES 密钥初始化
     DWORD OnAesEncrypt(LPVOID InBuffer,DWORD InLength,LPVOID OutBuffer);            //AES 加密数据
     DWORD OnAesUncrypt(LPVOID InBuffer,DWORD InLength,LPVOID OutBuffer);            //AES 解密数据
 private:
     Aes *m_lpAes;
 };


#endif // TAESCLASS_H
