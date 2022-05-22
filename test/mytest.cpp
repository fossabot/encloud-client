#include "test/mytest.h"
#include "common/networkmanager.h"
#include "common/settingmanager.h"
#include "common/messagemanager.h"
#include "common/cryptographymanager.h"
#include "common/storagemanager.h"
#include "common/entity/directory.h"
#include "common/entity/directoryitem.h"
#include "common/globalmarco.h"
#include <QApplication>
#include <QMimeDatabase>
#include <QMap>
#include <QBuffer>

CryptographyManager *crytoMgr =  CryptographyManager::self();
NetworkManager * netMgr = NetworkManager::self();
void networkmgr_test(void){
    QNetworkRequest requst;
    requst.setHeader(QNetworkRequest::ContentTypeHeader, "application/text");
    requst.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.102 Safari/537.36");
    requst.setUrl(QUrl("http://localhost:8080/test/headertest"));
    QNetworkReply* reply =  netMgr->getHttpMgr()->get(requst);
    QObject::connect(reply, &QNetworkReply::uploadProgress, [reply](qint64 bytesSent, qint64 bytesTotal){
        stdoutput << "已上传量" <<bytesSent << "总上传量" << bytesTotal;
    });
    QObject::connect(reply, &QNetworkReply::downloadProgress, [reply](qint64 bytesReceived, qint64 bytesTotal){
        stdoutput << "已接收量"<<bytesReceived << "总下载量: "<< bytesTotal;
    });
    QObject::connect(reply, &QNetworkReply::redirected, [reply](const QUrl &url){
        stdoutput << "重定向到"<< url << "了";
    });
    QObject::connect(reply, &QNetworkReply::encrypted, [reply](){
        stdoutput << "已加密传输";
    });

    QObject::connect(reply,&QNetworkReply::readyRead,  [reply,requst](){
        QByteArray result =  reply->readAll();
        stdoutput << result.data();
        QApplication::exit();
    });
}


/**
jsonTset
*/
void netowrkmgr_test2(void){
    QJsonObject  json;
    json.insert("age", 111);
    json.insert("name", "陈宏峰2");
    Reply *reply = netMgr->sendJson(QUrl(LOGIN_PATH),json);
    QObject::connect(reply, &Reply::readyReadJson,[reply](QJsonValue jsonValue){
        stdoutput << jsonValue.toObject();
        stdoutput << "connet函数中"<< (int*)reply;
        reply->deleteLater();
        QApplication::exit();
    });
}
void cryptographymanager_test1(){
    QByteArray key = crytoMgr->symKeyGenerate(CryptographyManager::AES_128_ECB);
    QByteArray str = QByteArray("hello world", 11);
    QByteArray encipher =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB, &str,&key,NULL);
    QByteArray plain =
            crytoMgr->symDecipher(CryptographyManager::AES_128_ECB, &encipher,&key, NULL);
    stdoutput<<  "str size:" << str.size() << "str: " << str.data();
    stdoutput<<  "key size: " << key.size() << "key base64: "<< key.toBase64();
    stdoutput<<  "encipher size: " << encipher.size() << " encipher base64: " << encipher.toBase64();
    stdoutput<<  "plain size: " << plain.size() << " plain: " << plain.data();
    exit(0);
}

void cryptographymanager_test2(){
    QPair<QByteArray,QByteArray> keyPair =  crytoMgr->asyKeyGenerate(CryptographyManager::RSA_1024);
    stdoutput << keyPair.first.data();
    stdoutput << keyPair.second.data();
    exit(0);
}

void base64Test(){
    QString  str  = "java844444444441";
    QByteArray strBase64 =  str.toLocal8Bit().toBase64();
    stdoutput << strBase64.size();
    QByteArray str1 =  QByteArray::fromBase64(strBase64);
    stdoutput << str1.size();
    stdoutput << str1.data();
    exit(0);
}

void paddingTest(){
    QString str = "hello11";
    QByteArray bytearray = str.toLocal8Bit();
    bytearray.append(16-bytearray.size(),'\0');
    stdoutput << bytearray << bytearray.size();
    exit(0);
}

void mimeTest(){
    QMimeDatabase database;
    stdoutput << database.mimeTypeForFile("/home/vick/Screenshot_20220408_105647.png").name();
}

void mapTest(){
    QMap<QString, Directory> map;
    Directory dir;
    dir.setDirectoryName("C++——");
    map.insert("dir1", dir);
    stdoutput <<  map.value("dir1").getDirectoryName();
    map["dir1"].setDirectoryName("java__");
    stdoutput <<  map.value("dir1").getDirectoryName();
    exit(0);
}

void variantTest(){
    DirectoryItem item;
    item.setItemName("java");

    QVariant variant =  QVariant::fromValue(&item);
    stdoutput << variant;
    DirectoryItem *newItem = variant.value<DirectoryItem*>();
    stdoutput << newItem->getItemName();
    exit(0);
}

void qbuffTest(){
    CryptographyManager * crytoMgr =  CryptographyManager::self();
    QBuffer buffEncipher;
    QBuffer buffDecipher;
    buffEncipher.open(QIODevice::ReadWrite);
    buffDecipher.open(QIODevice::ReadWrite);
    QFile file("/home/vick/qBittorrent.tar.gz");
    file.open(QIODevice::ReadOnly);

    QByteArray key = crytoMgr->symKeyGenerate(CryptographyManager::AES_128_ECB);
    QByteArray temp;
    QByteArray temp2;
    qint64 blockSize = 1024*4;
    qint64 totalBytes =  QFileInfo("/home/vick/qBittorrent.tar.gz").size();
    qint64 remainingBytes = totalBytes;
    qint64 byteWritten = 0;
    stdoutput << totalBytes;
    //加密
    while(byteWritten != totalBytes){
        temp = file.read(qMin(remainingBytes, blockSize));
        temp2 = crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                      &temp,
                                      &key,NULL);
        buffEncipher.write(temp2);
        byteWritten += temp.length();
        remainingBytes -= temp.length();
        temp.resize(0);
        temp2.resize(0);
    }

    totalBytes = buffEncipher.size();
    stdoutput << totalBytes;
    remainingBytes = totalBytes;
    byteWritten = 0;
    buffEncipher.reset();
    while(byteWritten != totalBytes){
        temp = buffEncipher.read(qMin(remainingBytes, blockSize));
        temp2 = crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                                      &temp,
                                      &key,NULL);
        buffDecipher.write(temp2);
        byteWritten += temp.length();
        remainingBytes -= temp.length();
        temp.resize(0);
        temp2.resize(0);
    }
    stdoutput << buffDecipher.data().size();
    QFile newFile("/home/vick/aaa.tar.gz");
    newFile.open(QIODevice::WriteOnly);
    newFile.write(buffDecipher.data());
    newFile.close();
    stdoutput << "已完成";
    exit(0);
}

void testED(){
    QFile file("/home/vick/qBittorrent.tar.gz");
    file.open(QIODevice::ReadOnly);

    QByteArray key = crytoMgr->symKeyGenerate(CryptographyManager::AES_128_ECB);
    QByteArray fileBytes =  file.readAll();
    QByteArray file_with_encipher = crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                  &fileBytes,
                                  &key,NULL);

    QByteArray file_with_Decipher = crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                                  &file_with_encipher,
                                  &key,NULL);
    stdoutput << fileBytes.size();
    stdoutput << file_with_encipher.size();
    stdoutput << file_with_Decipher.size();
    QFile file2("/home/vick/bbb.tar.gz");
    file2.open(QIODevice::WriteOnly);
    file2.write(file_with_Decipher);
    file2.close();
    file.close();
    stdoutput   << "已完成";
    exit(0);
}


void downloadTest(){


}
