/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef baseencrypt_h
#define baseencrypt_h

#include <QtCore/QObject>

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

    virtual void Init();

    virtual QString Encrypt(const QString &pEncryptStr) = 0;

    virtual QString Decrypt(const QString &pDecryptStr) = 0;

};

#endif //baseencrypt_h
