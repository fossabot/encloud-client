#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QObject>
#include <QSslConfiguration>
QNetworkAccessManager mgr;
QSslConfiguration sslconfig;
void test(void){
    QNetworkRequest requst;
    QString data("hello world");
    //requst.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    requst.setHeader(QNetworkRequest::ContentTypeHeader, "application/text");
    requst.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.102 Safari/537.36");
    requst.setUrl(QUrl("http://192.168.5.1:8080/encloud/echo-test"));
    //.setSslConfiguration(sslconfig);
    QNetworkReply* reply =  mgr.get(requst);

    QObject::connect(reply,&QNetworkReply::readyRead,  [reply,requst](){
        QByteArray result =  reply->readAll();
        qDebug() << result.data();
    });
    QObject::connect(reply, &QNetworkReply::uploadProgress, [reply](qint64 bytesSent, qint64 bytesTotal){
       qDebug() << "upload" <<bytesSent;
    });
    QObject::connect(reply, &QNetworkReply::downloadProgress, [reply](qint64 bytesReceived, qint64 bytesTotal){
       qDebug() << "download"<<bytesReceived << "total: "<< bytesTotal;
    });
    QObject::connect(reply, &QNetworkReply::redirected, [reply](const QUrl &url){
       qDebug() << "重定向到"<< url << "了";
    });
    QObject::connect(reply, &QNetworkReply::encrypted, [reply](){
       qDebug() << "已加密传输";
    });

}
