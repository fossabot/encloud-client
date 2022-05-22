#include "test/qtapitest.h"
#include "common/networkmanager.h"
#include "common/settingmanager.h"
#include "common/messagemanager.h"
#include "common/cryptographymanager.h"
#include "common/storagemanager.h"
#include <iostream>
#include <QApplication>
#include <QString>
#include <QObject>
using namespace std;

QNetworkAccessManager * netmgr = new QNetworkAccessManager();
void network_test(void){
    QNetworkRequest requst;
    requst.setHeader(QNetworkRequest::ContentTypeHeader, "application/text");
    requst.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.102 Safari/537.36");
    requst.setUrl(QUrl("https://www.bilibili.com"));
    QNetworkReply* reply =  netmgr->get(requst);
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

void MD5_test(void){
    QJsonObject json;
    json.insert("itemID",QString("222"));
    json.insert("token", "8b84f6224394478d851880c83b5043c8");
    QNetworkRequest request;
    request.setUrl(QUrl(DOWNLOAD_FILE_PATH));
    request.setRawHeader("Cookie","SESSIONID=055a62d03c2d49d0b7f2e03ba111bcd7");
    QByteArray jsonBytes = QJsonDocument(json).toJson();
    QNetworkReply * reply =  netmgr->post(request,jsonBytes);
    QObject::connect(reply,&QNetworkReply::readyRead, [=](){
       QByteArray  bytes =  reply->readAll();
       stdoutput << bytes.data();
    });
}


