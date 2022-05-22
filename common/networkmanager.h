#pragma once

#include "globalmarco.h"
#include "entity/uploadtask.h"
#include "messagemanager.h"
#include "settingmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QMimeDatabase>
//响应管理器
class Reply: public QObject{
    Q_OBJECT
    friend class NetworkManager;
//非静态成员
public:
    explicit Reply(QNetworkReply *reply);
    ~Reply();
public:
    QNetworkReply*  getQNetworkReply();
    qint32          getStatusCode();
private:
    QNetworkReply   *m_reply;
    qint32          m_statusCode;
private slots:
    void readyReadProcess();

//信号
signals:
    void readyReadJson(QJsonValue jsonValue);
    void readyReadBinary(QIODevice *dataDevice);
    void finished();
    void uploadProgress(qint64 bytesSend, qint64 bytesTotals);
    void downloadProgress(qint64 bytesDownload, qint64 bytesTotals);
};


//网络管理器
class NetworkManager : public QObject{
    Q_OBJECT
//非静态成员
private:
    explicit NetworkManager(QObject *parent = nullptr);
    explicit NetworkManager(const NetworkManager &other);
    ~NetworkManager();

public:
    Reply*  sendJson(QUrl url, QJsonValue jsonValue);
    Reply*  sendMultiPart(QUrl url, QHttpMultiPart *multiPart);
    Reply*  sendGetRequest(QUrl url);

    QNetworkAccessManager* getHttpMgr();

private:

    QNetworkAccessManager   *m_httpmgr;
//静态成员
public:
    static NetworkManager   *self();
private:
    static NetworkManager   *s_netmgr;

//信号
signals:

};

