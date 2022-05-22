#include "common/networkmanager.h"
#include "common/settingmanager.h"
#include "common/messagemanager.h"
#include "common/cryptographymanager.h"
#include "common/storagemanager.h"
#include <iostream>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
using namespace std ;
/**
秘钥生成接口
RAND_bytes(key,16);

上下文接口
EVP_CIPHER_CTX *cipherCtx =  EVP_CIPHER_CTX_new()
EVP_CIPHER_CTX_reset(cipherCtx);

加解密接口
EVP_EncryptInit_ex(cipherCtx,EVP_aes_128_ecb(), NULL, key ,NULL);
EVP_EncryptUpdate(cipherCtx, cipher,&outl , str,55)
EVP_EncryptFinal_ex(cipherCtx,cipher+outl, &outl)

EVP_DecryptInit_ex(cipherCtx,EVP_aes_128_ecb(), NULL, key ,NULL)
EVP_DecryptUpdate(cipherCtx, plain, &outl , cipher,64)
EVP_EncryptFinal_ex(cipherCtx,cipher+outl, &outl)
EVP_CIPHER_CTX_free(cipherCtx);
*/
void AES_TEST(){
    //数据和秘钥
    int outl = 0;
    unsigned char str[64] = "hello Just Qt! cpp-cpp-cppfsdfsdfwecgfgergregreggrrgerg";
    unsigned char cipher[100] = {0};
    unsigned char plain[100] = {0};
    unsigned char key[20] = {0};
    //生成秘钥
    RAND_bytes(key,16);
    stdoutput << "秘钥base64表示:" << QByteArray((const char*)key, 16).toBase64();
    stdoutput << "原始数据: " << QByteArray((const char*)str,64).data();
    stdoutput << "================================" ;


    //加密
    EVP_CIPHER_CTX *cipherCtx =  EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(cipherCtx,EVP_aes_128_ecb(), NULL, key ,NULL);
    stdoutput << "状态代码" << EVP_EncryptUpdate(cipherCtx, cipher,&outl , str,55) <<  "outlen" << outl ;
    stdoutput << "状态代码" << EVP_EncryptFinal_ex(cipherCtx,cipher+outl, &outl) << "outlen" << outl ;
    stdoutput << "加密后数据: " << QByteArray((const char*)cipher,64).data();
    stdoutput << "================================" ;

    //解密
    EVP_CIPHER_CTX_reset(cipherCtx);
    EVP_DecryptInit_ex(cipherCtx,EVP_aes_128_ecb(), NULL, key ,NULL);
    stdoutput << "秘钥base64表示:" << QByteArray((const char*)key, 16).toBase64();
    stdoutput << "状态代码" <<EVP_DecryptUpdate(cipherCtx, plain, &outl , cipher,64) << "outlen" << outl ;
    stdoutput << "状态代码" <<EVP_DecryptFinal_ex(cipherCtx,plain+outl, &outl)<< "outlen" << outl ;
    stdoutput << "解密后数据: " << QByteArray((const char*)plain,55).data();
    EVP_CIPHER_CTX_free(cipherCtx);

    exit(0);
}
/**
bio接口
BIO_new(BIO_s_mem()或BIO_s_file())
BIO_get_mem_data(BIO*, char**)
BIO_free()

上下文接口
EVP_PKEY_CTX_new(key, NULL);
EVP_PKEY_CTX_new_id(key, NULL);
EVP_PKEY_CTX_free

证书接口
X509_new()
PEM_read_bio_X509(bp, &x, 0, NULL)
PEM_write_bio_X509(bp, x)
X509_free()

秘钥接口
EVP_PKEY_new
EVP_PKEY_free

PEM_write_bio_PKCS8PrivateKey(bp, key, EVP_des_ede3_cbc(),NULL, 0, 0, "hello"))
PEM_read_bio_PrivateKey(bp, NULL, pass_cb, "My Private Key") , int pass_cb(char *buf, int size, int rwflag, void *u)

PEM_write_bio_PUBKEY();
PEM_read_bio_PUBKEY();

EVP_PKEY_keygen_init(EVP_PKEY_CTX *ctx)
EVP_PKEY_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY **ppkey);

加解密接口
int EVP_PKEY_encrypt_init(EVP_PKEY_CTX *ctx);
int EVP_PKEY_encrypt(EVP_PKEY_CTX *ctx,
                     unsigned char *out, size_t *outlen,
                     const unsigned char *in, size_t inlen);

int EVP_PKEY_decrypt_init(EVP_PKEY_CTX *ctx);
int EVP_PKEY_decrypt(EVP_PKEY_CTX *ctx,
                     unsigned char *out, size_t *outlen,
                     const unsigned char *in, size_t inlen);
*/
void RSA_TEST(){
    //初始化
    int outl = 0;
    unsigned char str[64] = "hello Just Qt! cpp-cpp-cppcpp-ppppppppppppppppppppppppp";
    unsigned char cipher[100] = {0};
    unsigned char plain[100] = {0};
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

    //秘钥生成
    EVP_PKEY * key = NULL;
    stdoutput << "test1"<< EVP_PKEY_keygen_init(ctx);
    stdoutput << "test2"<< EVP_PKEY_CTX_set_rsa_keygen_bits(ctx,1024);
    stdoutput << "test3"<< EVP_PKEY_keygen(ctx, &key);
    EVP_PKEY_CTX_free(ctx);

    //公钥加密
    ctx = EVP_PKEY_CTX_new(key, NULL);

    stdoutput << "test4"<< EVP_PKEY_encrypt_init(ctx);
    stdoutput << "test5"<< EVP_PKEY_encrypt(ctx, cipher, (size_t*)&outl, str, 55);
    stdoutput << "加密输出大小"  << outl ;
    stdoutput << "加密后数据: " << QByteArray((const char*)plain,55).data();
    stdoutput << "===========================";

    //私钥解密
    EVP_PKEY_decrypt_init(ctx);
    EVP_PKEY_decrypt(ctx, plain, (size_t*)&outl,cipher, 128);
    stdoutput << "解密输出大小"  << outl ;
    stdoutput << "解密后数据: " << QByteArray((const char*)plain,55).data();

    //释放资源
    EVP_PKEY_CTX_free(ctx);
    exit(0);
}

/**
上下文接口
EVP_MD_CTX_new
EVP_MD_CTX_free()

EVP_SignInit(ctx, EVP_sha512())
EVP_SignUpdate
EVP_SignFinal

EVP_VerifyInit
EVP_VerifyUpdate
EVP_VerifyFinal
*/
void MD5_TSET(){

}
