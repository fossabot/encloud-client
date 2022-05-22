#include "globaldatamanager.h"

GlobalDataManager *GlobalDataManager::s_userDataMgr = new GlobalDataManager(NULL);
GlobalDataManager::GlobalDataManager(QObject *parent)
    : QObject{parent}
{

}
const Token &GlobalDataManager::token() const
{
    return m_token;
}

void GlobalDataManager::setToken(const Token &newToken)
{
    m_token = newToken;
}

const User &GlobalDataManager::user() const
{
    return m_user;
}

void GlobalDataManager::setUser(const User &newUser)
{
    m_user = newUser;
}

const Account &GlobalDataManager::account() const
{
    return m_account;
}

void GlobalDataManager::setAccount(const Account &newAccount)
{
    m_account = newAccount;
}

const QList<Message> &GlobalDataManager::messages() const
{
    return m_messages;
}

void GlobalDataManager::setMessages(const QList<Message> &newMessages)
{
    m_messages = newMessages;
}

void GlobalDataManager::setAccountMainKey(const QByteArray mainKey){
    m_account.setMainKey(mainKey);
}

void GlobalDataManager::setAccountPrivateKey(const QByteArray privateKey){
    m_account.setPrivateKey(privateKey);
}

UploadTask *GlobalDataManager::takeUploadTask(){
    if(m_uploadList.isEmpty()){
        return  NULL;
    }
    return m_uploadList.takeFirst();
}

void GlobalDataManager::addUploadTask(UploadTask *task){
    m_uploadList.append(task);
}

DownloadTask* GlobalDataManager::takeDownloadTask(){
    if(m_downloadList.isEmpty()){
        return NULL;
    }
    return m_downloadList.takeFirst();
}

void GlobalDataManager::addDownloadTask(DownloadTask *task){
    m_downloadList.append(task);
}

GlobalDataManager *GlobalDataManager::self(){
    return s_userDataMgr;
}

void GlobalDataManager::beginDataSync(
        qint64 userTimerInterval,
        qint64 accountTimerInterval,
        qint64 messageTimerInterval)
{
    m_userDataSyncTimer = new QTimer(this);
    m_accountDataSyncTimer = new QTimer(this);
    m_messageDataSyncTimer = new QTimer(this);
    connect(m_userDataSyncTimer, &QTimer::timeout,
            this,&GlobalDataManager::userSyncProcess);
    connect(m_accountDataSyncTimer, &QTimer::timeout,
            this,&GlobalDataManager::accountSyncProcess );
    connect(m_messageDataSyncTimer, &QTimer::timeout,
            this, &GlobalDataManager::messageSyncProcess);
    m_userDataSyncTimer->start(userTimerInterval);
    m_accountDataSyncTimer->start(accountTimerInterval);
    m_messageDataSyncTimer->start(messageTimerInterval);
}

void GlobalDataManager::stopDataSync(){
    if(m_userDataSyncTimer != NULL){
        m_userDataSyncTimer->stop();
        m_userDataSyncTimer->deleteLater();
    }
    if(m_accountDataSyncTimer != NULL){
        m_accountDataSyncTimer->stop();
    }

    if(m_messageDataSyncTimer != NULL){
        m_messageDataSyncTimer->stop();
        m_messageDataSyncTimer->deleteLater();
    }
}

void GlobalDataManager::userSyncProcess(){
    //初始化
    NetworkManager* netMgr =  NetworkManager::self();
    MessageManager* msgMgr =  MessageManager::self();

    RequestBase request;
    request.setToken(m_token);

    QJsonValue requestJson =  msgMgr->getRequestBaseJson(&request);
    Reply * reply = netMgr->sendJson(QUrl(USER_SYNC_PATH),requestJson);
    connect(reply, &Reply::readyReadJson, this, [this,msgMgr](QJsonValue responseJson){
        UserSyncResponse response;
        msgMgr->phraseUserSyncResponseJson(&responseJson,&response);
        stdoutput << "user同步:"
                  << "状态码" << response.getStatusCode()
                  << "服务器消息" << response.getServerMessage();
        m_user = response.getUser();

    });
}

void GlobalDataManager::accountSyncProcess(){
    //初始化
    NetworkManager* netMgr =  NetworkManager::self();
    MessageManager* msgMgr =  MessageManager::self();

    RequestBase request;
    request.setToken(m_token);
    QJsonValue requestJson =  msgMgr->getRequestBaseJson(&request);
    Reply * reply = netMgr->sendJson(QUrl(ACCOUNT_SYNC_PATH),requestJson);
    connect(reply, &Reply::readyReadJson, this, [this,msgMgr](QJsonValue responseJson){
        AccountSyncResponse response;
        msgMgr->phraseAccountSyncResponseJson(&responseJson,&response);
        stdoutput << "account同步:"
                  << "状态码" << response.getStatusCode()
                  << "服务器消息" << response.getServerMessage();
        m_account.setAccountName(response.getAccount().getAccountName());
        m_account.setPicture(response.getAccount().getPicture());
    });
}

void GlobalDataManager::messageSyncProcess(){
    //初始化
    NetworkManager* netMgr =  NetworkManager::self();
    MessageManager* msgMgr =  MessageManager::self();

    RequestBase request;
    request.setToken(m_token);

    QJsonValue requestJson =  msgMgr->getRequestBaseJson(&request);
    Reply * reply = netMgr->sendJson(QUrl(MESSAGE_SYNC_PATH),requestJson);
    connect(reply, &Reply::readyReadJson, this, [this,msgMgr](QJsonValue responseJson){
        MessageSyncResponse response;
        msgMgr->phraseMessageSyncResponseJson(&responseJson,&response);
        stdoutput << "message同步:"
                  << "状态码" << response.getStatusCode()
                  << "服务器消息" << response.getServerMessage();
        m_messages = response.getMessages();
    });
}



