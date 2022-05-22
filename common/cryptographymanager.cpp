#include "cryptographymanager.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <QCryptographicHash>

CryptographyManager *CryptographyManager::s_crytoMgr = new CryptographyManager();
CryptographyManager::CryptographyManager(QObject *parent)
    : QObject{parent}
{

}

QByteArray CryptographyManager::symKeyGenerate(SYM_ALGORITHM method){
    if(method == AES_128_ECB){
        unsigned char buff[16] = {0};
        RAND_bytes(buff,16);
        return QByteArray((const char*)buff,16);
    }
}

QByteArray CryptographyManager::symEncipher(
        SYM_ALGORITHM method,
        const QByteArray *data,
        const QByteArray *key,
        const QByteArray *iv)
{
    if(data == NULL || key == NULL){
        return QByteArray();
    }

    //初始化
    EVP_CIPHER_CTX *ctx =  EVP_CIPHER_CTX_new();
    unsigned char*   buff       = NULL;//对于大多数加密器来说， 加密输出的大小在[0,dataSize+blackSize]
    int     updateLen  = 0;
    int     finalLen   = 0;

    //加密
    if(method == AES_128_ECB){
        buff = new unsigned char[data->size()+16];
        EVP_EncryptInit_ex(ctx,EVP_aes_128_ecb(), NULL,
                           (unsigned char*)key->data(),
                           iv==NULL?NULL:(unsigned char*)iv->data());
        EVP_EncryptUpdate(ctx, buff, &updateLen,
                          (unsigned char*)data->data(),data->size());
        EVP_EncryptFinal_ex(ctx, buff+updateLen, &finalLen);
    }
    //生成返回对象
    QByteArray forRet((const char*)buff,updateLen+finalLen);

    //释放资源
    if(buff != NULL){
        delete []buff;
    }
    EVP_CIPHER_CTX_free(ctx);

    return forRet;
}

QByteArray CryptographyManager::symDecipher(
        SYM_ALGORITHM method,
        const QByteArray *data,
        const QByteArray *key,
        const QByteArray *iv)
{
    if(data == NULL || key == NULL){
        return QByteArray();
    }
    //初始化资源
    EVP_CIPHER_CTX *ctx =  EVP_CIPHER_CTX_new();
    char    *buff      = NULL;//对于大多数加密器来说， 加密输出的大小在[0,dataSize+blackSize]
    int     updateLen  = 0;
    int     finalLen   = 0;

    //解密
    if(method == AES_128_ECB){
        buff = new char[data->size()];
        EVP_DecryptInit_ex(ctx,EVP_aes_128_ecb(), NULL,
                           (unsigned char*)key->data(),
                           iv==NULL?NULL:(unsigned char*)iv->data());
        EVP_DecryptUpdate(ctx,
                          (unsigned char*)buff, &updateLen,
                          (unsigned char*)data->data(), data->size());
        EVP_DecryptFinal_ex(ctx, (unsigned char*)buff+updateLen, &finalLen);
    }

    //生成返回对象
    QByteArray forRet((const char*)buff,updateLen+finalLen);

    //释放资源

    if(buff != NULL){
        delete []buff;
    }
    EVP_CIPHER_CTX_free(ctx);
    return forRet;
}

KeyPair CryptographyManager::asyKeyGenerate(ASY_ALGORITHM method){
    if(method == RSA_1024){
        //初始化
        EVP_PKEY_CTX * ctx  =   EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
        BIO *bp_publicKey   =   BIO_new(BIO_s_mem());
        BIO *bp_privateKey  =   BIO_new(BIO_s_mem());
        EVP_PKEY *pkey      =   NULL;

        //生成秘钥
        EVP_PKEY_CTX_set_rsa_keygen_bits(ctx,1024);
        EVP_PKEY_keygen_init(ctx);
        EVP_PKEY_keygen(ctx,&pkey);
        PEM_write_bio_PKCS8PrivateKey(bp_privateKey,pkey,NULL,NULL,0,NULL,NULL);
        PEM_write_bio_PUBKEY(bp_publicKey,pkey);

        //获取秘钥
        char *buff   = NULL;
        int  buffLen = 0;
        buffLen = BIO_get_mem_data(bp_publicKey, &buff);
        QByteArray publicKey(buff,buffLen);
        buffLen = BIO_get_mem_data(bp_privateKey, &buff);
        QByteArray privateKey(buff,buffLen);
        EVP_PKEY_CTX_free(ctx);
        return qMakePair(publicKey,privateKey);
    }
}

QByteArray CryptographyManager::calcHashCode(HASH_ALGORITHM method, const QByteArray *data){
    if(method == CryptographyManager::MD5){
        QCryptographicHash crytoHash(QCryptographicHash::Md5);
        crytoHash.addData(*data);
        return crytoHash.result();
    }

}

QByteArray CryptographyManager::calcHashCode(HASH_ALGORITHM method, QIODevice *device){
    if(method == CryptographyManager::MD5){
        QCryptographicHash crytoHash(QCryptographicHash::Md5);
        crytoHash.addData(device);
        return crytoHash.result();
    }
}


CryptographyManager *CryptographyManager::self(){
    return  s_crytoMgr;
}

