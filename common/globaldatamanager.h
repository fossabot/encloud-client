#pragma once
#include "globalmarco.h"
#include "common/networkmanager.h"
#include "common/messagemanager.h"
#include "entity/user.h"
#include "entity/account.h"
#include "common/entity/group.h"
#include "common/entity/share.h"
#include "common/entity/message.h"
#include "common/entity/uploadtask.h"
#include "common/entity/downloadtask.h"
#include <QObject>
#include <QDateTime>
#include <QImage>
#include <QTimer>


class GlobalDataManager : public QObject{
    Q_OBJECT
//非静态成员
public:
    const Token &token() const;
    void setToken(const Token &newToken);
    const User &user() const;
    void setUser(const User &newUser);
    const Account &account() const;
    void setAccount(const Account &newAccount);
    const QList<Message> &messages() const;
    void setMessages(const QList<Message> &newMessages);

    void setAccountMainKey(const QByteArray mainKey);
    void setAccountPrivateKey(const QByteArray privateKey);

    UploadTask* takeUploadTask();
    void addUploadTask(UploadTask *task);

    DownloadTask* takeDownloadTask();
    void addDownloadTask(DownloadTask *task);

    bool clearData();
    void beginDataSync(qint64 userTimerInterval,qint64 accountTimerInterval,qint64 messageTimerInterval);
    void stopDataSync();
private:
    explicit GlobalDataManager(QObject *parent = nullptr);
    void userSyncProcess();
    void accountSyncProcess();
    void messageSyncProcess();
    Token                   m_token;
    User                    m_user;
    Account                 m_account;
    QList<Message>          m_messages;
    QTimer                  *m_userDataSyncTimer;
    QTimer                  *m_accountDataSyncTimer;
    QTimer                  *m_messageDataSyncTimer;
    QList<UploadTask*>      m_uploadList;
    QList<DownloadTask*>    m_downloadList;

//静态成员
public:
    static GlobalDataManager  *self();
private:
    static GlobalDataManager  *s_userDataMgr;
signals:
};

