/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef SIMPLECRYPT_H
#define SIMPLECRYPT_H

#include <QString>
#include <QVector>
#include <QFlags>

#include "baseencrypt.h"

/**
  * @brief   this simplecrypt class copy from https://wiki.qt.io/Simple_encryption_with_SimpleCrypt
  * @author  liushixiong (635672377@qq.com)
  * @version 0.01
  * @date    2015/12/19
  */
class SimpleCrypt : public BaseEncrypt
{
public:
    enum CompressionMode {
        CompressionAuto,
        CompressionAlways,
        CompressionNever
    };

    enum IntegrityProtectionMode {
        ProtectionNone,

        ProtectionChecksum,

        ProtectionHash
    };

    enum Error {
        ErrorNoError,         /*!< No error occurred. */
        ErrorNoKeySet,        /*!< No key was set. You can not encrypt or decrypt without a valid key. */
        ErrorUnknownVersion,  /*!< The version of this data is unknown, or the data is otherwise not valid. */
        ErrorIntegrityFailed, /*!< The integrity check of the data failed. Perhaps the wrong key was used. */
    };

    SimpleCrypt();

    explicit SimpleCrypt(quint64 key);

    QString Encrypt(const QString &pEncryptStr);

    QString Decrypt(const QString &pDecryptStr);

    void setKey(quint64 key);

    bool hasKey() const {return !m_keyParts.isEmpty();}

    void setCompressionMode(CompressionMode mode) {m_compressionMode = mode;}

    CompressionMode compressionMode() const {return m_compressionMode;}

    void setIntegrityProtectionMode(IntegrityProtectionMode mode) {m_protectionMode = mode;}

    IntegrityProtectionMode integrityProtectionMode() const {return m_protectionMode;}

    Error lastError() const {return m_lastError;}

    QString encryptToString(const QString& plaintext) ;

    QString encryptToString(QByteArray plaintext) ;

    QByteArray encryptToByteArray(const QString& plaintext) ;

    QByteArray encryptToByteArray(QByteArray plaintext) ;

    QString decryptToString(const QString& cyphertext) ;

    QByteArray decryptToByteArray(const QString& cyphertext) ;

    QString decryptToString(QByteArray cypher) ;

    QByteArray decryptToByteArray(QByteArray cypher) ;

    enum CryptoFlag{CryptoFlagNone = 0,
                    CryptoFlagCompression = 0x01,
                    CryptoFlagChecksum = 0x02,
                    CryptoFlagHash = 0x04
                   };
    Q_DECLARE_FLAGS(CryptoFlags, CryptoFlag);

private:
    void splitKey();

    quint64 m_key;

    QVector<char> m_keyParts;

    CompressionMode m_compressionMode;

    IntegrityProtectionMode m_protectionMode;

    Error m_lastError;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(SimpleCrypt::CryptoFlags)

#endif // SimpleCrypt_H
