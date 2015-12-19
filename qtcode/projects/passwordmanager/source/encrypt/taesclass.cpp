/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include "taesclass.h"

TAesClass::TAesClass()
{
    mAes = NULL;
    //InitializePrivateKey(16, (unsigned char*)"\x79\x76\x68\x6B\x77\x66\x6E\x68\x72\x65\x73\x63\x6C\x6B\x70\x6E");
}

TAesClass::~TAesClass()
{
    if (NULL != mAes) {
        delete mAes;
        mAes = NULL;
    }
}

void TAesClass::InitializePrivateKey(DWORD KeySize, UCHAR *KeyBytes)
{
    if (mAes) {
        delete mAes;
        mAes = NULL;
    }
    mAes = new AesEncrypt(KeySize, KeyBytes);
}

DWORD TAesClass::OnAesEncrypt(LPVOID InBuffer, DWORD InLength, LPVOID OutBuffer)
{
    DWORD OutLength=0;
    if (NULL == mAes || NULL == OutBuffer) {
        return 0;
    }

    UCHAR *lpCurInBuff = (UCHAR *)InBuffer;
    UCHAR *lpCurOutBuff = (UCHAR *)OutBuffer;
    long blocknum = InLength / 16;
    long leftnum = InLength % 16;
    for(long i=0; i<blocknum; i++) {
        mAes->Cipher(lpCurInBuff, lpCurOutBuff);
        lpCurInBuff += 16;
        lpCurOutBuff += 16;
        OutLength += 16;
    }
		//多余出leftnum 字节 则加密时 多出16-leftnum 个字节
    if(leftnum) {
        UCHAR inbuff[16];
        memset(inbuff, 0, 16);
        memcpy(inbuff, lpCurInBuff, leftnum);
        mAes->Cipher(inbuff, lpCurOutBuff);
        lpCurOutBuff += 16;
        OutLength += 16;
    }
    //新增16个字节，用以确定增加的字节数
    UCHAR extrabuff[16];
    memset(extrabuff, 0, 16);
    *((LPDWORD)extrabuff) = 16 + (16 - leftnum) % 16; //多出16+(16-leftnum)%16个字节
    mAes->Cipher(extrabuff, lpCurOutBuff);
    OutLength += 16;
    return OutLength;
}

DWORD TAesClass::OnAesUncrypt(LPVOID InBuffer, DWORD InLength, LPVOID OutBuffer)
{
    DWORD OutLength = 0;
    if (NULL == mAes || NULL == OutBuffer) {
        return 0;
    }
    UCHAR *lpCurInBuff = (UCHAR *)InBuffer;
    UCHAR *lpCurOutBuff = (UCHAR *)OutBuffer;
    long blocknum = InLength / 16;
    long leftnum = InLength % 16;
    if (leftnum) {
        return 0;
    }
    for(long i = 0; i < blocknum; i++)
    {
        mAes->InvCipher(lpCurInBuff,lpCurOutBuff);
        lpCurInBuff += 16;
        lpCurOutBuff += 16;
        OutLength += 16;
    }

    UCHAR *lpExtraInBuff = lpCurOutBuff - 16;
    DWORD dwExtraBytes = *((LPDWORD)lpExtraInBuff);
    return (OutLength - dwExtraBytes);
}
