#pragma once

#include "common/globalmarco.h"
#include "messagemanager.h"
#include "storagemanager.h"

class SettingManager : public QObject{
    Q_OBJECT
//非静态成员
private:
    explicit SettingManager(QObject *parent = nullptr);
    explicit SettingManager(const SettingManager& other);
public:
    void setConfigFilePath(QString path);
    void setServerName(QString name);
    void setServerPort(QString port);
    void setUploadConcurrentThreadCount(qint8 count);
    void setDownloadConcurrentThreadCount(qint8 count);

    QString getConfigFilePath(QString path);
    QString getServerName(QString name);
    QString getServerPort(QString port);
    qint8 getUploadConcurrentThreadCount(qint8 count);
    qint8 getDownloadConcurrentThreadCount(qint8 count);

private:

    //客户端设置
    QString     m_configFilePath;

    //服务器设置
    QString     m_serverName;
    QString     m_serverPort;

    //传输设置
    qint8       m_uploadConcurrentThreadCount;
    qint8       m_downloadConcurrentThreadCount;

//静态成员
public:
    static SettingManager *self();

private:
    static SettingManager *s_settingMgr;



};

