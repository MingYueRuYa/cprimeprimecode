/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef baseencrypt_h
#define baseencrypt_h

#include <QtCore/QObject>

typedef unsigned long DWORD;
typedef unsigned char UCHAR,*PUCHAR;
typedef void *PVOID,*LPVOID;
typedef unsigned char byte;
typedef DWORD *PDWORD,*LPDWORD;

/**
  * @brief   encrypt base class
  * @author  liushixiong (635672377@qq.com)
  * @version 0.01
  * @date    2015/12/17
  */
class BaseEncrypt : public QObject
{
	Q_OBJECT

public:
	BaseEncrypt();

	virtual ~BaseEncrypt();

    virtual void Init(DWORD KeySize, UCHAR *KeyBytes);

    virtual QString Encrypt(const QString &pEncryptStr) = 0;

    virtual QString Decrypt(const QString &pDecryptStr) = 0;

};

#endif //baseencrypt_h
