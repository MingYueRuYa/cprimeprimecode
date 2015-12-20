/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include "encryptcontroller.h"
#include "simplecrypt.h"

EncryptController *EncryptController::mThis = NULL;

EncryptController::~EncryptController()
{
	if (NULL != mThis) {
		delete mThis;
		mThis = NULL;
	}
}

BaseEncrypt *EncryptController::GetBaseEncrypt(const QString &pEncryptName)
{
	if ("simplecrypt" == pEncryptName) {
        return new SimpleCrypt(Q_UINT64_C(0x0c2ad4a4acb9f023));
	} 
}


EncryptController::EncryptController()
{
}

EncryptController *EncryptController::__Instance()
{
  if (NULL == mThis) {
    mThis = new EncryptController();
    return mThis;
  } else {
	return mThis;
  }
}

