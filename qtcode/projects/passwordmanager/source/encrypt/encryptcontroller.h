
#ifndef encryptcontroller_h
#define encryptcontroller_h

#include <QtCore/QObject>

#include "baseencrypt.h"

class EncryptController : public QObject
{
public:
    ~EncryptController();

    /*!
     * according to encryption name(ex, aes, md5, res) return subencrypt class
     * */
    BaseEncrypt *GetBaseEncrypt(const QString &pEncryptName);

    /*!
     * notice: attention multithread.
     * */
    static EncryptController *__Instance();

private:
	EncryptController();

private:
    static EncryptController *mThis;

	BaseEncrypt *mBaseEncrypt;

};
#endif //encryptcontroller_h 
