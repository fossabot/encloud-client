#pragma once

#include "globalmarco.h"
#include "globaldatamanager.h"
#include <QObject>
#include <QDebug>

class CryptographyManager : public QObject{
    Q_OBJECT
public:
    enum SYM_ALGORITHM{
        AES_128_ECB,
        AES_128_CBC
    };
    enum ASY_ALGORITHM{
        RSA_1024,
        RSA_2048
    };
    enum HASH_ALGORITHM{
        MD5
    };

//非静态成员
private:
    explicit CryptographyManager(QObject *parent = nullptr);
public:
    QByteArray  symKeyGenerate(SYM_ALGORITHM method);
    QByteArray  symEncipher(SYM_ALGORITHM method, const QByteArray *data, const QByteArray *key, const QByteArray *iv = NULL);
    QByteArray  symDecipher(SYM_ALGORITHM method, const QByteArray *data, const QByteArray *key, const QByteArray *iv = NULL);

    KeyPair     asyKeyGenerate(ASY_ALGORITHM method);
    QByteArray  asyEncipher(ASY_ALGORITHM method, const QByteArray *data, const QByteArray *key, const QByteArray *iv = NULL);
    QByteArray  asyDecipher(ASY_ALGORITHM method, QByteArray *data, const QByteArray *key, const QByteArray *iv = NULL);

    QByteArray  calcHashCode(HASH_ALGORITHM method, const QByteArray *data);
    QByteArray  calcHashCode(HASH_ALGORITHM method, QIODevice *device);
private:


//静态成员
public:
    static CryptographyManager *self();
private:
    static CryptographyManager *s_crytoMgr;


signals:

};


