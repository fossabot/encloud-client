#include "networkmanager.h"
//Reply
Reply::Reply(QNetworkReply *reply){
    m_reply = reply;
    //读取完成时的操作
    connect(m_reply, &QNetworkReply::finished, this, &Reply::readyReadProcess);

    //上传操作进度
    connect(m_reply, &QNetworkReply::uploadProgress, [this](qint64 bytesSent, qint64 bytesTotal){
        if(bytesTotal <= 0) return;
        emit this->uploadProgress(bytesSent,bytesTotal);
    });

    //下载进度操作
    connect(m_reply, &QNetworkReply::downloadProgress, [this](qint64 bytesReceived, qint64 bytesTotal){
//        stdoutput << bytesReceived;
        emit this->downloadProgress(bytesReceived,bytesTotal);
    });
}

Reply::~Reply(){
    m_reply->deleteLater();
}

QNetworkReply *Reply::getQNetworkReply(){
    return m_reply;
}

qint32 Reply::getStatusCode(){
    return m_statusCode;
}

void Reply::readyReadProcess(){
    QString type =  m_reply->header(QNetworkRequest::ContentTypeHeader).toString();
    m_statusCode =  m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    stdoutput << "reply处理类型: " <<  (type.isEmpty() ? "无响应类型" : type);
    if(type ==  "application/json"){
        QByteArray byteArray = m_reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(byteArray);
        if(document.isArray()){
            emit readyReadJson(document.array());
            return;
        }
        if(document.isObject()){
            emit readyReadJson(document.object());
            return;
        }
    }
    if( type == "application/octet-stream"){
        emit this->readyReadBinary(m_reply);
        return ;
    }

    if(type == "text/html;charset=utf-8" || type=="text/html"){
        stdoutput << m_reply->readAll().data();
    }

    m_statusCode =  m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit this->finished();


}

//NetworkManager
NetworkManager* NetworkManager::s_netmgr = new NetworkManager;
NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
{
    m_httpmgr = new QNetworkAccessManager();

}

NetworkManager::~NetworkManager(){
    delete m_httpmgr;
}

NetworkManager* NetworkManager::self(){
    return NetworkManager::s_netmgr;
}

Reply* NetworkManager::sendJson(QUrl url, QJsonValue jsonValue){
    QNetworkRequest requst;
    requst.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requst.setUrl(url);
    QNetworkReply *reply = m_httpmgr->post(requst, QJsonDocument(jsonValue.toObject()).toJson());

    Reply * forRet = new Reply(reply);
    return forRet;
}

Reply *NetworkManager::sendMultiPart(QUrl url, QHttpMultiPart *multiPart){
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = m_httpmgr->post(request,multiPart);
    Reply * forRet = new Reply(reply);
    return forRet;
}

Reply *NetworkManager::sendGetRequest(QUrl url){
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = m_httpmgr->get(request);
    Reply *forRet = new Reply(reply);
    return forRet;
}

QNetworkAccessManager *NetworkManager::getHttpMgr(){
    return m_httpmgr;
}



